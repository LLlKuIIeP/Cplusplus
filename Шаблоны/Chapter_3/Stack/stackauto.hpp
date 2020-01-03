// 3.4
#pragma once
#include <array>
#include <cassert>


template<typename T, auto Maxsize>
class Stack
{
public:
    using size_type = decltype (Maxsize);

    Stack();
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const
    {
        return numElems == 0;
    }
    size_type size() const
    {
        return numElems;
    }

private:
    std::array<T, Maxsize> elems;
    size_type numElems;
};

template<typename T, auto Maxsize>
Stack<T, Maxsize>::Stack() : numElems(0) {}

template<typename T, auto Maxsize>
void Stack<T, Maxsize>::push(T const& elem)
{
    assert(numElems < Maxsize);
    elems[numElems] = elem;
    ++numElems;
}

template<typename T, auto Maxsize>
void Stack<T, Maxsize>::pop()
{
    assert(!empty());
    --numElems;
}

template<typename T, auto Maxsize>
T const& Stack<T, Maxsize>::top() const
{
    assert(!empty());
    return elems[numElems - 1];
}
