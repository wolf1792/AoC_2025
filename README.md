
Advent of Code 2025 (c++)
=====================

Project layout
--------------
- `src/` : C++ sources and headers. Notable files:
	- `main.cpp` : the primary entry used by the CMake target. It constructs day-specific solver objects (e.g `Day1`, `Day2`) and calls `solve()` and `solve2()` on each, printing results.
	- `dayX.hpp` : day-specific solver classes exposing `solve()` and `solve2()`.
- `input_files/` : sample and real input files (e.g. `day1.txt`, `day1_sample.txt`).

How `main` works
-----------------
The top-level `src/main.cpp` creates instances of solver classes (for example `Day1`, `Day2`), calls their `solve()` and `solve2()` methods, and prints the returned results using `std::println`. Each day solver is implemented in its corresponding `dayX.hpp`/source and is responsible for loading/parsing input data when needed.

Build instructions
------------------
Recommended: build with CMake (works cross-platform):

```bash
# from repository root
cmake -S . -B build
cmake --build build --config Release

# Resulting executable (on Windows) will be at: build/cpp-codingchallenge.exe
``` 

Notes:
- The provided `CMakeLists.txt` configures an executable target named `cpp-codingchallenge` that currently compiles `src/main.cpp` (the top-level runner). 

Running the program
-------------------
- All classes load input files from the folder `input_files`, so the main executable should be launched from `../input_files`
