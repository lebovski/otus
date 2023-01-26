#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

template <typename T>
struct WaitingQueue {

	WaitingQueue()
		: m_headPtr{new Node}, m_tailPtr{m_headPtr.get()}, m_stopped{false} {
	}

	WaitingQueue(const WaitingQueue &) = delete;
	WaitingQueue(WaitingQueue &&) = delete;

	WaitingQueue &operator=(const WaitingQueue &) = delete;
	WaitingQueue &operator=(WaitingQueue &&) = delete;

	/** @brief Takes entry with waiting is case of empty WaitingQueue.
		 *  @param entry result entry.
		 *  @note This is blocking function!
		 *  @return false in case if queue was stopped
		 */
	bool pop(T &entry) {
		// Just pop head with waiting
		return popHead(entry);
	}

	/** @brief Tries to take entry from the front of the WaitingQueue.
		 *  @param entry result entry
		 *  @return true is WaitingQueue was not empty and entry was got,
		 *  false otherwise.
		 *  @note This is non-blocking function.
		 */
	bool tryPop(T &entry) {
		// Just pop head
		std::unique_ptr<Node> prevHead = tryPopHead(entry);
		// And check if WaitingQueue was empty
		return prevHead.get() != nullptr;
	}

	/** @brief Pushes new value to the WaitingQueue.
		 *  @param value value to push.
		 *  @note This function will wake-up only one thread waiting on the pop function.
		 *  @note Template TT only to use perfect forwarding here.
		 */
	template <typename TT>
	void push(TT &&value) {
		// Create new node
		std::unique_ptr<Node> node{new Node};
		// Additional scope to control tailMutex locking
		{
			std::lock_guard<std::mutex> lck{m_tailMutex};
			if (m_stopped)
				return;
			// Push value to the current tail node
			m_tailPtr->value = std::forward<TT>(value);
			// Set next for the current tail
			m_tailPtr->next = std::move(node);
			// Change tail to the new tail (new node)
			m_tailPtr = m_tailPtr->next.get();
		}
		// Notification
		m_conditional.notify_one();
	}

	/** @brief Checks if WaitingQueue is empty.
		 *  @return true if WaitingQueue is empty,
		 *  false otherwise.
		 *  @note This function requires mutex locking.
		 */
	bool empty() {
		std::lock_guard<std::mutex> lck{m_headMutex};
		return m_headPtr.get() == tail();
	}

	/** @brief Notificates all threads to unblock them.
	 * */
	void stop() {
		std::lock_guard<std::mutex> lck1{m_headMutex};
		std::lock_guard<std::mutex> lck2{m_tailMutex};
		m_stopped = true;
		m_conditional.notify_all();
	}

private:
	/** @brief Implementation of the Nde of the linked list
		 */
	struct Node {
		T value;
		std::unique_ptr<Node> next;
	};

	/** @brief Takes tail pointer.
		 *  @return tail pointer
		 *  @note This function is thread-safe
		 */
	Node *tail() {
		std::lock_guard<std::mutex> lck{m_tailMutex};
		return m_tailPtr;
	}

	/** @brief Takes head pointer.
		 *  @return head pointer.
		 *  @note This function is NOT thread-safe. Caller should lock m_headMutex!
		 */
	std::unique_ptr<Node> takeHeadUnsafe() {
		std::unique_ptr<Node> prevHead = std::move(m_headPtr);
		m_headPtr = std::move(prevHead->next);
		return prevHead;
	}

	/** @brief Attempt to take head.
		 *  @return head pointer in case of not empty WaitingQueue,
		 *  empty Node::Ptr otherwise
		 *  @note This function is thread-safe.
		 */
	std::unique_ptr<Node> tryPopHead(T &entry) {
		std::lock_guard<std::mutex> lck{m_headMutex};
		if (m_headPtr.get() == tail()) {
			// WaitingQueue is empty
			return {};
		}
		// Take value from the head node.
		entry = std::move(m_headPtr->value);
		// And remove head node from the list.
		return takeHeadUnsafe();
	}

	/** @brief Takes entry from the head of the WaitingQueue with waiting in case of empty.
		 *  @param entry result entry
		 *  @note This function is thread-safe.
		 *  @note This is blocking function!
		 *  @returns false in case if WaitingQueue was stopped
		 */
	bool popHead(T &entry) {
		std::unique_lock<std::mutex> lck{m_headMutex};
		// Wait until WaitingQueue is not empty
		m_conditional.wait(
			lck, 
			[&]() { 
				if (m_stopped) return true;
				return (m_headPtr.get() != tail()); 
			}
		);
		if (m_stopped)
			return false;
		// Take value
		entry = std::move(m_headPtr->value);
		// And remove head node from the list
		takeHeadUnsafe();
		return true;
	}

	// Mutex for the head element of the WaitingQueue
	std::mutex m_headMutex;
	// Head element pointer
	std::unique_ptr<Node> m_headPtr;
	// Mutex for the tail element of the WaitingQueue
	std::mutex m_tailMutex;
	// Raw pointer to the tail element
	Node *m_tailPtr;
	// Condition for waiting data
	std::condition_variable m_conditional;
	// Stop flag
	bool m_stopped;
};

using WorkQueue = WaitingQueue<int>;
const int WORK_COUNT = 100;

void work_producer(WorkQueue& queue, std::atomic<bool>& stop_flag) {
	for (int i = 0; i < WORK_COUNT; ++i) {
		// put new work to the queue
		std::cout << "work_producer - put new value: " << i << std::endl;
		if (!stop_flag)
			queue.push(i);
		else
			break;
		// wait a bit before the next iteration
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	std::cout << "work_producer - end of cycle" << std::endl;
}

void work_consumer(WorkQueue& queue) {
	int value = 0;
		// make a waiting pop from the queue
	while(queue.pop(value)) {
		std::cout << "work_consumer - pop new value: " << value << std::endl;
	}
	std::cout << "work_consumer - end of cycle" << std::endl;
}

void example() {
	std::atomic<bool> stop_flag = false;
	WorkQueue work_queue;

	std::cout << "Launch threads!" << std::endl;

	std::thread work_producer_thread{
		work_producer, 
		std::ref(work_queue),
		std::ref(stop_flag)
	};
	std::thread work_consumer_thread1{
		work_consumer,
		std::ref(work_queue)
	};
	std::thread work_consumer_thread2{
		work_consumer,
		std::ref(work_queue)
	};

	std::this_thread::sleep_for(std::chrono::seconds{5});

	std::cout << "Finish working!" << std::endl;

	// stop all threads
	stop_flag = true;
	// need this to unblock all threads, witch are waiting the queue
	work_queue.stop();
	// wait all threads
	work_producer_thread.join();
	work_consumer_thread1.join();
	work_consumer_thread2.join();

	std::cout << "Finished!" << std::endl;
}

int main() {

	example();

	return 0;
}