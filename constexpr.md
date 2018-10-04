**constexpr** - вычисляет константы и функции на этапе компиляции

Константы<br>
```cpp
constexpr double earth_gravity = 9.8;
constexpr double moon_gravity = earth_gravity / 6;
```

Функции<br>
```cpp
constexpr int pow(int x, int n) {
  return n == 1 ? 1 : x * pow(x, n - 1);
}

int N = pow(3, 5);
```

Ограничения на функции:<br>
- внутри `constexpr` функции нельзя вызывать не `constexpr` функции
- тело функции должно быть из единого `return`, после него может быть выражение
- можно и к методам класса, только если те можно вычислить на этапе компиляции
