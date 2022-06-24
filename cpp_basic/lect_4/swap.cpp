// OTUS C++ basic course example
// pass parameters by reference to swap function

#include <iostream>

void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " a b\n";
        return 1;
    }
    int a = std::atoi(argv[1]);
    int b = std::atoi(argv[2]);
    swap(a, b);
    std::cout << a << " " << b << "\n";
}
