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

int main()
{


    cout << Factorial<5>::value << endl;
    return 0;
}
