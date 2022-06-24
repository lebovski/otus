// OTUS C++ Basic course
// pow function example

#include <cfloat>
#include <cmath>
#include <iostream>
#include <limits>
#include <math.h>

// Write pow function code below

// compare if two float are close enougth and can be interpteted as equal
bool is_close(float a, float b)
{
    if (std::isinf(a) && std::isinf(b))
    {
        return true;
    }

    if (std::isnan(a) && std::isnan(b))
    {
        return true;
    }

    return std::fabs(a - b) < std::numeric_limits<float>::epsilon();
}

// Test compares results of pow function provided by programmer with std::pow
bool test_pow(float base, unsigned int exp)
{
    std::cout << "Testing pow(" << base << ", " << exp << ")\t";
    float expected = std::pow(base, exp);
    float actual = pow(base, exp);

    if (is_close(expected, actual))
    {
        std::cout << "OK\n";
        return true;
    }
    else
    {
        std::cout << "FAIL\n";
        std::cout << "expected: " << expected << ", actual: " << actual << "\n";
        return false;
    }
}

int main()
{
    bool all_success = true;

    all_success &= test_pow(2.0, 3);
    all_success &= test_pow(1.0, 1);
    all_success &= test_pow(5.0, 0);
    all_success &= test_pow(-5.0, 2);
    all_success &= test_pow(-5.0, 3);
    all_success &= test_pow(0.0, 2);
    all_success &= test_pow(1.1e+5, 10);
    all_success &= test_pow(1e-5, 10);
    all_success &= test_pow(INFINITY, 2);
    all_success &= test_pow(NAN, 2);

    return all_success;
}
