<h1 align="center">C++</h1>
Туториалы OpenGL:
</br>[Находки в сети за август 2015 по OpenGL](http://eax.me/links-issue-31/ "Записки программиста")

**[\<type_traits>](type_trains.md)** - поддержка типов<br>
**[decltype](decltype.md)** - оператор decltype<br>
**[arguments](arguments.md)** - переменное число параметров<br>
**[\<function>](function.md)** - указатели на функции<br>
**[constexpr](constexpr.md)** - константы компиляции<br>
**[\<any>](any.md)** - если ли элементв в контейнере<br>
**[\count](count.md)** - количесво элементов<br>
```
#include <type_traits>
#define DECLARE_has(FIELD)\
template<typename T>\
struct has_##FIELD\
{\
    template<typename U, typename = decltype(U::FIELD)>\
    static std::true_type   check(int);\
    
    template<typename U>\
    static std::false_type  check(long);\
\
    using value = decltype(check< T >(0));\
};

struct x {};
struct y { int jopa; };

DECLARE_has(jopa)

static_assert(std::is_same_v<has_jopa<y>::value, std::true_type>);
static_assert(std::is_same_v<has_jopa<x>::value, std::false_type>);
```


optional
```
std::optional<int> foo()
{

    return std::optional {1}; // std::nullopt;
}

auto opt = foo();
if(opt) {
}
else /*nullopt*/{
}

//задать дефолтное значение auto res = opt.value_or({});

```
