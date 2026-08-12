1. Why is `std::size_t` appropriate for the dataset size, while `long long` is more appropriate for its sum? Mention one risk of mixing signed and unsigned arithmetic.
    - `std::size` capable to index every value in dataset of any length. 
    - sum arithmetic should be done on `long long` type, 
      - even if each individual value fits in an int, summing many of them (e.g. 100,000 values near INT_MAX) can overflow an int accumulator, 
      - while long long's much larger range makes that overflow effectively impossible for realistic input sizes.
    - One concrete example: comparing a signed int to an unsigned std::size_t (e.g. int i = -1; if (i < size) ...) 
      - causes the compiler to implicitly convert i to unsigned, turning -1 into a huge positive number — so a loop guard meant to stop at a negative index instead evaluates as true and can cause out-of-bounds access.
2. Explain the difference among `const int*`, `int* const`, and `const int* const`.
    - `const int*` is non const pointer to const int. 
    - `int* const` is const pointer to non const int.
    - `const int * const` is const pointer to const int.
3. Why do arrays passed as function parameters not retain their array size? Relate your answer to array-to-pointer conversion.
    - arrays like `int[]` are syntax sugar that will decay to pointer like `int*` so we can't relay on it's size, `sizeof` operator will return size of pointer to int instead size of array in memory.
4. Compare pass-by-value, pass-by-pointer, pass-by-reference, and pass-by-`const`-reference. Give one appropriate use case for each.
    - pass-by-value copies values into function, we use it when we do not want to modify original value or to save memory when passing primitive values which size is less then `sizeof(int*)`.
    - pass-by-pointer is used to operate on original value inside function. 
      - use when the argument might legitimately be "absent" (nullptr), when you need to reassign what's pointed to, or when working with arrays/dynamic memory where pointer arithmetic is natural (e.g. your begin/end functions).
    - pass-by-reference is used to operate on the original value inside the function, references are available in C++, they are simpler to read then pointers and decay to pointers. 
      - use when the object is guaranteed to exist (references can't be null) and you just want cleaner syntax than pointers, with no risk of a null-dereference bug — e.g. swap_values(int& lhs, int& rhs).
    - pass-by-const-reference is used to safe memory while not copying by value and keep original object safe from any modifications.
5. Describe the four build stages from source file to executable: preprocessing, compilation, assembling, and linking. At which stage would an unresolved function definition normally be reported?
    - preprocessing - solve all defines and includes `#` and create big code file.
    - compilation - compile all C/C++ files into assembly code.
    - assembly - assemble all ASM files into object files.
    - linking - replace external libraries stubs addresses inside assembled object files to real links
6. Explain how AddressSanitizer and UndefinedBehaviorSanitizer help with this assignment. Give one defect each sanitizer may detect, and explain why passing sanitizer checks does not prove that a program is correct.
    - We can compile application with active sanitizer and run program to see sanitizer insights, such as undefined behavior or memory leaks.
