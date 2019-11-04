```cpp
// true если все элементы последовательности удовлетворяют условию
template<class InputIt, class UnaryPredicate>
bool all_of(InputIt first, InputIt last, UnaryPredicate p);

// true если хотябы один элемент последовательности удовлетворяют условию
template<class InputIt, class UnaryPredicate>
bool any_of(InputIt first, InputIt last, UnaryPredicate p);

// true если ниодин элемент последовательности не удовлетворяют условию
template<class InputIt, class UnaryPredicate>
bool none_of(InputIt first, InputIt last, UnaryPredicate p);
```
