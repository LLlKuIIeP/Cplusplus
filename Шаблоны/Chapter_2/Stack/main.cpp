#include <iostream>
#include <vector>
#include <cassert>


template<typename T>
class Stack
{
private:
    std::vector<T> elems;

public:
    // внутри можно без параметра шаблона
    Stack(Stack const& lhs) : elems(lhs) {}
    Stack& operator=(Stack const& lhs)
    {
        elems = lhs.elems;
    }

    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const
    {
        return elems.emoty();
    }
};

template<typename T>
void Stack<T>::push(T const& elem)
{
    elems.push_back(elem);
}
template<typename T>
void Stack<T>::pop()
{
    assert(!elems.empty());
    elems.pop_back();
}
template<typename T>
T const& Stack<T>::top() const
{
    assert(!elems.empty());
    return elems.back();
}


int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}
