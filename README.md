# Petit Koka Compiler in C++

This repository contains a C++ implementation of a compiler for a subset of the [Koka](https://koka-lang.github.io/koka/) language. Koka is a functional programming language with a strong focus on managing side effects. This project provides a simple compiler that should passes all the tests :eyes: for compliance with the Petit Koka language specification.

---

## Features

- Full implementation of the Petit Koka language syntax and semantics.
- Basic Type checking
- Built using C++ for future performance using LLVM.

---

## Errors made along the way

- Using Bison/Flex was a bad idea, it is very old, forces the use of raw pointers, cant emit tokens (in flex), cant forward lookup tokens (in flex), RIP Bison/Flex, shouldn't have exhumed you.
- Using C++ was also a bad idea... the lack of matching is painfull.

---

## Problems found along the way

- `8 + (return 5)` is well typed in koka but crashes at compilation...
this is also a problem for typing as `return 8` is of type int but then because `if n <= 1 then return 1`
gets desugared into `if n <= 1 then return 1 else {}` there is a type mismatch as "{}" is type unit.
The solution i chose is to use a loose type that can only unify to unit or the same sub-type.

- The compilation of `println` was a bit of a pain because of this (the koka compiler seem to fail typing it ...) :

```koka
fun main()
    println(main())
    8 + main()
```

In this example once we reach the typing of println, main is unit -> weak so we are printing a weak type... We have to make a choice among the 4 we can make : unit, bool, string, int.
But if we make the wrong lets say string choice we unify with main and main becomes : unit -> string.
Then we get a type mismatch at `8 + main()`. The solution : ad-hoc polymorphism.
I implemented it with `TVariant` it only supports basic types (the 4 basic types mentionned above) and works by storing the set of possibile type. If we didnt do that then either we cant type this code or we have to do a LOT of backtracking which is not ideal.

- We do need some kind of parametric types for such examples :

I achieve this by keeping intact the types in the env, except the current funtion.

```koka
fun main()
  val l = default(head([8]), 42)
  val k = default(head(["waw"]), "ohno")
  42
```

Overall it's not trivial to both accept "testfile-parametric-1.koka" while rejecting "typing/bad/testfile-ad-hoc-poly-2.koka"

---

## Todos

- Conflicts, conflicts and conflicts...
- Basic x86 assembly production "by hand" or LLVM IR production
- There are a LOT of memory leaks, not really a problem if you compile a single file, but is a problem for multiple files

---

## Requirements

To build and use this compiler, the following dependencies are required:

- `gcc` (GCC Compiler)
- `llvm` (LLVM Toolchain)
- `bison` (Parser Generator)
- `flex` (Lexical Analyzer Generator)

---

## Build Instructions

1.Clone the repository:

```bash
git clone https://github.com/maelhos/petit-koka.git
cd petit-koka
```

2.Build the compiler:

```bash
make clean
make
```

3.Run the tests:

```bash
./test.sh -2 ./kokac
```

## Acknowledgments

- Jean-Christophe Filliâtre for making this awesome project statement (and his incredible compilation course)
- My Coffee machine for helping me code all this in 3 weeks

---
