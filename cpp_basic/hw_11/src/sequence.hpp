#include <cstddef>
#include <iostream>
#include "interface.h"

template <class T>
class Sequence : public IContainer<T>
{
public:
    Sequence() : m_region{nullptr}, m_size{0} {}

    void push_back(T value) override { insert(m_size, value); }

    void insert(int position, T value) override
    {
        T *new_region = new T[m_size + 1];
        int shift = 0;
        for (int i = 0; i < m_size + 1; ++i)
        {
            if (i == position)
            {
                new_region[i] = value;
                shift = 1;
            }
            else
            {
                new_region[i] = m_region[i - shift];
            }
        }

        delete[] m_region;
        m_region = new_region;

        m_size += 1;
    }

    void erase(int position) override
    {
        T *new_region = new T[m_size - 1];
        int shift = 0;
        for (int i = 0; i < m_size; ++i)
        {
            if (i == position - 1)
            {
                shift = 1;
            }
            else
            {
                new_region[i - shift] = m_region[i];
            }
        }

        delete[] m_region;
        m_region = new_region;

        m_size -= 1;
        if (m_size == 0) {
            m_region = nullptr;
        }
    }

    void pop_back() { erase(m_size); }

    int size() override { return m_size; }

    T operator[](int index) override { return m_region[index]; }

    std::string name() { return "sequence"; }

    bool empty() { return m_size == 0 && m_region == nullptr; }

private:
    T *m_region;
    int m_size;
};