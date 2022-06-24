#include <cstring>
#include <iostream>

class DynamicString {
public:
	DynamicString() : m_data{nullptr}, m_size{0} {}

	explicit DynamicString(const char *str) : DynamicString{} {
		if (str == nullptr)
			return;
		// First need to check the length of the [str]
		size_t length = std::strlen(str);
		if (!length)
			return;
		// Now we need to allocate memory for the [length] symbols
		m_data = new char[length + 1]; // one more symbol for the zero-termination
		// And now we can copy all symbols from the [str] to the our memory;
		for (size_t i = 0; i < length; ++i) {
			m_data[i] = str[i];
		}
		// Add one more symbol for the zero-termination
		m_data[length] = '\0';
		// Set a correct [m_size] value
		m_size = length;
	}

	DynamicString(const DynamicString &other) : DynamicString{other.data()} {}

	~DynamicString() {
		delete[] m_data;
	}

	size_t size() const { return m_size; }
	char *data() const { return m_data; }

private:
	char *m_data;
	size_t m_size;
};

void example() {
	std::cout << "Basic usage: " << std::endl;
	DynamicString str{"Hello!"};
	std::cout << str.size() << std::endl;
	std::cout << str.data() << std::endl;
}

namespace constructors {

	struct TrivialStruct {
		int a;
		int b;
	};

	void trivial_example() {
		// Aggregate initialization is possible
		TrivialStruct trivial{
			10,
			12
		};
	}

	struct StillTrivialStruct {
		StillTrivialStruct() = default;

		int a;
		int b;
	};

	void still_trivial_example() {
		// Untill C++20
		StillTrivialStruct still_trivial{
			10,
			12
		};
	};

	struct NotTrivialStruct {
		NotTrivialStruct() {}

		int a;
		int b;
	};

	void not_trivial_example() {
		// Will not compile:
		// error: no matching function for call to 
		// 'constructors::NotTrivialStruct::NotTrivialStruct(<brace-enclosed initializer list>)

		// NotTrivialStruct not_trivial{
		// 	10,
		// 	12
		// };

	}



} // namespace constructors

int main() {
	example();
	return 0;
}
