#include <iostream>

class Complex {
public:
	Complex() : m_real{0}, m_im{0} {}
	Complex(float real, float im) : m_real{real}, m_im{im} {}

	// Will not compile!
	// Complex(Complex other) : m_real{other.m_real}, m_im{other.m_im} {}
	Complex(const Complex& other) : m_real{other.m_real}, m_im{other.m_im} {}
	// Complex(const Complex& other) = delete;

	// Complex& operator=(const Complex& other) = delete;
	Complex& operator=(const Complex& other) {
		m_real = other.m_real;
		m_im = other.m_im;
		return *this;
	}

	float real() const { return m_real; }
	float im() const { return m_im; }

private:
	float m_real;
	float m_im;
};

void example() {
	Complex c{1, 2};

	// It is not a copy - it is a constructor call!
	Complex not_a_copy = Complex{3, 4};

	// Call a copy constructor here
	Complex copy = c;

	Complex assign;
	// Call a operator= here
	assign = c;

	Complex assign2;
	assign2 = assign = c;
}

int main() {
	example();

	return 0;
}