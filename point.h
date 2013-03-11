#include "head.h"

#include <iostream>
using std::cin;

template <typename T>
class Point {
	private:
		T x, y;

	public:
		Point() {
			cin >> x >> y;
		}

		Point(T p, T q) {
			x = p;
			y = q;
		}

		T getX() { return x; }
		T getY() { return y; }

		friend Segment<T>;
		friend Circle<T>;
		friend Poly<T>;
};
