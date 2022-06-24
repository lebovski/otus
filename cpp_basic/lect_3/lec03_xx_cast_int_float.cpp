#include <iostream>

int main(int, char *[])
{
    int a1 = 1042284544;
    float x1 = *((float *)&a1);
    std::cout << "From " << a1 << " to " << x1 << std::endl;

    std::cout << (float)a1 << std::endl;

    float x2 = 0.15625;
    int a2 = *((int *)&x2);
    std::cout << "From " << x2 << " to " << a2 << std::endl;

    return 0;
}