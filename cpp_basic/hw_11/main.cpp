#include <iostream>
#include "src/sequence.hpp"
#include "src/linked.hpp"
#include "src/interface.h"

void print_all(IContainer<int> *seq)
{
    for (int i = 0; i < seq->size(); i++)
    {
        std::cout << (*seq)[i];
            if (i != seq->size() - 1)
            {
                std::cout << ", ";
            }
    }

    std::cout << std::endl;
}

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

        print_all(seq);
        // seq->print();

        std::cout << seq->size() << std::endl;

        seq->erase(3);
        seq->erase(4);
        seq->erase(5);
        print_all(seq);

        seq->insert(0, 10);
        print_all(seq);

        seq->insert(seq->size() / 2, 20);
        print_all(seq);

        seq->insert(seq->size(), 30);
        print_all(seq);
    }
}