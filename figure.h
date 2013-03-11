#ifndef _FIGURE

#define _FIGURE

#include "head.h"

class AFigure {
	protected:
		double square;

	public:
		template <typename U> bool isContain(Point<U>);
		template <typename U> bool isIntersect(Segment<U>);

		double getSquare() { return square; }
};

#endif
