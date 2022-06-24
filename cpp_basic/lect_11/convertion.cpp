#include <iostream>
#include <string>

namespace cast {

	void test_function(int a, int b) {
		std::cout << a << " + " << b << " = " << a + b << std::endl;
	}

	void test() {
		{
			int a = 12;
			int b = 21;
			test_function(a, b); // Good - int, int
		}

		{
			short a = 12;
			short b = 21;
			test_function(a, b); // Good also - short, short
		}

		{
			int a = 12;
			float b = 21.0f;
			// Warning:
			// warning C4244: 'argument': conversion from 'float' to 'int', possible loss of data
			test_function(a, b);

			// Good now - explicit type cast
			test_function(a, static_cast<int>(b));
		}
	}

	template <typename T>
	class Optional {
	public:
		Optional()
			: m_is_set{false} {}
		Optional(const T &value)
			: m_value{value}, m_is_set{true} {}

		explicit operator bool() const {
			return m_is_set;
		}

		operator T() const {
			return m_value;
		}

		T value() const {
			return m_value;
		}

	private:
		T m_value;
		bool m_is_set;
	};

	void example() {
		Optional<std::string> no_value_optional{};

		if (!no_value_optional) { // Optional::operator bool call
			std::cout << "no_value_optional does not have a value!" << std::endl;
		}

		Optional<std::string> value_optional{"Hello!"};
		if (value_optional) {
			std::cout << "value_optional has value = " << value_optional.value() << std::endl;
		}

		// Good - Optional::operator T call
		std::string str = value_optional;

		// Hm...???
		// Optional::operator bool call if it is not explicit
		// float f = value_optional;
	}

} // namespace cast

namespace error {
	enum class ErrorCode {
		Ok,
		Failed,
		NotFound,
		OutOfMemory
	};

	class Error {
	public:
		Error() : m_code{ErrorCode::Ok} {}

		explicit Error(ErrorCode code) : m_code{code} {}

		bool isError() const { return m_code != ErrorCode::Ok; }
		ErrorCode getError() const { return m_code; }

		operator bool() const { return isError(); }
	private:
		ErrorCode m_code;
	};

	void example() {
		Error error{ErrorCode::NotFound};

		if (error.isError()) {
			std::cout << "We have error!" << std::endl;
		} else {
			std::cout << "Everything is good!" << std::endl;
		}

		// Call the Error::operator bool here
		if (error) {
			std::cout << "We have error!" << std::endl;
		} else {
			std::cout << "Everything is good!" << std::endl;
		}

		float f = error;
	}
} // namespace error

int main() {

	cast::test();
	cast::example();
	error::example();

	return 0;
}