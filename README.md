# Discrete Program Synthesis

A C++ implementation of a program synthesizer that automatically generates programs from input-output examples.

## Overview

This project demonstrates how program synthesis works by creating a system that can automatically write simple arithmetic expressions based on examples. Given a set of input-output pairs, the synthesizer will find the simplest program that satisfies all examples.

## Features

- Enumerate and evaluate candidate programs
- Find the simplest program that matches given examples
- Support for basic arithmetic operations (+, -, *, /)

## Getting Started

### Prerequisites

- C++17 compatible compiler
- CMake 3.10+
- spdlog (for logging)

### Building

```bash
mkdir build && cd build
cmake ..
make
```

### Running Examples

```bash
./build/examples/arithmetic/arithmetic_example
```

## Example

```cpp
// Define examples: f(x) = 2x + 1
std::vector<Example> examples = {
    {0, 1},  // f(0) = 1
    {1, 3},  // f(1) = 3
    {2, 5}   // f(2) = 5
};

// Create synthesizer and find a solution
Synthesizer synth(examples);
ExprPtr result = synth.synthesize();

// Output: ((x * 2) + 1)
```
