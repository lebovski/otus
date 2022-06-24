#include <algorithm>
#include <iostream>
#include <string>

namespace motivation {

	class Distance {
	public:
		Distance(int value) : m_value{value} {
			std::cout << "Distance(" << value << ")" << std::endl;
		}
		int value() const { return m_value; }

	private:
		int m_value;
	};

	class Weigth {
	public:
		Weigth(int value) : m_value{value} {
			std::cout << "Weigth(" << value << ")" << std::endl;
		}
		int value() const { return m_value; }

	private:
		int m_value;
	};

	int calculate_delivery_price(Distance d, Weigth w) {
		const int minDistance = 10;

		return std::max(d.value(), minDistance) * w.value();
	}

	void example() {
		int distance = 10;
		int weight = 2;

		// We make a mistake - passed arguments in the wrong order
		std::cout << calculate_delivery_price(weight, distance) << std::endl;
		// Wrong price will be computed: 100
	}

} // namespace motivation

namespace solution {

	class Distance {
	public:
		explicit Distance(int value) : m_value{value} {
			std::cout << "Distance(" << value << ")" << std::endl;
		}
		int value() const { return m_value; }

	private:
		int m_value;
	};

	class Weigth {
	public:
		explicit Weigth(int value) : m_value{value} {
			std::cout << "Weigth(" << value << ")" << std::endl;
		}
		int value() const { return m_value; }

	private:
		int m_value;
	};

	int calculate_delivery_price(Distance d, Weigth w) {
		const int minDistance = 10;

		return std::max(d.value(), minDistance) * w.value();
	}

	void example() {
		int distance = 10;
		int weight = 2;

		// Now We can't make such a silly a mistake!
		// We should pass Distance and Weight object explicit
		std::cout << calculate_delivery_price(Distance{distance}, Weigth{weight}) << std::endl;
		// Wrong price will be computed
	}

} // namespace solution

int main() {

	motivation::example();
	solution::example();

	return 0;
}