#pragma once
#include <vector>
// ģ��һ�����������򣬶�Ӧgeos::operation::intersection::Rectangle��geos::Enevelope
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