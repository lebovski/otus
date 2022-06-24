#include <cstddef>
#include <iostream>
#include "interface.h"

template <class T>
struct Node
{
    Node *next; // указатель на следующий элемент Node
    Node *prev; // указатель на предыдущий элемент Node
    T data;     // пользовательские данные (хранимый объект)
};

template <class T>
class Linked : public IContainer<T>
{
public:
    Linked() : m_size{0}, m_last{nullptr} {}

    void push_back(T value) override
    {
        Node<T> *new_node = new Node<T>{};

        if (m_last != nullptr)
        {
            m_last->next = new_node;
        }
        
        new_node->prev = m_last;
        new_node->next = nullptr;
        new_node->data = value;

        m_last = new_node;
        m_size += 1;
    }

    void insert(int position, T value) override
    {
        Node<T> *node = m_last;
        for (int i = 0; i < m_size - position; i++)
        {
            node = node->prev;
        }

        Node<T> *prev = node;
        Node<T> *next = node->next;

        Node<T> *new_node = new Node<T>{};
        new_node->data = value;
        new_node->prev = prev;
        new_node->next = next;
        prev->next = new_node;
        next->prev = new_node;

        m_size += 1;
    }

    void erase(int position) override
    {
        Node<T> *node = m_last;
        for (int i = 0; i < m_size - position; i++)
        {
            node = node->prev;
        }

        Node<T> *prev = node->prev;
        Node<T> *next = node->next;

        prev->next = next;
        next->prev = prev;

        m_size -= 1;
    }

    int size() override
    {
        return m_size;
    }

    T operator[](int index) override
    {
        Node<T> *node = m_last;
        for (int i = 0; i < index; i++)
        {
            node = node->prev;
        }

        return node->data;
    }

    void print() override
    {
        Node<T> *node = m_last;
        for (int i = 0; i < m_size; i++)
        {
            std::cout << node->data;
            if (i != m_size - 1)
            {
                std::cout << ", ";
            }

            node = node->prev;
        }
        std::cout << std::endl;
    }

private:
    Node<T> *m_first;
    Node<T> *m_last;
    int m_size;
};