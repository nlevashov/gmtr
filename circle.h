#ifndef _CIRCLE

#define _CIRCLE

#include "figure.h"
#include "point.h"
#include "segment.h"
#include <cmath>

template <class T = double>
class circle : public Afigure {
	private:
		T _radius, _x, _y;

	public:
		circle() {}

		circle(T radius, T centerX, T centerY) : _radius(radius), _x(centerX), _y(centerY)
		{
			_square = (double) M_PI * _radius * _radius;
		}

		template <class U>
		circle(const circle<U> & c) : _radius(T (c.radius())), _x(T (c.x())), _y(T (c.y()))
		{
			_square = c.square();
		}

		template <class U>
		circle & operator = (const circle<U> & c)
		{
			_radius = T (c.radius());
			_x = T (c.x());
			_y = T (c.y());
			_square = c.square();
			return *this;
		}

		T radius() const { return _radius; }
		T x() const { return _x; }
		T y() const { return _y; }

		template <class U>
		bool isContain(point<U> p) {
			return ((_x - p.x()) * (_x - p.x()) + (_y - p.y()) * (_y - p.y()) <= _radius * _radius);
		}

		template <class U>
		bool isIntersect(segment<U> s) {
			double xt, yt;

			if (s.x1() == s.x2()) {
				xt = s.x1();
				yt = _y;
			} else {
				double k = (s.y1() - s.y2()) / (s.x1() - s.x2());
				xt = (_x + (_y - s.y1()) * k + s.x1() * k * k) / (1 + k * k);
				yt = (s.y1() + (_x - s.x1()) * k + _y * k * k) / (1 + k * k);
			}

			return ( (s.isContain(point<double>(xt, yt)) && ((_x - xt) * (_x - xt) + (_y - yt) * (_y - yt) <= _radius * _radius) )
				|| ((_x - s.x1()) * (_x - s.x1()) + (_y - s.y1()) * (_y - s.y1()) <= _radius * _radius)
				|| ((_x - s.x2()) * (_x - s.x2()) + (_y - s.y2()) * (_y - s.y2()) <= _radius * _radius) );
		}
};

#endif
