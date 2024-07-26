#include <benchmark/benchmark.h>

#define BENCHMARK_COLLECTIONS 1
#if BENCHMARK_RECTANGLE
#include "./tests/geometry/main.cpp"
#endif 
#if BENCHMARK_COLLECTIONS
#include "./tests/collections/test-iterate-std-vector.cpp"
#endif
BENCHMARK_MAIN();