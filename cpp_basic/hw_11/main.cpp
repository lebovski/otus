#include <iostream>
#include "sequence.cpp"
#include "linked.cpp"

int main()
{
    std::cout << "Sequence" << std::endl;

    Linked<int> seq;

    for (int i = 0; i < 10; i++)
    {
        seq.push_back(i);
    }

    seq.print();

    std::cout << seq.size() << std::endl;

    seq.erase(3);
    seq.erase(4);
    seq.erase(5);
    seq.print();

    seq.insert(0, 10);
    seq.print();

    // seq.insert(seq.size()/2, 20);
    // seq.print();

    // seq.insert(seq.size(), 30);
    // seq.print();
}