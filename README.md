# Image Manipulation Library
A C++20 image manipulation library for loading, processing, and transforming images.

Final project for COMS4995W-002 Design using C++, Fall 2026.

## Project Structure

```text
.
├── include/       # Public headers
├── src/           # Library implementation
├── tests/         # Unit tests
├── CMakeLists.txt
└── README.md
```

## Requirements

- C++20 compatible compiler
- CMake 3.20 or later

## Build

Clone the repository:

```bash
git clone <repository-url>
cd image-manip
```

Configure the project:

```bash
cmake -S . -B build
```

Compile:

```bash
cmake --build build
```

## Running Tests

Build the project first:

```bash
cmake --build build
```

Run all tests:

```bash
cd build
ctest --output-on-failure
```
