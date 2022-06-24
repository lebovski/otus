#include <iostream>
#include <iomanip>
#include <limits>
#include <cfloat>
#include <math.h>

using std::cout;
using std::endl;
using std::setw;

int main(int, char *[])
{
     const unsigned int text_width = 14;
     const unsigned int digit_width = 11;

     // float
     cout << endl
          << setw(text_width) << "float"
          << setw(text_width) << "size is " << sizeof(float) << " byte(s)"
          << setw(text_width) << "min value = "
          << setw(digit_width) << std::numeric_limits<float>::min()
          << setw(text_width) << "max value = "
          << setw(digit_width) << std::numeric_limits<float>::max()
          << endl
          << setw(text_width + 1) << "Eps = " << std::numeric_limits<float>::epsilon() << endl;

     // double
     cout << endl
          << setw(text_width) << "double"
          << setw(text_width) << "size is " << sizeof(double) << " byte(s)"
          << setw(text_width) << "min value = "
          << setw(digit_width) << std::numeric_limits<double>::min()
          << setw(text_width) << "max value = "
          << setw(digit_width) << std::numeric_limits<double>::max()
          << endl
          << setw(text_width + 1) << "Eps = " << std::numeric_limits<double>::epsilon() << endl;

     // long double
     cout << endl
          << setw(text_width) << "long double"
          << setw(text_width) << "size is " << sizeof(long double) << " byte(s)"
          << setw(text_width) << "min value = "
          << setw(digit_width) << std::numeric_limits<long double>::min()
          << setw(text_width) << "max value = "
          << setw(digit_width) << std::numeric_limits<long double>::max()
          << endl
          << setw(text_width + 1) << "Eps = " << std::numeric_limits<long double>::epsilon() << endl;

     const double a = 0.2;
     const double b = 1 / std::sqrt(5) / std::sqrt(5);

     cout << std::setprecision(20) << a << std::endl;
     cout << std::setprecision(20) << b << std::endl;

     if (a != b)
          cout << "a != b" << std::endl;

     const double eps1 = 1e-14;
     if (std::fabs(a - b) < eps1)
          cout << "a == b within " << eps1 << std::endl;

     return 0;
}

// End of the file
