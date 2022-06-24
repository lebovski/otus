// OTUS C++ basic course
// Recursive fibinacci numbers

#include <iostream>
#include <cstdlib>

// Eval nth fibanicci number
unsigned long fib(unsigned long n) {
    if (n < 2) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

int main(int argc, char *argv[]) {
    unsigned long n = 100;
    if (argc == 2) {
        long tmp = std::atol(argv[1]);
        if (tmp < 0) {
            std::cerr << "Only non-negative number allowed\n";
            return 1;
        }
        n = tmp;
    }
    for (unsigned long i = 0; i < n; ++i) {
        std::cout << fib(i) << "\n";
    }
    return 0;
}