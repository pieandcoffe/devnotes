# Assignment 1 — Data, Memory, and Predictable C++

**Estimated time:** 6–12 hours  
**Total:** 100 points  
**Language:** C++20  
**Compiler:** Clang (`clang++`)

## Purpose

This assignment consolidates the material from Classes 01–11. You will work with fundamental types, expressions, control flow, functions, arrays, pointers, references, dynamic memory, `const`, casts, compiler diagnostics, and sanitizers.

The assignment has three parts:

1. a small command-line data analyzer;
2. independent debugging exercises;
3. conceptual questions answered in your `README.md`.

You are expected to combine the covered concepts rather than reproduce isolated examples from the notes.

## Learning objectives

After completing this assignment, you should be able to:

- choose appropriate integral and floating-point types;
- separate declarations, definitions, and responsibilities between functions;
- use pointers and pointer arithmetic only within valid array bounds;
- use references when a function must modify an existing object;
- apply `const` to communicate and enforce read-only access;
- allocate and release dynamic arrays correctly;
- distinguish compile-time errors, runtime failures, undefined behavior, unspecified behavior, and memory leaks;
- use explicit casts where a conversion should be visible;
- compile a multi-file C++20 program with strict warnings;
- use sanitizers to detect memory and undefined-behavior defects.

---

# Part A — Dataset Analyzer (60 points)

Write a command-line program that reads a sequence of integers, computes statistics, transforms the sequence, and prints a report.

## A.1 Input format

Read input from standard input (`std::cin`).

The first value is `n`, the number of integers in the dataset. The next `n` values are the dataset.

```text
n
value_1 value_2 ... value_n
```

Requirements for `n`:

- `1 <= n <= 100000`;
- use an unsigned size type suitable for indexing and object sizes;
- reject missing, zero, or excessively large sizes without allocating the array.

If the size or any dataset value cannot be read, print

```text
error: invalid input
```

to `std::cerr` and return a non-zero exit code.

## A.2 Storage requirements

Store the primary dataset in a dynamically allocated array created with `new[]`.

You must:

- allocate the array only after validating `n`;
- release it exactly once with `delete[]`;
- avoid memory leaks on every exit path after allocation;
- never access an element outside `[0, n)`;
- not use `malloc`, `calloc`, `realloc`, or `free`;
- not use `std::vector` as a replacement for the required dynamic array.

Standard containers may be used where explicitly permitted below.

## A.3 Required functions

Implement at least the following functions. You may add helper functions when they improve clarity.

```cpp
bool read_values(int* data, std::size_t size);

const int* find_min(const int* begin, const int* end);
const int* find_max(const int* begin, const int* end);

long long calculate_sum(const int* begin, const int* end);
double calculate_mean(const int* begin, const int* end);

void swap_values(int& lhs, int& rhs);
void reverse_values(int* begin, int* end);

bool is_negative(int value);
bool is_even(int value);

std::size_t count_if(
    const int* begin,
    const int* end,
    bool (*predicate)(int)
);

void print_values(const int* begin, const int* end);
```

The range `[begin, end)` includes the value pointed to by `begin` and excludes the value pointed to by `end`.

### Function requirements

- `find_min` and `find_max` must return a pointer to an element in the original array. They must not return a pointer or reference to a local variable.
- `calculate_sum` must accumulate into `long long`, not `int`.
- `calculate_mean` must perform floating-point division. Make the integral-to-floating conversion explicit with `static_cast`.
- `swap_values` must modify its arguments through references.
- `reverse_values` must reverse the array in place and must call `swap_values`.
- `count_if` must call the supplied function through the function pointer. Do not duplicate separate counting loops for negative and even values.
- Functions that only inspect data must accept pointers to `const` data.
- Do not use `const_cast`, `reinterpret_cast`, or C-style casts.

You may assume that the required range-processing functions receive a non-empty valid range from `main`.

## A.4 Frequency table

Build a frequency table for the original values using:

```cpp
std::map<int, std::size_t>
```

Print one line per distinct value in ascending key order. The frequency table must describe the original dataset. Reversing the array does not change its frequencies.

## A.5 Required report

Print the following fields in this exact order:

```text
count: <number of values>
min: <minimum value>
max: <maximum value>
sum: <sum>
mean: <mean with exactly three digits after the decimal point>
negative: <number of negative values>
even: <number of even values>
reversed: <values in reverse order, separated by one space>
frequencies:
<value>: <frequency>
...
```

Use the appropriate tools from `<iomanip>` to print the mean with exactly three digits after the decimal point.

Do not print prompts such as `Enter n:`. Prompts make automated testing unnecessarily difficult.

## A.6 Example 1

Input:

```text
8
5 -2 5 8 0 -2 7 4
```

Expected output:

```text
count: 8
min: -2
max: 8
sum: 25
mean: 3.125
negative: 2
even: 5
reversed: 4 7 -2 0 8 5 -2 5
frequencies:
-2: 2
0: 1
4: 1
5: 2
7: 1
8: 1
```

## A.7 Example 2

Input:

```text
1
-7
```

Expected output:

```text
count: 1
min: -7
max: -7
sum: -7
mean: -7.000
negative: 1
even: 0
reversed: -7
frequencies:
-7: 1
```

## A.8 Invalid-input examples

Each of the following inputs must fail cleanly without allocation leaks:

```text
0
```

```text
100001
```

```text
3
10 x 30
```

Expected error text:

```text
error: invalid input
```

## A.9 Source organization

Organize Part A into at least two translation units:

- `main.cpp` — input validation, allocation ownership, report coordination, and cleanup;
- `analysis.cpp` — definitions of the required analysis and transformation functions.

You may add `analysis.hpp` for shared declarations. If you do, include it in both translation units and use an include guard or `#pragma once`. Do not include one `.cpp` file from another `.cpp` file.

---

# Part B — Debugging Clinic (25 points)

For each case below:

1. classify the primary defect;
2. explain why it occurs in one to three sentences in `README.md`;
3. write a corrected version in `debugging.cpp`;
4. preserve the apparent intent of the original code.

Your classifications should use the most precise applicable term, such as:

- compile-time error;
- undefined behavior;
- memory leak;
- unspecified evaluation order;
- well-defined but logically incorrect behavior.

Place each correction in a separate function named `debug_case_1` through `debug_case_5`. The file does not need its own `main` function.

## Case 1 — A returned reference

```cpp
const int& larger(int a, int b) {
    int result = a > b ? a : b;
    return result;
}
```

Preserve the intent: return the larger value safely.

## Case 2 — Cleanup

```cpp
void cleanup() {
    int* first = new int(10);
    int* second = new int(20);

    std::cout << *first + *second << '\n';
    delete first, second;
}
```

Preserve the intent: print the sum and release both allocations.

## Case 3 — Pointer constness

```cpp
void reset(const int* value) {
    *value = 0;
}
```

Preserve the intent: allow the function to reset a non-constant integer supplied by the caller. Do not use a cast.

## Case 4 — Lost array size

```cpp
void print_all(const int values[]) {
    const std::size_t size = sizeof(values) / sizeof(values[0]);

    for (std::size_t i = 0; i < size; ++i) {
        std::cout << values[i] << '\n';
    }
}
```

Preserve the intent: print every element of an array. Make the size available to the function explicitly.

## Case 5 — Side effects and evaluation order

```cpp
int combine() {
    int value = 1;
    return value++ + ++value;
}
```

Preserve the intended left-to-right calculation by separating the side effects into clearly ordered statements. In your explanation, distinguish evaluation order from operator precedence.

---

# Part C — Written Reasoning (15 points)

Answer the following questions in `README.md`. Aim for precise explanations rather than long essays. Include small code fragments where useful.

Each question is worth 2.5 points.

1. Why is `std::size_t` appropriate for the dataset size, while `long long` is more appropriate for its sum? Mention one risk of mixing signed and unsigned arithmetic.
2. Explain the difference among `const int*`, `int* const`, and `const int* const`.
3. Why do arrays passed as function parameters not retain their array size? Relate your answer to array-to-pointer conversion.
4. Compare pass-by-value, pass-by-pointer, pass-by-reference, and pass-by-`const`-reference. Give one appropriate use case for each.
5. Describe the four build stages from source file to executable: preprocessing, compilation, assembling, and linking. At which stage would an unresolved function definition normally be reported?
6. Explain how AddressSanitizer and UndefinedBehaviorSanitizer help with this assignment. Give one defect each sanitizer may detect, and explain why passing sanitizer checks does not prove that a program is correct.

---

# Build and validation requirements

## Build Part A

From the submission directory, your program must compile with:

```sh
clang++ -std=c++20 -Wall -Wextra -Wpedantic -Werror main.cpp analysis.cpp -o analyzer
```

Run it with:

```sh
./analyzer
```

## Build with sanitizers

Your program must also compile with:

```sh
clang++ -std=c++20 -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined main.cpp analysis.cpp -o analyzer_san
```

Run all normal and invalid-input tests with the sanitizer build:

```sh
./analyzer_san
```

If your platform supports leak detection through AddressSanitizer, verify that no leaks are reported. Record the compiler version, commands, test inputs, and sanitizer result in `README.md`.

## Compile Part B

`debugging.cpp` must compile independently as an object file:

```sh
clang++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -c debugging.cpp
```

A successful build is necessary but not sufficient: your corrections must also remove the underlying defects.

---

# Submission structure

Submit one directory with the following files:

```text
assignment1/
├── main.cpp
├── analysis.cpp
├── analysis.hpp       # optional but recommended
├── debugging.cpp
└── README.md
```

Do not submit executables, object files, sanitizer output files, or editor-specific build directories.

## Required `README.md` contents

Your README must contain:

1. your name;
2. a short description of your program;
3. exact build and run commands;
4. a list of tests you performed, including edge and invalid inputs;
5. the result of your sanitizer run;
6. the five Part B classifications and explanations;
7. answers to all six Part C questions;
8. any known limitations.

---

# Constraints and code quality

- Use only C++20 standard-library facilities.
- The submitted program must compile without warnings under the required flags.
- Initialize every variable before reading its value.
- Do not rely on undefined behavior or implementation-specific type sizes.
- Do not use global mutable variables.
- Do not use `goto`.
- Do not use C-style casts, `reinterpret_cast`, or `const_cast`.
- Do not replace the required pointer, reference, dynamic-array, or function-pointer work with higher-level alternatives.
- Prefer readable statements over expressions containing several side effects.
- Use meaningful names and consistent formatting.
- Comments should explain decisions or non-obvious constraints, not restate every line.

Use of standard algorithms is allowed only where it does not bypass a required implementation. In particular, do not replace `find_min`, `find_max`, `count_if`, `swap_values`, or `reverse_values` with standard-library equivalents.

---

# Grading rubric

## Part A — Dataset Analyzer: 60 points

| Criterion | Points |
| --- | ---: |
| Correct input parsing, size validation, and error behavior | 7 |
| Correct dynamic allocation and `delete[]` cleanup on all paths | 8 |
| Correct pointer-range implementation of minimum and maximum | 6 |
| Correct `long long` sum and floating-point mean | 6 |
| Correct reference-based swap and in-place reversal | 6 |
| Correct function-pointer-based negative/even counting | 6 |
| Correct ordered frequency table using `std::map` | 5 |
| Exact report structure and correct results for edge cases | 6 |
| Appropriate `const`, types, casts, and bounds-safe pointer use | 5 |
| Multi-file organization, readability, and warning-free build | 5 |
| **Subtotal** | **60** |

## Part B — Debugging Clinic: 25 points

Each case is worth 5 points:

- 2 points for accurate classification and explanation;
- 3 points for a safe correction that preserves intent.

| Criterion | Points |
| --- | ---: |
| Five classifications and explanations | 10 |
| Five correct, compiling repairs | 15 |
| **Subtotal** | **25** |

## Part C — Written Reasoning: 15 points

| Criterion | Points |
| --- | ---: |
| Six accurate and concise answers | 15 |
| **Subtotal** | **15** |

## General deductions

The following deductions may be applied across the relevant rubric categories:

- code does not compile with the required Clang command: up to **−25**;
- warnings under the required flags: up to **−10**;
- sanitizer-detected invalid memory access, undefined behavior, or leak: up to **−15**;
- missing `README.md` sections: up to **−10**;
- prohibited cast or replacement of a required technique: points for that requirement receive no credit.

A submission cannot receive full credit merely because it reproduces the sample output. It must also work for additional valid, boundary, duplicate-heavy, all-negative, and malformed inputs.

---

# Hints

These hints are intentionally directional; they are not a solution.

- For a dynamic array `data` of length `size`, the half-open range is `[data, data + size)`.
- A pointer returned by `find_min` or `find_max` can be dereferenced by the caller after checking that the range was non-empty.
- Think carefully about the loop condition for in-place reversal. Avoid forming or dereferencing a pointer before the beginning of the array.
- Integer division occurs before assignment to `double` unless at least one operand is converted before the division.
- `delete first, second;` is parsed using the comma operator; it is not shorthand for two `delete` expressions.
- When an array parameter appears as `T values[]`, the parameter is adjusted to a pointer type.
- Build the frequency table before or after reversal—the frequencies are identical—but print the required statistics consistently.
- During development, test the smallest valid dataset before testing large inputs.

No reference solution is included in the student assignment. Your implementation and explanations are part of the assessed work.
