## This file will is a guide on compiling this program

#### Dependencies
	- Cmake at version 3.10 or higher
	- There is no required libraries. All libraries are dependency-free or precompiled (glfw3)

#### Compiler
Personally i develop on gcc on linux and mingw-64 in CLion on Windows.
I tried compiling program with mingw-64 from msys2 and it works but is painfull to use.

Code should generally 'just compile' with gcc, make and cmake (it will *probably* work with clang but i haven't tested that). I don't support visual studio compiler because it has different build flags and it would make Cmake files needlessly more complex
