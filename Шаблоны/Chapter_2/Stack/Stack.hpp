#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cassert>


// для объявления дружественной вне класса
template<typename T>
class Stack;
template<typename T>
std::ostream& operator<<(std::ostream& strm, Stack<T> const& s);
// ----


template<typename T>
class Stack
{
private:
    std::vector<T> elems;
    static_assert(std::is_default_constructible_v<T>, "Класс Stack требует элементы, конструируемые по умолчпию");

public:
    // внутри можно без параметра шаблона
    Stack() = default;
    Stack(Stack const& lhs) : elems(lhs) {}
    Stack& operator=(Stack const& lhs) { elems = lhs.elems; }

    void push(T const& elem) { elems.push_back(elem); }
    T pop();
    T const& top() const;
    bool empty() const { return elems.empty(); }

    // operators
    bool operator==(Stack const& lhs) { return elems == lhs.elems; }
    // обычная, не шаблонная функция, инстанцируемая при необходимости
    friend std::ostream& operator<<(std::ostream& strm, Stack<T> const& s) { s.printOn(strm); return strm; }
    // объявления вне класса через отдельную шаблонную функцию, поэтому параметр шаблона отличный от Т
    template<typename U>
    friend std::ostream& operator<<(std::ostream& strm, Stack<U> const& s);
    // параметр шаблона выступает как спецаялизация, но для этого нужно предварительное объявление
    friend std::ostream& operator<< <T>(std::ostream& strm, Stack<T> const& s); // параметр Т после оператора означает специализацию шаблона
    void printOn(std::ostream& strm) const noexcept;
};

// вывод определенного типа
Stack(char const*) -> Stack<std::string>;

template<typename T>
std::ostream& operator<<(std::ostream& strm, Stack<T> const& s)
{
    s.printOn(strm);
    return strm;
}

template<typename T>
T Stack<T>::pop()
{
    assert(!elems.empty());
    T elem = elems.back();
    elems.pop_back();
    return elem;
}

template<typename T>
T const& Stack<T>::top() const
{
    assert(!elems.empty());
    return elems.back();
}

template<typename T>
void Stack<T>::printOn(std::ostream& strm) const noexcept
{
    for(T const& elem : elems) {
        strm << elem << ' ';
    }
}
