#include <iostream>

template<typename T>
struct MyClass;     // первичный шаблон
template<typename T, std::size_t SZ>
struct MyClass<T[SZ]>   // частичная специализация для массивов с известными границами
{
    static void print()
    {
        std::cout << "print() для T[" << SZ << "]\n";
    }
};

template<typename T, std::size_t SZ>
struct MyClass<T(&)[SZ]>    // частичная специализация для ссылок на массив с известными границами
{
    static void print()
    {
        std::cout << "print() для T(&)[" << SZ << "]\n";
    }
};

template<typename T>
struct MyClass<T[]>     // частичная специализация для массива с неизвестными границами
{
    static void print()
    {
        std::cout << "print() для T[]\n";
    }
};

template<typename T>
struct MyClass<T(&)[]>      // частичная специализация для ссылок на массив с неизвестными границами
{
    static void print()
    {
        std::cout << "print() для T(&)[]\n";
    }
};

template<typename T>
struct MyClass<T*>      // частичная специализация для указателей
{
    static void print()
    {
        std::cout << "print() для T*\n";
    }
};

template<typename T1, typename T2, typename T3>
void foo(
        int a1[7], int a2[],    // указатели по правилам языка
        int (&a3)[42],          // ссылка на массив с известными границами
        int(&x0)[],             // ссылка на массив с неизвестными границами
        T1 x1,                  // передача по значению с низведением
        T2& x2, T3&& x3         // передача по ссылке
        )
{
    MyClass<decltype (a1)>::print();    // MyClass<T*>
    MyClass<decltype (a2)>::print();    // MyClass<T*>
    MyClass<decltype (a3)>::print();    // MyClass<T(&)[SZ]>
    MyClass<decltype (x0)>::print();    // MyClass<T(&)[]>
    MyClass<decltype (x1)>::print();    // MyClass<T*>
    MyClass<decltype (x2)>::print();    // MyClass<T(&)[]>
    MyClass<decltype (x3)>::print();    // MyClass<T(&)[]>
}


int main()
{
    int a[42];
    MyClass<decltype (a)>::print();     // MyClass<T[SZ]>
    extern int x[];
    MyClass<decltype (x)>::print();    // MyClass<T[]>

    foo(a, a, a, x, x, x, x);
    //cout << "Hello World!" << endl;
    return 0;
}

int x[] = {0, 8, 15};
