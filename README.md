# Two's Complement Arithmetic (Addition and Subtraction)

This repository contains both C and C++ implementations of two's complement arithmetic in signed integer representation. It was developed as part of the **Computer Organization and Algorithm (COA)** course during self-study.

## Overview
- Implements binary addition in two's complement form.
- Subtraction is implicitly included, since subtraction in two's complement is performed via addition.
- Provides error codes for debugging when something goes wrong (distinct from segmentation faults).

## Error Handling
- The C implementation uses explicit error codes and `fprintf` messages for clarity by printing to Standard Error.
- These codes are designed to make debugging straightforward without relying on runtime crashes.

## Cryptic Constructs
- The `BinAdd` function is deliberately written using pointer arithmetic for training purposes.
- Example: `0[temp]` is equivalent to `temp[0]`, but chosen to challenge novices and encourage deeper understanding.
- Another example is pointer-based index traversal when performing bit addition.

## C++ Expansion
- In C, expressions like `Bin bin = bin1 + bin2;` are not possible.
- The C++ version introduces a `Bin` class with operator overloading:
  - `operator+` for addition
  - `operator=` for assignment
- This makes usage more natural and idiomatic in C++.

## Example
```c
// C version
BinAdd(bin1, bin2);

// C++ version
Bin bin = bin1 + bin2;
```

## Learning Goals
This project is not only about functionality but also about **discipline and awareness** in low-level programming:
- **Pointer arithmetic practice**: Using constructs like `0[temp]` to deepen understanding of array indexing and memory access.
- **Error handling discipline**: Explicit error codes instead of silent failures or crashes.
- **Const correctness in C++**: Learning how to enforce immutability and safe access in class design.
- **Memory ownership awareness**: Implementing constructors, destructors, and assignment operators to avoid leaks and undefined behavior.
- **Bridging paradigms**: Experiencing the transition from procedural C to object-oriented C++ while preserving operational clarity.


## Note
Compilation instructions for both C and C++ versions are not included here.  
Try running them on your own 😁
