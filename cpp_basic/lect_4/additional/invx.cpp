// OTUS C++ bsic course
// Extended Euclidean algorithm
// Pass by pointer example

#include <cstdlib>
#include <iostream>

// Extended Euclidean algorithm to solve
// a*y + b*y = gcd(a, b) equation
// x and y is an optional out parameters
// if x or y is not null according root whill be stored in
int egcd(int a, int b, int *x, int *y) {
    int x1 = 1, x2 = 0;
    int y1 = 0, y2 = 1;

    while (b != 0) {
        int q = a / b;
        int r = a % b;

        int tmp = x2;
        x2 = x1 - q * x2;
        x1 = tmp;

        tmp = y2;
        y2 = y1 - q * y2;
        y1 = tmp;

        a = b;
        b = r;
    }
    if (x != nullptr) {
        *x = x1;
    }
    if (y != nullptr) {
        *y = y1;
    }
    return a;
}

// Find inverse of integer x by mod p
// invx * x = 1 mod p
// return 0 if x is non-inversible
int inv(int x, int p) {
    int invx = 0;
    if (egcd(x, p, &invx, nullptr) != 1) { // no inverse number exists
        return 0;
    }
    return invx;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " x p\n";
        return 1;
    }
    int x = std::atoi(argv[1]);
    int p = std::atoi(argv[2]);
    if (x <= 0 || p <= 0) {
        std::cerr << "Only poitive numbers allowed\n";
        return 1;
    }

    int invx = inv(x, p);
    if (invx == 0) {
        std::cerr << "Non-inversible\n";
        return 1;
    }
    std::cout << invx << "\n";
    return 0;
}