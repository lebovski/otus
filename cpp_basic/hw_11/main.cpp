#include <iostream>
#include "sequence.cpp"
#include "linked.cpp"
#include "interface.h"

int main()
{
    IContainer<int> *containers[2];

    containers[0] = new Linked<int>{};
    containers[1] = new Sequence<int>{};

    for (int i = 0; i < 2; i++)
    {
        IContainer<int> *seq = containers[i];

        std::cout << seq->name() << std::endl;

        for (int i = 0; i < 10; i++)
        {
            seq->push_back(i);
        }

        seq->print();

        std::cout << seq->size() << std::endl;

        seq->erase(3);
        seq->erase(4);
        seq->erase(5);
        seq->print();

        seq->insert(0, 10);
        seq->print();

        seq->insert(seq->size() / 2, 20);
        seq->print();

        seq->insert(seq->size(), 30);
        seq->print();
    }
}