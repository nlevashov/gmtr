#ifndef _POLY

#define _POLY

#include "figure.h"
#include "point.h"
#include "segment.h"
#include "vector.h"
#include <cmath>
using namespace myvector;

template <class T>
class poly : public Afigure {
	private:
		struct Tpoint {
			T _x, _y;
		};

		vector<Tpoint> _points;

	public:
		poly() {}

		poly(size_t n, T * coords)	//количество точек, массив точек (x0, y0, x1, y1, ...) в том порядке в котором он расположены на многоугольнике (по или против часовой стрелки)
		{
			for (size_t i = 0; i < n; i++) {
				_points[i]._x = coords[i * 2];
				_points[i]._y = coords[i * 2 + 1];
			}

			_square = 0;
			for (size_t i = 1; i < n - 1; i++) {
				_square += abs ( 0.5 * ((_points[i]._x - _points[0]._x) * (_points[i+1]._y - _points[0]._y) - (_points[i+1]._x - _points[0]._x) * (_points[i]._y - _points[0]._y)) );
				//0,5*[(x1-x3)(y2-y3)-(x2-x3)(y1-y3)]
			}
		}

		template <class U>
		poly(const poly<U> & p)
		{
			for (size_t i = 0; i < p.points_num(); i++) {
				_points[i]._x = T (p.x(i));
				_points[i]._y = T (p.y(i));
			}

			_square = p.square();
		}

		template <class U>
		poly & operator = (const poly<U> & p)
		{
			_points.resize(p.points_num());

			for (size_t i = 0; i < p.points_num(); i++) {
				_points[i]._x = p.x(i);
				_points[i]._y = p.y(i);
			}

			_square = p.square();
			return *this;
		}

		size_t points_num() const { return _points.size(); }
		T x(size_t i) const { return _points(i)._x; }
		T y(size_t i) const { return _points(i)._y; }

		template <class U>
		bool isContain(point<U> p)
		{
			double xMin = _points[0]._x;
			double xMax = _points[0]._x;
			for (size_t i = 1; i < _points.size(); i++) {
				if (_points[i]._x < xMin) xMin = _points[i]._x;
				if (_points[i]._x > xMax) xMax = _points[i]._x;
			}

			return (isIntersect(segment<double>(xMin - 1, double (p.y()), double (p.x()), double (p.y()))) && isIntersect(segment<double>(xMax + 1, double (p.y()), double (p.x()), double (p.y()))));
		}

		template <class U>
		bool isIntersect(segment<U> s)
		{
			for (size_t i = 0; i < _points.size() - 1; i++)
				if (s.isIntersect( segment<T>(_points[i]._x, _points[i]._y, _points[i+1]._x, _points[i+1]._y) )) return true;

			return s.isIntersect(segment<T>(_points[0]._x, _points[0]._y, _points[_points.size() - 1]._x, _points[_points.size() - 1]._y));
		}
};

#endif
