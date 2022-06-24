#include <iostream>

namespace basic_usage {
	class Complex {
	public:
		Complex() : m_real{0}, m_im{0} {}
		Complex(float real, float im) : m_real{real}, m_im{im} {}

		float real() const { return m_real; }
		float im() const { return m_im; }

	private:
		float m_real;
		float m_im;
	};

	void example() {
		Complex c1{1, 2};
		Complex c2{3, 4};

		Complex c_sum{c1.real() + c2.real(), c1.im() + c2.im()};
		std::cout << "c_sum = " << c_sum.real() << " + " << c_sum.im() << "i" << std::endl;
	}
} // namespace basic_usage

namespace methods {
	class Complex {
	public:
		Complex() : m_real{0}, m_im{0} {}
		Complex(float real, float im) : m_real{real}, m_im{im} {}

		float real() const { return m_real; }
		float im() const { return m_im; }

		Complex sum(Complex rhs) const {
			return Complex{real() + rhs.real(), im() + rhs.im()};
		}

		Complex sub(Complex rhs) const {
			return Complex{real() - rhs.real(), im() - rhs.im()};
		}

	private:
		float m_real;
		float m_im;
	};

	void example() {
		Complex c1{1, 2};
		Complex c2{3, 4};
		Complex c3{5, 6};

		Complex c_sub = c3.sub(c1.sum(c2)); // :( very complex syntax...
		std::cout << "c_sub = " << c_sub.real() << " + " << c_sub.im() << "i" << std::endl;
	}
} // namespace methods

namespace operators {
	class Complex {
	public:
		Complex() : m_real{0}, m_im{0} {}
		// Complex(float real) : m_real{real}, m_im{0} {}
		Complex(float real, float im) : m_real{real}, m_im{im} {}

		float real() const { return m_real; }
		float im() const { return m_im; }

		Complex &operator+=(Complex rhs) {
			m_real += rhs.real();
			m_im += rhs.im();
			return *this;
		}

	private:
		float m_real;
		float m_im;
	};

	Complex operator+(Complex c1, Complex c2) {
		return Complex{c1.real() + c2.real(), c1.im() + c2.im()};
	}

	// Complex operator+(Complex c, float f) {
	// 	return Complex{c.real() + f, c.im()};
	// }

	Complex operator-(Complex c1, Complex c2) {
		return Complex{c1.real() - c2.real(), c1.im() - c2.im()};
	}

	std::ostream &operator<<(std::ostream &os, Complex complex) {
		os << complex.real() << " + " << complex.im() << "i";
		return os;
	}

	void example() {
		Complex c1{1, 2};
		Complex c2{3, 4};
		Complex c3{5, 6};

		Complex c_sub = c3 - (c1 + c2);	 // Nice!
		std::cout << c_sub << std::endl; // Nice also!
		c_sub += c1;

		// What if you want...
		// Complex c4 = c1 + 42.f;
	}

	// operators:
	// + - * / % ^ & | ~ ! = < > += -= *= /= %= ^= &= |=
	// << >> >>= <<= == != <= >=
	// <=> (since C++20)
	// && || ++ -- , ->* -> ( ) [ ]

	// Restrictions
	// The operators
	//     :: (scope resolution),
	//      . (member access),
	//     .* (member access through pointer to member),
	//     ?: (ternary conditional)
	// cannot be overloaded.

	// New operators such as **, <>, or &| cannot be created.
	// It is not possible to change the precedence, grouping, or number of operands of operators.
	// The overload of operator -> must either return a raw pointer,
	// or return an object (by reference or by value) for which operator -> is in turn overloaded.
	// The overloads of operators && and || lose short-circuit evaluation.

} // namespace operators

int main() {

	basic_usage::example();
	methods::example();
	operators::example();

	return 0;
}