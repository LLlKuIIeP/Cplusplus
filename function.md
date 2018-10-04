**function** - класс для хранения указателей на функции, методы и функциональные объекты(классы с перегруженным оператором `operator()([параметры])`)

```cpp
int mult(int x, int y) {
  return x * y;
}

class InDiv {
public:
  int operator()(int x, int y) {
    return x / y;
  }
};


std::funcyion<int (int, int)> op;
if (operand == '*') {
  op = &mult;
}
else if (operand == '/') {
  op = InDiv();
}

inr res = op(7, 8);
```

```cpp
std::function<int (int, int)> op = [](int x, int y) { return x / y; };
```
