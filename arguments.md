Шаблоны с переменным числом аргументов

```cpp
void print_values(std::ostream & os) {}

template <class T>
void print_values(std::ostream & os, T arg) {
    os << typeid(arg).name() << ": " << arg;
}

template <class T, class... Args>
void print_values(std::ostream & os, T arg, Args... args) {
    os << typeid(arg).name() << ": " << arg << std::endl;
    print_values(os, args...);
}
```
