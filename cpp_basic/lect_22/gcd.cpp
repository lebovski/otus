// Calculate greatest common divisor using Euclidean algorithm

#include <cstdlib>
#include <iostream>

unsigned gcd(unsigned a, unsigned b);

int main(int, char *argv[]) {
  unsigned a = std::atoi(argv[1]);
  unsigned b = std::atoi(argv[2]);

  std::cout << gcd(a, b) << "\n";
  return EXIT_SUCCESS;
}

unsigned int gcd(unsigned int a, unsigned int b) {
  do {
    unsigned r = a % b;
    a = b;
    b = r;
  } while (b);
  return a;
}
