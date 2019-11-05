#include <iostream>

using namespace std;


template<size_t N>
struct Factorial
{
    static constexpr size_t value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0>
{
    static constexpr size_t value = 1;
};

template<>
struct Factorial<1>
{
    static constexpr size_t value = 1;
};


template<size_t Exp>
struct pow1
{
    double operator()(double base) const noexcept
    {
        return base * pow1<Exp - 1>{}(base);
    }
};
template<>
struct pow1<0>
{
    double operator()(double base) const noexcept
    {
        return 1.0;
    }
};
// C++17
template<size_t Exp>
struct pow17
{
    double operator()(double base) const noexcept
    {
        if constexpr (Exp == 0) {
            return  1.0;
        }
        else {
            return base * pow17<Exp - 1>{}(base);
        }
    }
};

int main()
{
    cout << Factorial<5>::value << endl;
    cout << pow1<2>{}(3) << endl;
    cout << pow17<4>{}(3) << endl;
    return 0;
}
