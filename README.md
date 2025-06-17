# ProbDS-Lite

This is a minimal prototype implementing a Bloom filter as described in
`Plan`. The library is header-only and built with CMake.

## Build & Test

```
cmake -S . -B build
cmake --build build
ctest --test-dir build
```
