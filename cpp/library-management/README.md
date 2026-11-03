# C++ Library Management

A console library-management coursework project with books, readers, employees, reservations, loans, CSV persistence and simulated dates. This is a separate C++ implementation from the Java library project.

The sources come from `io/test` in the academic archive. Packaging replaces the non-standard `bits/stdc++.h` umbrella header with standard includes and adds a portable CMake target. Existing compiler warnings and educational authentication remain; no real user data is supplied.

## Build and run

With a C++17 compiler and CMake:

```text
cmake -S . -B build
cmake --build build
```

Run the produced `library_management` executable (Windows: `library_management.exe`; some CMake generators place it under `build/Debug`). CSV paths are relative to the working directory. Registration creates local demonstration accounts; use synthetic data.

The source was compiled with MinGW GCC 13.1 and a startup/menu/exit smoke check passed. Full lending and reservation workflows have not been tested. Password handling is educational and unsuitable for a real service.
