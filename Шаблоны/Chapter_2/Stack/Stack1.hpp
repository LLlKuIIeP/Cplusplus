/// 2.5
#pragma once
#include <deque>
#include <string>
#include <cassert>
#include <Stack.hpp>


// Частичная специализация для std::string с контейнером std::deque
template<>
class Stack<std::string>
{
private:
    std::deque<std::string> elems;
public:
    void push(std::string const&);
    void pop();
    std::string const& top() const;
    bool empty() const
    {
        return elems.empty();
    }
};

void Stack<std::string>::push(std::string const& elem)
{
    elems.push_back(elem);
}

void Stack<std::string>::pop()
{
    assert(!elems.empty());
    elems.pop_back();
}

std::string const& Stack<std::string>::top() const
{
    assert(!elems.empty());
    return elems.back();
}
