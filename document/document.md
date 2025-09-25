# Programming in Suny (version 1.0)

## 1. Introduction

**Suny** is a lightweight scripting language designed to be **small but powerful**, combining the minimalism and efficiency of **Lua** with the clarity and readability of **Python**.

Suny is intended to be a language that is:

* **Small** in implementation, so it is easy to understand and port.
* **Powerful** in expressiveness, so developers can solve real problems without feeling restricted.
* **Beginner-friendly**, encouraging experimentation and rapid learning.

### 1.1 Origins and Motivation

Suny was created as an experiment: *Can one person design and build a language from scratch that is both minimal and useful?*

Many modern languages are large, with complex standard libraries, heavy runtime systems, and thousands of pages of documentation. While this makes them powerful, it also makes them intimidating to beginners and difficult to fully understand.

Lua inspired Suny by showing that a small, elegant core can be extremely flexible. Python inspired Suny with its philosophy of readability and simplicity. Suny combines both ideas: a minimal implementation with a syntax that feels natural and beginner-friendly.

---

### 1.2 Philosophy of Suny

The design of Suny is guided by three principles:

1. **Simplicity**

   * The syntax is minimal, with few keywords.
   * Code should be as close to “pseudocode” as possible.

2. **Clarity**

   * Programs should be easy to read and write.
   * Indentation and structure should make logic clear at first glance.

3. **Power from smallness**

   * Instead of a large standard library, Suny focuses on a small but flexible core.
   * Advanced features can be built from simple building blocks.
   * The VM and bytecode are simple, so the language can be embedded or extended easily.

---

### 1.3 Typical Uses

Suny is not meant to replace large general-purpose languages like C++ or Java. Instead, it is designed for:

* **Learning programming concepts**: because the syntax is clean and the language is small, learners can quickly see how programming works.
* **Rapid experimentation**: with its interactive REPL, Suny encourages trial and error.
* **Scripting and automation**: Suny scripts can be written quickly to automate repetitive tasks.
* **Language research**: Suny itself is a good case study for building interpreters, compilers, and VMs.

---

### 1.4 A First Taste of Suny

Here is a simple Suny program:

```suny
print("Hello, Suny!")

i = 1
while i <= 5 do
    print("Count:", i)
    i = i + 1
end
```

This small example demonstrates Suny’s philosophy:

* Clean syntax (`while ... do ... end` is intuitive).
* No unnecessary boilerplate (no `main()` required).
* Immediate feedback in the REPL or script mode.

---

### 1.5 Implementation and Portability

Suny is written in **C**, which makes it:

* **Portable**: it can run on Windows, Linux, macOS, or even embedded devices.
* **Efficient**: compiled C code executes quickly with minimal overhead.
* **Compact**: the entire language implementation is small compared to larger interpreters.

The virtual machine (VM) of Suny executes bytecode instructions, similar to Lua or Python, but with a simplified design so it is easy to understand.

---

### 1.6 Vision for Suny

Suny will continue to evolve, but its vision will remain the same:

* Stay **small**: the core should remain lightweight and easy to understand.
* Stay **powerful**: expressive enough to build real applications.
* Stay **friendly**: a tool for both learners and curious developers who want to explore language design.

Like Lua, Suny will always value **elegance over complexity**. Like Python, it will always value **readability over clever tricks**.

In this way, Suny aims to be a language that is both a learning tool and a practical scripting solution: **a small language with big possibilities.**

# 2. Getting Started

Every programming language revolves around two fundamental concepts:

* **Input** – data provided to the program.
* **Output** – results produced by the program.

Suny follows the philosophy of being *small but powerful*: you can start writing programs immediately with very little setup, yet the language remains expressive enough for more complex projects.

---

## 2.1. Your First Program

The very first program most people write is a greeting message:

```suny
print("Hello, Suny!")
```

When executed, it produces:

```
Hello, Suny!
```

---

### Explanation

* `print` is a **built-in function** that sends output to the screen.
* `"Hello, Suny!"` is a **string literal**, which means a fixed sequence of characters enclosed in double quotes.
* In Suny, strings can contain letters, numbers, punctuation, or even Unicode characters.

This simple example already shows Suny’s core design principle: **clarity and simplicity**. With a single line of code, you can produce visible output.

---

## 2.2. More Printing Examples

The `print` function is versatile. Here are a few variations:

```suny
print(123)                  -- prints a number
print("Suny", "Language")   -- prints multiple values
print(10 + 20)              -- prints the result of an expression
print(nil)                  -- prints "nil"
```

Output:

```
123
Suny Language
30
nil
```

**Notes:**

* Unlike some languages, `print` in Suny automatically converts values to a string representation when displaying them.
* Multiple arguments are separated by a space.
* The special value `nil` represents “nothing” or “no value”.

---

## 2.3. Running Suny Programs

There are two main ways to run Suny code:

### (a) Interactive Prompt (REPL)

The **REPL** (Read–Eval–Print Loop) lets you type commands one at a time and immediately see results.

To start the prompt, open a terminal and run:

```bash
suny -p
```

Example session:

```
PS C:\Suny> suny -p
Suny 1.0  Copyright (C) 2025-present, by dinhsonhai132
Type "exit()" or press Ctrl+C to quit.
>>> print("Suny is fun!")
Suny is fun!
>>> 5 * (2 + 3)
25
>>> exit()
PS C:\Suny>
```

The REPL is ideal for **learning**, quick experiments, or testing small pieces of code.

---

### (b) Running from a File

For larger programs, it is more convenient to save your code into a file with the extension `.suny`.

Example: create a file called `main.suny` with the contents:

```suny
print("Welcome to Suny!")
```

Run it with:

```bash
PS C:\Suny> suny main.suny
Welcome to Suny!
PS C:\Suny>
```

This way, you can build reusable scripts and share them with others.

---

## 2.4. Command-Line Options

The `suny` command supports several options. To see them, type:

```bash
PS C:\Suny> suny -h
```

You will see:

```
Suny 1.0 Copyright (C) 2025-present, by dinhsonhai132
Usage: suny [options] [file]
Options:
  -c [file]   Compile the file
  -p          Run the prompt
  -h          Show this help
```

### Explanation:

* `suny file.suny` → Runs the given program file.
* `suny -p` → Starts the interactive prompt (REPL).
* `suny -c file.suny` → Compiles the file (future versions may produce bytecode or executables).
* `suny -h` → Displays the help message.

---

## 2.5. Summary

At this point, you know how to:

* Write your first Suny program.
* Display text, numbers, and expressions using `print`.
* Run code interactively in the REPL.
* Execute code stored in `.suny` files.
* Use the command-line options for Suny.

Suny programs begin simple, but the language is designed to scale as you grow. In the following sections, we will cover **basic syntax, variables, data types, and control structures**, which together form the foundation of programming in Suny.

# 3. Simple Math and Operators

Suny supports a rich set of operators for performing **arithmetic calculations**, **comparisons**, and other common tasks. These operators form the foundation for writing expressions, which are evaluated to produce values.

---

## 3.1. Arithmetic Operators

Arithmetic operators allow you to perform basic mathematical calculations.

```suny
print(2 + 3)       # Addition: 5
print(5 - 2)       # Subtraction: 3
print(4 * 2)       # Multiplication: 8
print(10 / 2)      # Division: 5.0
print((1 + 2) * 3) # Parentheses control order: 9
```

### Explanation:

* `+` adds numbers.
* `-` subtracts numbers.
* `*` multiplies numbers.
* `/` divides numbers and always produces a floating-point result (e.g., `5 / 2` → `2.5`).
* Parentheses `()` can be used to control precedence, just like in mathematics.

---

### Integer Division and Remainder

In addition to normal division, Suny provides:

```suny
print(7 // 2)  # Integer division: 3
print(7 % 2)   # Modulo (remainder): 1
```

* `//` performs **floor division**, discarding the decimal part.
* `%` returns the **remainder** after division.

---

### Exponentiation

You can raise numbers to a power with `**`:

```suny
print(2 ** 3)  # 2^3 = 8
print(9 ** 0.5) # Square root of 9 = 3.0
```

---

### Notes on Arithmetic

* Division `/` always returns a floating-point number, even if the result is mathematically an integer.
* Using `//` guarantees an integer result (rounded down).
* Exponentiation works with both integers and floats.

---

## 3.2. Comparison Operators

Comparison operators compare two values and return a **Boolean result** (`true` or `false`).

```suny
print(3 < 5)    # true
print(5 > 3)    # true
print(2 == 2)   # true
print(2 <= 3)   # true
print(5 >= 5)   # true
print(10 != 5)  # true
```

### Explanation:

* `<` → less than
* `>` → greater than
* `==` → equal to
* `<=` → less than or equal to
* `>=` → greater than or equal to
* `!=` → not equal to

---

### Comparing Different Types

In Suny, comparisons generally make sense when values are of the same type. For example:

```suny
print("apple" == "apple")   # true
print("apple" == "banana")  # false
```

Comparing numbers and strings directly is not allowed and will raise an error:

```suny
print(5 == "5")  # Error: cannot compare number and string
```

This design keeps Suny simple and predictable.

---

## 3.3. Boolean Results

The results of comparisons are Boolean values: `true` or `false`.

```suny
a = (5 > 3)
print(a)    # true

b = (10 == 2)
print(b)    # false
```

These Boolean results are often used in **if statements** and **loops** (explained in later chapters).

---

## 3.4. Operator Precedence

When multiple operators appear in the same expression, Suny follows a **precedence order**:

1. Parentheses `()`
2. Exponentiation `**`
3. Multiplication, Division, Floor Division, Modulo `* / // %`
4. Addition and Subtraction `+ -`
5. Comparisons `< > <= >= == !=`

Example:

```suny
print(2 + 3 * 4)    # 14, because * has higher precedence
print((2 + 3) * 4)  # 20, because () overrides precedence
```

---

## 3.5. Summary

In this section, you learned:

* Suny supports **basic arithmetic operators**: `+ - * / // % **`.
* Division `/` always returns a float; use `//` for integer division.
* The modulo operator `%` returns the remainder.
* **Comparison operators** return Booleans (`true`/`false`) and include `<, >, ==, !=, <=, >=`.
* Operator precedence follows standard mathematical rules.

These operators are the building blocks for expressions. Combined with variables and control structures, they allow you to perform calculations, make decisions, and write meaningful programs.

---

# 4. Variables

In programming, **variables** are like containers that hold values. Instead of writing the same number or string over and over, you can store it in a variable and use the variable’s name to refer to it. This makes your code shorter, clearer, and easier to change later.

In **Suny**, variables are simple and flexible. You don’t have to declare their type (like `int` or `float` in C). Instead, Suny figures it out automatically when you assign a value.

---

## 4.1 Global Variables

A **global variable** is a variable created outside of any function.
It can be accessed from anywhere in the program: inside functions, loops, or just at the top level.

This makes globals powerful, but also dangerous—if too many parts of your code can change the same variable, it’s easy to introduce bugs.

### Example in Suny:

```suny
a = 1  
b = 2  

print(a)  # prints 1  
print(b)  # prints 2  

b = b + 5
print(b)  # prints 7
```

### Key Points:

* A global is “visible” everywhere in the program.
* Changing it inside a function changes it for everyone else too.
* This makes programs easier to write at first, but harder to maintain in the long run.

### Comparison:

* **C/C++:** Globals must be declared outside of `main()` or any function, often with a type like `int x = 5;`.
* **Python:** Any variable defined at the top level of a file is global, but inside functions you must use `global x` if you want to modify it.
* **Lua:** All variables are global by default unless marked `local`.

In Suny, like Lua, variables are global unless you put them inside a function, where they become local.

---

## 4.2 Local Variables

A **local variable** exists only inside the function where you create it.
Once the function finishes running, the variable disappears, and you cannot access it anymore.

This is useful because it prevents different parts of the program from interfering with each other.

### Example in Suny:

```suny
function test() do  
    x = 10  
    print(x)  # prints 10  
end  

test()  
print(x)  # error: x is not defined  
```

Here, `x` is local to `test()`. Trying to use it outside gives an error.

---

### Why Locals Are Better:

* **Safety:** No other part of your program can accidentally change them.
* **Clarity:** When reading the function, you know that the variable belongs only there.
* **Memory:** Locals only live while the function is running, so they free up memory afterward.

### Good Practice:

Always prefer **local variables** unless you have a strong reason to use globals.
Globals are best for values that truly belong to the whole program, such as configuration settings or constants.

---

## 4.3 Assignment

An **assignment** means giving a variable a new value.

In Suny, this is done with the `=` operator:

```suny
a = 5
b = "hello"
c = true
```

Once assigned, you can use the variable in calculations or other expressions.

### Updating Variables

You can change a variable by reassigning it:

```suny
a = 0  
a = a + 1   # now a is 1  
a = a * 2   # now a is 2
```

### Compound Assignment

Suny also supports shorthand operators:

```suny
a = 0  
a += 1  # increase by 1  
a -= 1  # decrease by 1  
a *= 2  # multiply by 2  
a /= 2  # divide by 2  
```

These are equivalent to the longer forms:

* `a += 1` → `a = a + 1`
* `a -= 1` → `a = a - 1`
* `a *= 2` → `a = a * 2`
* `a /= 2` → `a = a / 2`

---

## 4.4 Example Program

Here’s a full program that mixes globals, locals, and assignments:

```suny
score = 0   # global variable

function add_points(points) do
    local_bonus = 2      # local variable
    score += points + local_bonus
    print("Added", points, "points. Current score:", score)
end

add_points(5)   # Added 5 points. Current score: 7
add_points(3)   # Added 3 points. Current score: 12

print(score)    # 12
print(local_bonus)  # error: local_bonus is not defined
```

---

## 4.5 Summary

* **Variables** hold values like numbers, strings, or booleans.
* **Globals** can be used anywhere but may cause conflicts if overused.
* **Locals** are safer and should be preferred.
* **Assignments** let you change a variable’s value, and compound assignments make it shorter.

Think of globals as “public” values and locals as “private” values.
If you want your code to be clean, predictable, and bug-free—use locals as much as possible.

# 5. Data Types

Suny is **dynamically typed**, meaning you don’t need to declare the type of a variable explicitly.
The type of a variable is determined automatically at runtime based on the value you assign to it.

This makes Suny flexible and expressive, while still providing a consistent set of **core data types**.

The main built-in types in Suny are:

* **Boolean** (`true`, `false`)
* **Numbers** (integers and floats)
* **Strings** (text enclosed in quotes)
* **Lists** (ordered collections of items)
* **Functions** (first-class values, both named and anonymous)

---

## 5.1 Boolean

Booleans represent **truth values**: `true` or `false`.

```suny
is_sunny = true
is_raining = false

print(is_sunny)   # true
print(is_raining) # false
```

### Boolean in Conditions

```suny
weather = "sunny"

if weather == "sunny" do
    print("Go outside!")
else
    print("Stay inside!")
end
```

Booleans are especially important in **control flow** (if/else, loops, etc.).
They can also result from **comparison operators**:

```suny
print(5 > 3)    # true
print(5 < 3)    # false
print(5 == 5)   # true
print(5 != 5)   # false
```

### Boolean Operators

| Operator | Meaning     | Example          | Result |
| -------- | ----------- | ---------------- | ------ |
| `and`    | Logical AND | `true and false` | false  |
| `or`     | Logical OR  | `true or false`  | true   |
| `not`    | Logical NOT | `not true`       | false  |

---

## 5.2 Numbers

Numbers are used for mathematics and calculations.
Suny supports **integers** (whole numbers) and **floats** (decimal numbers).

```suny
a = 10       # integer
b = -5       # integer
c = 3.14     # float
d = -0.5     # float
```

### Arithmetic Operators

| Operator | Description         | Example  | Result |
| -------- | ------------------- | -------- | ------ |
| `+`      | Addition            | `5 + 3`  | `8`    |
| `-`      | Subtraction         | `5 - 3`  | `2`    |
| `*`      | Multiplication      | `5 * 3`  | `15`   |
| `/`      | Division (float)    | `5 / 2`  | `2.5`  |
| `//`     | Floor division      | `5 // 2` | `2`    |
| `%`      | Modulus (remainder) | `5 % 2`  | `1`    |
| `**`     | Power (exponent)    | `2 ** 3` | `8`    |

### Examples

```suny
x = 10
y = 3

print(x + y)   # 13
print(x - y)   # 7
print(x * y)   # 30
print(x / y)   # 3.3333...
print(x // y)  # 3
print(x % y)   # 1
print(x ** y)  # 1000
```

### Precedence and Parentheses

Parentheses can be used to control the order of evaluation:

```suny
print(2 + 3 * 4)     # 14
print((2 + 3) * 4)   # 20
```

---

## 5.3 Strings

Strings represent **text**.
They are sequences of characters enclosed in **double quotes** `" "` or **single quotes** `' '`.

```suny
name = "Dinh Son Hai"
greeting = 'Hello, world!'

print(name)     # Dinh Son Hai
print(greeting) # Hello, world!
```

### String Operations

```suny
first = "Hello"
second = "World"
combined = first + " " + second

print(combined)      # Hello World
print(size(combined)) # 11
```

Strings can be compared:

```suny
print("abc" == "abc")  # true
print("abc" != "def")  # true
```

### Strings in Conditions

```suny
password = "1234"

if password == "1234" do
    print("Access granted")
else
    print("Access denied")
end
```

### Escape Characters

| Escape | Meaning      | Example             | Output         |
| ------ | ------------ | ------------------- | -------------- |
| `\n`   | Newline      | `"Hello\nWorld"`    | Hello<br>World |
| `\t`   | Tab          | `"Col1\tCol2"`      | Col1    Col2   |
| `\\`   | Backslash    | `"C:\\Path\\File"`  | C:\Path\File   |
| `\"`   | Double quote | `"He said: \"Hi\""` | He said: "Hi"  |
| `\'`   | Single quote | `'It\'s sunny'`     | It's sunny     |

---

## 5.4 Lists

Lists are **ordered collections** that can hold multiple items, even of different types.

```suny
numbers = [1, 2, 3, 4, 5]
names = ["Alice", "Bob", "Charlie"]
mixed = [1, "Two", true, 4.5]
```

### Accessing and Modifying Items

```suny
print(numbers[0])  # 1
numbers[0] = 10
print(numbers[0])  # 10
```

### Adding and Removing Items

```suny
push(numbers, 6)   # append
pop(numbers)       # remove last item
```

### Length of a List

```suny
print(size(numbers))  # 5
```

### Looping Over Lists

```suny
fruits = ["apple", "banana", "cherry"]

# Using index
for i in range(size(fruits)) do
    print(fruits[i])
end

# Using element directly
for fruit in fruits do
    print(fruit)
end
```

---

## 5.5 Functions

Functions in Suny are **first-class values**:
They can be assigned to variables, passed as arguments, returned, and even created anonymously.

---

### 5.5.1 Basic Function

```suny
function add(a, b) do
    return a + b
end

print(add(1, 2))  # 3
```

---

### 5.5.2 Higher-Order Functions

Functions can take other functions as arguments:

```suny
function apply(func, x, y) do
    return func(x, y)
end

print(apply(add, 5, 7))  # 12
```

---

### 5.5.3 Inner Functions

Functions can be nested:

```suny
function foo() do
    function bar() do
        print("This is bar")
    end
    return bar()
end

foo()  # Output: This is bar
```

---

### 5.5.4 Anonymous Functions

```suny
a = 10

getA = function() do
    return a
end

print(getA())  # 10
```

You can also call them immediately:

```suny
print(function() do
    return 42
end())   # 42
```

---

### 5.5.5 Lambda Functions

A **lambda** is a short form of anonymous function:

```suny
let f(x) = x + 1
print(f(2))  # 3
```

---

### 5.5.6 Special Local Variable: `self`

Inside a function, the special variable `self` always refers to that **function itself**.

```suny
function foo() do
    return self
end

anon = function() do
    return self
end
```

This makes recursion and self-reference easy, even without naming the function.

---

### 5.5.7 Example: Closure

```suny
function foo() do
    count = 0
    return function() do
        count = count + 1
        return count
    end
end

a = foo()
for i in range(10) do
    print(a())
end
```

**Output:**

```
1
2
3
4
5
6
7
8
9
10
```

---

## 5.5 Summary

* Booleans → true/false
* Numbers → integers & floats with `+ - * / // % **`
* Strings → text with escape sequences
* Lists → ordered collections with indexing and iteration
* Functions → first-class values, support closures, anonymous functions, and lambdas

# 7. Control Structures

Control structures determine the **flow of execution** in a program.
They allow you to make decisions, repeat actions, and handle complex logic.

Suny provides these main control structures:

* **Conditional Statements** (`if`, `elif`, `else`)
* **Loops** (`while`, `for`)
* **Special Controls** (`break`, `continue`)

---

## 7.1 Conditional Statements

Conditional statements let your program choose between different paths.

### 7.1.1 Basic `if`

```suny
score = 75

if score >= 50 do
    print("You passed!")
end
```

➡ If the condition is `true`, the code inside the block runs.
➡ If it is `false`, the block is skipped.

---

### 7.1.2 `if ... else`

```suny
score = 40

if score >= 50 do
    print("You passed!")
else
    print("Try again")
end
```

If the first condition fails, the `else` block executes.

---

### 7.1.3 `if ... elif ... else`

You can chain multiple conditions with `elif` (short for *else if*).

```suny
score = 85

if score >= 90 do
    print("Excellent")
elif score >= 75 do
    print("Good job")
elif score >= 50 do
    print("You passed")
else
    print("Failed")
end
```

✅ Conditions are checked from top to bottom.
✅ Only the **first matching block** is executed.

---

### 7.1.4 Nested Conditions

Conditions can be placed inside each other:

```suny
age = 20
has_id = true

if age >= 18 do
    if has_id do
        print("Access granted")
    else
        print("ID required")
    end
else
    print("Too young")
end
```

---

### 7.1.5 Comparison Operators Recap

| Operator | Meaning                  | Example  | Result |
| -------- | ------------------------ | -------- | ------ |
| `==`     | Equal                    | `5 == 5` | true   |
| `!=`     | Not equal                | `5 != 3` | true   |
| `>`      | Greater than             | `5 > 3`  | true   |
| `<`      | Less than                | `3 < 5`  | true   |
| `>=`     | Greater than or equal to | `5 >= 5` | true   |
| `<=`     | Less than or equal to    | `4 <= 5` | true   |

---

### 7.1.6 Boolean Logic in Conditions

```suny
temperature = 30
sunny = true

if temperature > 25 and sunny do
    print("Perfect beach day")
end

if temperature < 10 or not sunny do
    print("Maybe stay home")
end
```

---

## 7.2 Loops

Loops let you **repeat code** multiple times.

---

### 7.2.1 `while` Loop

Repeats while the condition is `true`.

```suny
count = 0

while count < 5 do
    print(count)
    count = count + 1
end
```

**Output:**

```
0
1
2
3
4
```

---

### 7.2.2 Infinite `while`

```suny
while true do
    print("Running forever...")
end
```

➡ You usually combine this with `break` to stop.

---

### 7.2.3 `for ... in range()`

Suny provides `range(n)` to generate numbers from `0` to `n-1`.

```suny
for i in range(5) do
    print(i)
end
```

**Output:**

```
0
1
2
3
4
```

You can also use `range(start, end)`:

```suny
for i in range(3, 7) do
    print(i)
end
# 3, 4, 5, 6
```

---

### 7.2.4 `for ... in list`

Iterating over items directly:

```suny
fruits = ["apple", "banana", "cherry"]

for fruit in fruits do
    print(fruit)
end
```

**Output:**

```
apple
banana
cherry
```

---

### 7.2.5 Nested Loops

```suny
for i in range(3) do
    for j in range(2) do
        print("i =", i, ", j =", j)
    end
end
```

---

## 7.3 Loop Control: `break` and `continue`

### 7.3.1 `break`

Stops the loop immediately.

```suny
for i in range(10) do
    if i == 5 do
        break
    end
    print(i)
end
```

**Output:** `0 1 2 3 4`

---

### 7.3.2 `continue`

Skips to the next iteration.

```suny
for i in range(5) do
    if i == 2 do
        continue
    end
    print(i)
end
```

**Output:** `0 1 3 4`

---

## 7.4 Combining Control Structures

Complex programs often use **if statements inside loops**:

```suny
for i in range(1, 11) do
    if i % 2 == 0 do
        print(i, "is even")
    else
        print(i, "is odd")
    end
end
```

---

## 7.5 Summary

* `if`, `elif`, `else` → decision making
* `while` → repeat while condition is true
* `for` → iterate over ranges or collections
* `break` → exit loop early
* `continue` → skip current iteration

Control structures are the **backbone of logic** in Suny.
They allow you to model real-world decisions, repeat tasks, and build dynamic programs.

---

# 8. Include

The **`include`** statement in Suny allows you to organize your program across multiple files or folders.
Instead of writing everything in a single file, you can split your code into smaller parts (modules, configs, helpers) and bring them together when needed.

When Suny sees an `include`, it **inserts the code from that file or folder directly into the current file** before running the program.
This makes it behave almost the same as if you had copy-pasted the contents manually, but in a more organized way.

---

## 8.1 Including a File

If the target is a **file**, Suny copies all its contents.

```suny
# config.suny
pi = 3.14
```

```suny
# main.suny
include "config"

print(pi)   # 3.14
```

Here, the variable `pi` becomes part of `main.suny`’s scope, as if it was defined inside it.

---

## 8.2 Including a Folder

If the target is a **folder**, Suny automatically looks for a file named `main.suny` inside that folder.

```
math/
 ├── main.suny
 └── extra.suny
```

```suny
# math/main.suny
square(x) = x * x
```

```suny
# main.suny
include "math"

print(square(5))   # 25
```

Suny only loads `math/main.suny` by default.
If you need extra files (`extra.suny` in this example), you must include them explicitly:

```suny
include "math/extra"
```

---

## 8.3 Search Paths

Suny resolves includes in this order:

1. **Current directory** – looks for a file or folder in the same place as the current `.suny` file.

2. **Library directory** – if not found locally, Suny searches in the global library folder:

   ```
   C:/Suny/libs
   ```

   Example:

   ```
   C:/Suny/libs/
     └── std/
          └── main.suny
   ```

   ```suny
   include "std"
   ```

   This would load the standard library `std/main.suny`.

3. **Error** – if nothing is found, Suny throws a compilation error.

---

## 8.4 Error Cases

* **Missing file or folder**

  ```suny
  include "not_found"
  ```

  ```
  Error: include target 'not_found' not found
  ```

* **Folder without main.suny**

  ```
  mylib/
    └── helper.suny
  ```

  ```suny
  include "mylib"
  ```

  ```
  Error: no main.suny in folder 'mylib'
  ```

* **Name conflicts**

  ```suny
  # a.suny
  x = 10

  # b.suny
  x = 20
  ```

  ```suny
  include "a"
  include "b"

  print(x)   # which one? result depends on last include
  ```

  Best practice: avoid re-using the same global variable names across includes.

---

## 8.5 Summary

* Use `include` for **constants, small configs, or utility functions**.
* Keep each folder/module self-contained with its own `main.suny`.
* Avoid circular includes (`A` includes `B`, and `B` includes `A`).
* Use unique variable/function names to prevent conflicts.
