#include "head.h"
#include "figure.h"

#include <iostream>
#include <cmath>
using std::cin;

template <typename T>
class Circle : public AFigure {
	private:
		T radius, x, y;

	public:
		Circle() {
			cin >> radius >> x >> y;
			square = M_PI * radius;
		}

		Circle(T rad, T centerX, T centerY) {
			radius = rad;
			x = centerX;
			y = centerY;
			square = (double) M_PI * radius;
		}

		T getRadius() { return radius; }
		T getX() { return x; }
		T getY() { return y; }

		bool isContain(Point<T> p) {
			return ((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) <= radius * radius);
		}

		bool isIntersect(Segment<T> s) {
			double xt, yt;

			if (s.x1 == s.x2) {
				xt = s.x1;
				yt = y;
			} else {
				double k = (s.y1 - s.y2) / (s.x1 - s.x2);
				xt = (x + (y - s.y1) * k + s.x1 * k * k) / (1 + k * k);
				yt = (s.y1 + (x - s.x1) * k + y * k * k) / (1 + k * k);
			}

			return ( (s.isContain(Point<>(xt, yt)) && ((x - xt) * (x - xt) + (y - yt) * (y - yt) <= radius * radius) )
				|| ((x - s.x1) * (x - s.x1) + (y - s.y1) * (y - s.y1) <= radius * radius)
				|| ((x - s.x2) * (x - s.x2) + (y - s.y2) * (y - s.y2) <= radius * radius) );
		}
};
