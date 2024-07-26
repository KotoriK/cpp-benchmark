#include <benchmark/benchmark.h>
#include <vector>
#include <execution>
#include <algorithm>

static void bench_by_index(benchmark::State& state) {
	size_t size = state.range(0);
	std::vector<int> vec(size);
	for (auto _ : state) {
		volatile int sum = 0;
		for (size_t i = 0; i < size;i++) {
			sum += vec[i];
		}
	}
}
static void bench_by_index_get_size_per_iteration(benchmark::State& state) {
	size_t size = state.range(0);
	std::vector<int> vec(size);
	for (auto _ : state) {
		volatile int sum = 0;
		for (size_t i = 0; i < vec.size();i++) {
			sum += vec[i];
		}
	}
}
static void bench_by_iterator(benchmark::State& state) {
	size_t size = state.range(0);
	std::vector<int> vec(size);
	for (auto _ : state) {
		volatile int sum = 0;
		for (auto i = vec.begin();i < vec.end();i++) {
			sum += *i;
		}
	}
}
static void bench_by_iterator_end_cached(benchmark::State& state) {
	size_t size = state.range(0);
	std::vector<int> vec(size);
	const auto end = vec.end();
	for (auto _ : state) {
		volatile int sum = 0;
		for (auto i = vec.begin();i < end;i++) {
			sum += *i;
		}
	}
}
struct double8 {
	double a;
	double b;
	double c;
	double d;
	double e;
	double f;
	double g;
	double h;
};
static void bench_by_range_blob(benchmark::State& state) {
	size_t size = state.range(0);
	std::vector<double8> vec(size);
	for (auto _ : state) {
		volatile double sum = 0;
		for (auto i : vec) {
			sum += i.e;
		}
	}
}
static void bench_by_range_blob_const_ref(benchmark::State& state) {
	size_t size = state.range(0);
	std::vector<double8> vec(size);
	for (auto _ : state) {
		volatile double sum = 0;
		for (const auto& i : vec) {
			sum += i.e;
		}
	}
}
static void bench_by_range(benchmark::State& state) {
	size_t size = state.range(0);
	std::vector<int> vec(size);
	for (auto _ : state) {
		volatile int sum = 0;
		for (auto i : vec) {
			sum += i;
		}
	}
}
static void bench_by_range_const_ref(benchmark::State& state) {
	size_t size = state.range(0);
	std::vector<int> vec(size);
	for (auto _ : state) {
		volatile int sum = 0;
		for (const auto& i : vec) {
			sum += i;
		}
	}
}

static void bench_by_std_for_each(benchmark::State& state) {
	size_t size = state.range(0);
	std::vector<double8> vec(size);
	for (auto _ : state) {
		volatile double sum = 0;
		std::for_each(vec.begin(), vec.end(), [&sum](const double8& i) { sum += i.e; });
	}
}
static void bench_by_std_for_each_function_init_outside(benchmark::State& state) {
	size_t size = state.range(0);
	std::vector<double8> vec(size);
	volatile int sum = 0;

	const auto cb = [&sum](const double8& i) { sum += i.e; };
	for (auto _ : state) {
		std::for_each(vec.begin(), vec.end(), cb);
	}
}



BENCHMARK(bench_by_index)->Range(10, 100000)->RangeMultiplier(100);
BENCHMARK(bench_by_index_get_size_per_iteration)->Range(10, 100000)->RangeMultiplier(100);
BENCHMARK(bench_by_iterator)->Range(10, 100000)->RangeMultiplier(100);
BENCHMARK(bench_by_iterator_end_cached)->Range(10, 100000)->RangeMultiplier(100);
BENCHMARK(bench_by_range_blob)->Range(10, 100000)->RangeMultiplier(100);
BENCHMARK(bench_by_range_blob_const_ref)->Range(10, 100000)->RangeMultiplier(100);
BENCHMARK(bench_by_range)->Range(10, 100000)->RangeMultiplier(100);
BENCHMARK(bench_by_range_const_ref)->Range(10, 100000)->RangeMultiplier(100);
BENCHMARK(bench_by_std_for_each)->Range(10, 100000)->RangeMultiplier(100);
BENCHMARK(bench_by_std_for_each_function_init_outside)->Range(10, 100000)->RangeMultiplier(100);