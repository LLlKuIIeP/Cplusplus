Оператор, который выводит тип, основываясь на выражении справа от равенства и добавляет `const &`<br>

```cpp
decltype([выражение]) [имя] = [элемент];
```

Ключевое слово `auto` обрезает внешнюю часть, т.е. `const &`

```cpp
array<T, N> arr;

for (size_t i = 0; i < N; ++i) {

  //копия
  auto elem = arr[i]; // в elem будет копия arr[i]

  //ссылка
  decltype(arr[0]) d_elem = arr[i]; // в d_elem будет ссылка const &arr[i]
}
```

```cpp
T a;
decltype(a) b = a; // в b будет типа T
decltype((a)) c = a; // в c будет типа T &
```
