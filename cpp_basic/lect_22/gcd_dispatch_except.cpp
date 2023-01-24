// Calculate greatest common divisor using Euclidean algorithm

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <system_error>

enum class GcdErrc {
    NoError = 0,
    NotEnoughParams,
    NegativeNumber,
    DivisionByZero,
};

class gcd_category : public std::error_category {
  public:
    const char *name() const noexcept override {
        return "gcd";
    }

    std::string message(int condition) const override;
};

std::error_condition make_error_condition(GcdErrc errc) {
    static gcd_category gcd_err_category;
    return std::error_condition{static_cast<int>(errc), gcd_err_category};
}

unsigned gcd(unsigned a, unsigned b);
unsigned parse_unsigned(char *str);

int main(int argc, char *argv[]) {
    try {
        if (argc < 3) {
            throw make_error_condition(GcdErrc::NotEnoughParams);
        }
        unsigned a = parse_unsigned(argv[1]);
        unsigned b = parse_unsigned(argv[2]);
        std::cout << gcd(a, b) << "\n";
    } catch (const std::error_condition &err) {
        std::cerr << err.message() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::invalid_argument &err) {
        std::cerr << err.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::out_of_range &err) {
        std::cerr << err.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unknown exception\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

unsigned gcd(unsigned a, unsigned b) {
    if (!b) {
        throw make_error_condition(GcdErrc::DivisionByZero);
    }
    do {
        unsigned r = a % b;
        a = b;
        b = r;
    } while (b);
    return a;
}

unsigned parse_unsigned(char *str) {
    int val = std::stoi(str);
    if (val < 0) {
        throw make_error_condition(GcdErrc::NegativeNumber);
    }
    return static_cast<unsigned>(val);
}

std::string gcd_category::message(int condition) const {
    switch (static_cast<GcdErrc>(condition)) {
    case GcdErrc::NoError:
        return "No error";
    case GcdErrc::NotEnoughParams:
        return "Usage: gcd a b";
    case GcdErrc::NegativeNumber:
        return "Number parse error: input must be positive integer";
    case GcdErrc::DivisionByZero:
        return "GCD error: divison by zero";
    default:
        return "Unknown error";
    }
}