#pragma once
#include <vector>
#include <random>
#include <iterator>
#include <memory>
#include "struct.h"
#include <utility>
#include <cassert>
using namespace std;
class RandomRectangleGenerator {
public:
	RandomRectangleGenerator(const RectangleArea& refRect, double size) : size(size) {
		distribX = std::uniform_real_distribution<double>(refRect.xmin, refRect.xmax);
		distribY = std::uniform_real_distribution<double>(refRect.ymin, refRect.ymax);
	}
	inline void generate(RectangleArea& rect) {
		rect.xmin = distribX(gen);
		rect.xmax = rect.xmin + size;
		rect.ymin = distribY(gen);
		rect.ymax = rect.ymin + size;
	}
private:
	std::mt19937 gen;
	std::uniform_real_distribution<double> distribX;
	std::uniform_real_distribution<double> distribY;
	double size;
};
class RandomPolygonGenerator {
public:
	RandomPolygonGenerator(const RectangleArea& refRect, size_t pointSizeMax, size_t pointSizeMin = 4) {
		assert(pointSizeMin >= 4);
		assert(pointSizeMax >= pointSizeMin);
		distribX = std::uniform_real_distribution<double>(refRect.xmin, refRect.xmax);
		distribY = std::uniform_real_distribution<double>(refRect.ymin, refRect.ymax);
		distribSize = std::uniform_int_distribution<size_t>(pointSizeMin, pointSizeMax);
	}
	inline CoordXY generateCoord() {
		return CoordXY{ distribX(gen) ,distribY(gen) };
	}
	inline CoordinateSequence generate() {
		return generate(distribSize(gen));
	}
	CoordinateSequence generate(size_t fixSize) {
		auto firstCoord = generateCoord();

		CoordinateSequence seq(fixSize);
		seq[0] = firstCoord;
		size_t i = 1;
		for (;i < fixSize - 1;i++) {
			seq[i] = generateCoord();
		}
		seq[i] = firstCoord;
		return seq;
	}
private:
	std::mt19937 gen;
	std::uniform_real_distribution<double> distribX;
	std::uniform_real_distribution<double> distribY;
	std::uniform_int_distribution<size_t> distribSize;
};