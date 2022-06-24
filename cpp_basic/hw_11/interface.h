#pragma once

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
    virtual void print() = 0;
};