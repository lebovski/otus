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
    Linked() : m_last{nullptr}, m_size{0} {}

    void push_back(T value) override
    {
        Node<T> *new_node = new Node<T>{};

        if (m_last != nullptr)
            m_last->next = new_node;

        new_node->prev = m_last;
        new_node->next = nullptr;
        new_node->data = value;

        m_last = new_node;
        m_size += 1;
    }

    void insert(int position, T value) override
    {
        if (position == 0)
        {
            Node<T> *f = get(1);
            Node<T> *new_node = new Node<T>{};

            new_node->data = value;
            new_node->prev = nullptr;
            new_node->next = f;

            f->prev = new_node;
            m_size += 1;

            return;
        }

        if (position == m_size)
        {
            push_back(value);

            return;
        }

        Node<T> *node = get(position);
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
        Node<T> *node = get(position);
        if (node == nullptr)
        {
            return;
        }

        Node<T> *prev = node->prev;
        Node<T> *next = node->next;

        if (prev != nullptr)
        {
            prev->next = next;
        }
        if (next != nullptr)
        {
            next->prev = prev;
        }

        m_size -= 1;
        if (m_size == 0) {
            m_last = nullptr;
        }
    }

    void pop_back() { erase(m_size); }

    int size() override { return m_size; }

    T operator[](int index) override { return get(index + 1)->data; }

    bool empty() { return m_size == 0 && m_last == nullptr; }

    std::string name() { return "linked"; }

private:
    Node<T> *m_last;
    int m_size;

    Node<T> *get(int index)
    {
        Node<T> *node = m_last;
        for (int i = 0; i < m_size - index; i++)
        {
            node = node->prev;
        }

        return node;
    }
};