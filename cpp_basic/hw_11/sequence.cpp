#include <cstddef>
#include <iostream>
#include "interface.h"

template <class T>
class Sequence : public IContainer<T>
{
public:
    Sequence() : m_size{0}, m_region{nullptr} {}

    void push_back(T value) override
    {
        insert(m_size, value);
    }

    void insert(int position, T value) override
    {
        T *new_region = new T[m_size + 1]; // новая область памяти
        int shift = 0;
        for (size_t i = 0; i < m_size + 1; ++i)
        {
            if (i == position)
            {
                new_region[i] = value; // добавление нового элемента
                shift = 1;
            }
            else
            {
                new_region[i] = m_region[i - shift]; // копирование элементов
            }
        }
        delete[] m_region;     // удаление старой области
        m_region = new_region; // сохранение новой в мембер
        m_size += 1;
    }

    void erase(int position) override
    {
        T *new_region = new T[m_size - 1]; // новая область памяти
        int shift = 0;
        for (int i = 0; i < m_size; ++i)
        {
            bool res = i == position;
            if (i == position - 1)
            {
                shift = 1;
            }
            else
            {
                new_region[i - shift] = m_region[i]; // копирование элементов
            }
        }
        delete[] m_region;     // удаление старой области
        m_region = new_region; // сохранение новой в мембер
        m_size -= 1;
    }

    int size() override
    {
        return m_size;
    }

    T operator[](int index) override
    {
        return m_region[index];
    }

    void print() override
    {
        for (int i = 0; i < m_size; i++)
        {
            std::cout << m_region[i];
            if (i != m_size - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }

private:
    T *m_region;
    int m_size;
};