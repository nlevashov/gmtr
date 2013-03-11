#include "head.h"

#include <iostream>
#include <cmath>
using std::cin;

template <typename T>
class Segment {
	private:
		T x1, y1, x2, y2;

	public:
		Segment() {
			cin >> x1 >> y1 >> x2 >> y2;
		}

		Segment(T ax, T ay, T bx, T by) {
			x1 = ax;
			y1 = ay;
			x2 = bx;
			y2 = by;
		}

		T getX1() { return x1; }
		T getY1() { return y1; }
		T getX2() { return x2; }
		T getY2() { return y2; }

		bool isContain(Point<T> p) {
			return ( ((p.x >= x1 && p.x <= x2) || (p.x <= x1 && p.x >= x2))
				&& ((p.y >= y1 && p.y <= y2) || (p.y <= y1 && p.y >= y2))
				&& (std::abs((p.y - y1) * (x1 - x2) - (p.x - x1) * (y1 - y2)) <= 0.000000000000001));
		}

		int isIntersect(Segment<T> b) {	// 0 - не паралельны, пересечений нет; 1 - не паралельны, есть пересечение; 2 - паралельны, нет общих точек; 3 - паралельны, имеют общую область;
			double parallel = (y1 - y2) * (b.x1 - b.x2) - (b.y1 - b.y2) * (x1 - x2);
			if (parallel == 0) {
				if (this -> isContain(Point<T>(b.x1, b.y1)) || this -> isContain(Point<T>(b.x2, b.y2))) return 3;
				else return 2;
			} else {
				double
					x = ((b.y1 - y1) * (x1 - x2) * (b.x1 - b.x2) + x1 * (y1 - y2) * (b.x1 - b.x2) - b.x1 * (b.y1 - b.y2) * (x1 - x2)) / parallel,
					y = (x1 == x2) ? ((b.y1 - b.y2) * (x - b.x1) / (b.x1 - b.x2) + b.y1) : ((y1 - y2) * (x - x1) / (x1 - x2) + y1);
				return (this -> isContain(Point<T>(x, y)) && b.isContain(Point<T>(x, y)));
			}
		}

		friend Circle<T>;
};
