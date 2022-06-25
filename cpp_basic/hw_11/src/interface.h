#pragma once

#include <string>

template <class T>
class IContainer
{
public:
    virtual ~IContainer() {}

    virtual void push_back(T value) = 0;
    virtual void insert(int position, T value) = 0;
    virtual void erase(int position) = 0;
    virtual int size() = 0;
    virtual T operator[](int index) = 0;
    virtual std::string name() = 0;
    virtual bool empty() = 0;
    virtual void pop_back() = 0;
};