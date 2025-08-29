# ☀️ Suny Programming Language

![Build](https://img.shields.io/badge/build-passing-brightgreen)
![License](https://img.shields.io/badge/license-MIT-blue)
![Platform](https://img.shields.io/badge/platform-cross--platform-lightgrey)

**Suny** is a lightweight, free, and open-source programming language written in **C**, inspired by the simplicity of **Lua** and **Python**.  
It provides clean syntax, dynamic typing, powerful standard libraries, and a fast interpreter — ideal for **beginners**, **scripting**, and **language creators**.

---

## ✨ Features

- 🔹 Python-like clean syntax  
- 🔹 Dynamic variables & control flow  
- 🔹 First-class functions  
- 🔹 Built-in math & list support  
- 🔹 Interactive REPL + `.suny` file runner  
- 🔹 C API to embed or extend Suny  

---

## 🔨 Build from Source

### Prerequisites
- C Compiler (**GCC / Clang / MSVC**)  
- **CMake 3.12+** or GNU Make  

### Build & Run
```bash
git clone https://github.com/dinhsonhai132/Suny.git
cd Suny
make                    # build Suny
./suny                  # run repl
./suny main.suny        # run file
```

---

## 🚀 Getting Started

### Hello World
```suny
print("Hello, Suny!")
```

### Variables
```suny
let a = "hello"
print(a)
```

### Functions
```suny
function add(a, b) do
    return a + b
end

print(add(3, 5))
```

### While Loop
```suny
a = 0
while a < 5 do
    a = a + 1
    print(a)
end
```

### If Statement
```suny
x = 10
if x > 5 then
    print("bigger than 5")
end
```

### Lists
```suny
a = [1, 2, ["hello", "hi"]]
a[2][0] = "hi"
print(a)
```

## 🤝 Contributing

Contributions are welcome! 🎉  
- Fork the project  
- Create your feature branch (`git checkout -b feature/awesome`)  
- Commit changes (`git commit -m 'Add awesome feature'`)  
- Push to branch (`git push origin feature/awesome`)  
- Open a Pull Request  

---

## 📜 License

**Suny** is licensed under the [MIT License](LICENSE).  
Free to use, modify, and distribute.

---

## 👨 Author

- **YouTube**: [@haidinhson](https://www.youtube.com/@haidinhson)  
- **GitHub**: [dinhsonhai132](https://github.com/dinhsonhai132)  
- **Email**: dinhsonhai440@gmail.com  
