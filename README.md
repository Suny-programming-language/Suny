# ☀️ Suny programming language ☀️

**Suny** is a lightweight, free, and open-source programming language written in C, inspired by the simplicity of Lua and Python. It provides clean syntax, dynamic typing, powerful standard libraries, and a fast interpreter — ideal for beginners and language creators alike.

---

## 🚀 Features

- 🔹 Python-like clean syntax
- 🔹 First-class functions
- 🔹 Built-in math & list support
- 🔹 Dynamic variables and control flow
- 🔹 Interactive REPL + `.suny` file runner
- 🔹 C++ API to embed or customize **Suny**

---

## 🔨 Build from source

- 🔹 Download the repository
- 🔹 Navigate to the `Suny-main` folder
- 🔹 run `make` to build `./bin/suny`

---

## ⚙️ Getting Started

**Prerequisites**

* C Compiler (MSVC / GCC / Clang)
* CMake 3.12+

**Running Suny**

```
suny main.suny          # run .suny file
```

## 🧠 Syntax Guide

**Output**
```
print("hello " + "world")
```


**Variable**
```
let a = "hello"
print(a)
```

**Function**
```
function add(a, b) do
    return a + b
end
```

**while loop**
```
a = 0
while a < 100 do
    a = a + 1
    print(a)
end
```

**if statement**
```
a = [1, 2, 3]
if size(a) == 3 then
    print("yes")
end
```

**list**
```
a = [1, 2, ["hello", "hi"]]
a[2][0] = "hi"
print(a)
```

**for loop**
```
for i in range(0, 1000) do
    print(i)
end
```

## Credit 👨

**My youtube: https://www.youtube.com/@haidinhson** 

**My Github: https://github.com/dinhsonhai132**

**My gmail: dinhsonhai440@gmail.com**