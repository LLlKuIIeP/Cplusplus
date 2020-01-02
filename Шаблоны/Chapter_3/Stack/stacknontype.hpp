#pragma once
#include <array>
#include <cassert>


template<typename T, std::size_t Maxsize>
class Stack
{
public:
    Stack();
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const
    {
        return numElems == 0;
    }
    std::size_t size() const{
        return numElems;
    }

private:
    std::array<T, Maxsize> elems;
    std::size_t numElems;
};

template<typename T, std::size_t Maxsize>
Stack<T, Maxsize>::Stack() : numElems(0) {}

template<typename T, std::size_t Maxsize>
void Stack<T, Maxsize>::push(T const& elem)
{
    assert(numElems < Maxsize);
    elems[numElems] = elem;
    ++numElems;
}

template<typename T, std::size_t Maxsize>
void Stack<T, Maxsize>::pop()
{
    assert(!empty());
    --numElems;
}

template<typename T, std::size_t Maxsize>
T const& Stack<T, Maxsize>::top() const
{
    assert(!empty());
    return elems[numElems - 1];
}
