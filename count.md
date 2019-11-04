```cpp
#include <algorithm>
// количесво элементов в контейнере с заданным значением
template<class InputIt, class T>
difference_type count(InputIt first, InputIt last, const T &value);

template<class InputIt, class UnaryPredicate>
difference_type count(InputIt first, InputIt last, UnaryPredicate p);
```
