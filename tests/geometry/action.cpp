#include "action.h"
/// <summary>
/// 
/// </summary>
/// <param name="amount">��������</param>
/// <param name="rect">�������ĸ���Χ</param>
/// <param name="size">���ɵ������εĳߴ�</param>
/// <returns></returns>
template <class ForwardIt>
static ForwardIt generateRandomRects(ForwardIt start, size_t amount, const RectangleArea& refRect, double size = 1.0) {
	if (amount == 0) {
		return start;
	}
	static_assert(std::is_same<typename std::iterator_traits<ForwardIt>::value_type, RectangleArea>::value, "ForwardIt must be iterator of RectangleArea");

	auto generator = make_unique<RandomRectangleGenerator>(refRect, size);
	auto end = start + amount;
	for (;start < end;start++) {
		generator->generate(*start);
	}
	return start;
}

static bool isOverlap(const RectangleArea& rect1, const RectangleArea& rect2) {
	return rect1.xmin < rect2.xmax && rect1.xmax > rect2.xmin && rect1.ymin < rect2.ymax && rect1.ymax > rect2.ymin;
}
static RectangleArea getEnvelope(const CoordinateSequence& seq) {
	RectangleArea rect = { 0,0,0,0 };
	for (auto i = seq.begin();i < seq.end() - 1;i++) {
		if (i->x > rect.xmax) {
			rect.xmax = i->x;
		}
		else
			if (i->x < rect.xmin) {
				rect.xmin = i->x;
			}
		if (i->y > rect.ymax) {
			rect.ymax = i->y;
		}
		else
			if (i->y < rect.ymin) {
				rect.ymin = i->y;
			}
	}
	return rect;
}
// TODO�� ʹ��simdһ�αȽ�4��double�ó����