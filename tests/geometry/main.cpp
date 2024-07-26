// test-topology.cpp: 定义应用程序的入口点。

#include <benchmark/benchmark.h>
#include "./action.cpp"

using namespace std;
constexpr RectangleArea areaKeep = RectangleArea{ 0,100,0,100 };
constexpr RectangleArea areaFiltered = RectangleArea{ 100,150,100,150 };
inline static size_t randomSize(size_t max) {
	if (max == 1) {
		return 1;
	}
	return rand() % max;
}
static vector<RectangleArea> prepareRects(size_t sizeShouldKeep, size_t sizeShouldFiltered) {
	const size_t sizeTotal = sizeShouldKeep + sizeShouldFiltered;

	vector<RectangleArea> rects(sizeTotal);

	size_t sizeShouldKeepRemain = sizeShouldKeep;
	size_t sizeShouldFilteredRemain = sizeShouldFiltered;
	auto it = rects.begin();
	size_t* refSizeRemain = &sizeShouldKeepRemain;
	const RectangleArea* refRect = &areaKeep;

	while (sizeShouldKeepRemain > 0 || sizeShouldFilteredRemain > 0) {
		size_t generateSize = randomSize(*refSizeRemain);
		it = generateRandomRects(it, generateSize, (*refRect));
		*refSizeRemain -= generateSize;
		if (refSizeRemain == &sizeShouldKeepRemain) {
			if (sizeShouldFilteredRemain > 0) {
				refSizeRemain = &sizeShouldFilteredRemain;
				refRect = &areaFiltered;
			}
		}
		else {
			if (sizeShouldKeepRemain > 0) {
				refSizeRemain = &sizeShouldKeepRemain;
				refRect = &areaKeep;
			}
		}
	}
	return rects;
}
static void bench_is_overlap(benchmark::State& state) {
	auto generator = make_unique<RandomRectangleGenerator>(areaKeep, 1.0);
	RectangleArea rect;
	generator->generate(rect);

	volatile bool result = false;
	for (auto _ : state) {
		result = isOverlap(rect, areaKeep);
	}
}
static void bench_filter_rects(benchmark::State& state) {
	auto sizeTotal = state.range(0);
	constexpr size_t sizeKeep = 800;

	auto rects = prepareRects(sizeKeep, sizeTotal - sizeKeep);

	for (auto _ : state) {
		state.PauseTiming();
		vector<RectangleArea> keepRects;
		keepRects.reserve(sizeKeep);
		state.ResumeTiming();
		for (const auto& i : rects) {
			if (isOverlap(i, areaKeep)) {
				keepRects.push_back(i);
			}
		}
		state.PauseTiming();
		assert(keepRects.size() == sizeKeep);
		state.ResumeTiming();
	}
}
static void bench_get_envelope(benchmark::State& state) {
	auto size = state.range(0);
	auto gen = make_unique<RandomPolygonGenerator>(areaKeep, static_cast<size_t> (size));
	auto polygon = gen->generate(size);
	for (auto _ : state) {
		getEnvelope(polygon);
	}
}

BENCHMARK(bench_filter_rects)->Unit(benchmark::kMillisecond)->Args({ 1000 }); //size: 1000
BENCHMARK(bench_filter_rects)->Unit(benchmark::kMillisecond)->Args({ 100000 });//size: 10,0000
BENCHMARK(bench_filter_rects)->Unit(benchmark::kMillisecond)->Args({ 1000000 });//size: 100,0000
BENCHMARK(bench_is_overlap)->Args({ 10000000 });//size: 1000,0000
BENCHMARK(bench_get_envelope)->Unit(benchmark::kMillisecond)->Args({ 10000 });//size: 100,0000
BENCHMARK(bench_get_envelope)->Unit(benchmark::kMillisecond)->Args({ 1000000 });//size: 100,0000



