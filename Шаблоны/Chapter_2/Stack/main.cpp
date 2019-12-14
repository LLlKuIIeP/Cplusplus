#include <iostream>
#include <Stack.hpp>


int main()
{
    std::cout << "Hello World!" << std::endl;

    Stack<double> s1;
    Stack<double> s2;
    void(s1 == s2);

    s1.push(1.);
    s1.printOn(std::cout);
    std::cout << std::endl;

    s2.push(2.);
    std::cout << s2 << std::endl;

    return 0;
}
