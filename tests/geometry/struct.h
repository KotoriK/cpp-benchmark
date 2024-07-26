#pragma once
#include <vector>
// 模拟一个长方形区域，对应geos::operation::intersection::Rectangle和geos::Enevelope
struct RectangleArea {
	double xmin;
	double xmax;
	double ymin;
	double ymax;
};

struct CoordXY {
	double x;
	double y;
};

typedef std::vector<CoordXY> CoordinateSequence;