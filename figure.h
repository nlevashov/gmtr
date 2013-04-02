#ifndef _FIGURE

#define _FIGURE

#include "point.h"
#include "segment.h"

class Afigure {
	protected:
		double _square;

	public:
		template <typename U> bool isContain(point<U>);
		template <typename U> bool isIntersect(segment<U>);

		double square() const { return _square; }
};

#endif
