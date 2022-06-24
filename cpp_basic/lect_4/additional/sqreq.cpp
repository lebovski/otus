// OTUS C++ basic course example
// Square equation solution
// Out function parameters example

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

// Solve square equation with given coefficients a, b and c
// Return number of roots (0, 1 or 2)
// If number of roots is not zero returns root value(s) in out parameters x1 and
// x2 Return -1 if any x will be a solution
int solve_sqreq(double a, double b, double c, double &x1, double &x2) {
    if (std::fpclassify(a) == FP_ZERO) { // linear equation case
        if (std::fpclassify(b) == FP_ZERO) {
            if (std::fpclassify(c) == FP_ZERO) {
                return -1;
            }
            return 0;
        }
        x1 = -c / b;
        return 1;
    }
    double D = b * b - 4 * a * c;
    if (D > 0.0) { // 2 roots
        x1 = (-b - std::sqrt(D)) / (2 * a);
        x2 = (-b + std::sqrt(D)) / (2 * a);
        return 2;
    } else if (std::fpclassify(D) == FP_ZERO) { // 1 root
        x1 = -b / (2 * a);
        return 1;
    } else { // no roots
        return 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " a b c\n";
        return 1;
    }
    double a = std::atof(argv[1]);
    double b = std::atof(argv[2]);
    double c = std::atof(argv[3]);
    double x1 = 0.0, x2 = 0.0;
    
    switch (solve_sqreq(a, b, c, x1, x2)) {
    case -1:
        std::cout << "any x is a root\n";
        break;
    case 0:
        std::cout << "zero roots\n";
        break;
    case 1:
        std::cout << "x = " << x1 << "\n";
        break;
    case 2:
        std::cout << "x1 = " << x1 << "\n";
        std::cout << "x2 = " << x2 << "\n";
        break;
    }
    return 0;
}
