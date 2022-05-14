# functional-cpp
Header-only tools for functional programming in C++

It provides the following features:

---

### Partial function application

```cpp
int add(int a, int b) {
  return a + b;
}
  
// ...

const auto add2 = partial::apply(add, 2);
const auto five = add2(3);
```

---

### Optional values with `Option`
It exposes two variants, `Some(T)` and `None`.

Usage:
```cpp
using option::Option;
using option::Some;
using option::None;

const Option<int> some_opt = Some(42);
const Option<int> none_opt = None;

const auto mapped_opt = some_opt.map(Map(x, x*2)); // Some(84)

const auto some_value = some_opt.value();
const auto none_value = none_opt.value_or(42);

auto divide(int a, int b) -> Option<int> {
  return (b != 0) ? Some(a/b) : None;
}
```

---

### Error handling with `Result`
`Result<T, U>` represents the result of an operation that can fail. It exposes two variants, `Ok(T)` and `Err(U)`.

Usage:
```cpp
using result::Result;
using result::Ok;
using result::Err;

auto foo() -> Result<int, bool> {
  return Ok(42);
}

auto bar() -> Result<int, bool> {
  return Err(false);
}
```

