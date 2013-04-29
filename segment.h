#ifndef _SEGMENT

#define _SEGMENT

#include "point.h"
#include <cmath>

//привидение

template <class T = double>
class segment {
	private:
		T _x1, _y1, _x2, _y2;

	public:
		segment() {}

		segment(T ax, T ay, T bx, T by) : _x1(ax), _y1(ay), _x2(bx), _y2(by) {}

		template <class U>
		segment(const segment<U> & s) : _x1(T (s.x1())), _y1(T (s.y1())), _x2(T (s.x2())), _y2(T (s.y2())) {}

		template <class U>
		segment & operator = (const segment<U> & s)
		{
			_x1 = T (s.x1());
			_y1 = T (s.y1());
			_x2 = T (s.x2());
			_y2 = T (s.y2());
			return * this;
		}

		T x1() const { return _x1; }
		T y1() const { return _y1; }
		T x2() const { return _x2; }
		T y2() const { return _y2; }

		template <class U>		//is it possible to use??
		bool isContain(point<U> p) {
			return ( ((p.x() >= _x1 && p.x() <= _x2) || (p.x() <= _x1 && p.x() >= _x2))
				&& ((p.y() >= _y1 && p.y() <= _y2) || (p.y() <= _y1 && p.y() >= _y2))
				&& (std::abs((p.y() - _y1) * (_x1 - _x2) - (p.x() - _x1) * (_y1 - _y2)) <= 0.000000000000001) );
		}

		template <class U>
		bool isIntersect(segment<U> s) {
			double parallel = (_y1 - _y2) * (s.x1() - s.x2()) - (s.y1() - s.y2()) * (_x1 - _x2);
			if (parallel == 0) {
				if (this -> isContain(point<T>(s.x1(), s.y1())) || this -> isContain(point<T>(s.x2(), s.y2()))) return true;
				else return false;
			} else {
				double
					x = ((s.y1() - _y1) * (_x1 - _x2) * (s.x1() - s.x2()) + _x1 * (_y1 - _y2) * (s.x1() - s.x2()) - s.x1() * (s.y1() - s.y2()) * (_x1 - _x2)) / parallel,
					y = (_x1 == _x2) ? ((s.y1() - s.y2()) * (x - s.x1()) / (s.x1() - s.x2()) + s.y1()) : ((_y1 - _y2) * (x - _x1) / (_x1 - _x2) + _y1);
				return (this -> isContain(point<double>(x, y)) && s.isContain(point<double>(x, y)));
			}
		}

		template <class U>
		int isIntersectDetail(segment<U> s) {	// 0 - не паралельны, пересечений нет; 1 - не паралельны, есть пересечение; 2 - паралельны, нет общих точек; 3 - паралельны, имеют общую область;
			double parallel = (_y1 - _y2) * (s.x1() - s.x2()) - (s.y1() - s.y2()) * (_x1 - _x2);
			if (parallel == 0) {
				if (this -> isContain(point<T>(s.x1(), s.y1())) || this -> isContain(point<T>(s.x2(), s.y2()))) return 3;
				else return 2;
			} else {
				double
					x = ((s.y1() - _y1) * (_x1 - _x2) * (s.x1() - s.x2()) + _x1 * (_y1 - _y2) * (s.x1() - s.x2()) - s.x1() * (s.y1() - s.y2()) * (_x1 - _x2)) / parallel,
					y = (_x1 == _x2) ? ((s.y1() - s.y2()) * (x - s.x1()) / (s.x1() - s.x2()) + s.y1()) : ((_y1 - _y2) * (x - _x1) / (_x1 - _x2) + _y1);
				return (this -> isContain(point<double>(x, y)) && s.isContain(point<double>(x, y)));
			}
		}
};

#endif
