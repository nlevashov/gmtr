#ifndef _POINT

#define _POINT

template <class T = double>
class point {
	private:
		T _x, _y;

	public:
		point() {}

		point(T p, T q) : _x(p), _y(q) {}

		template <class U>
		point(const point<U> & p) : _x(T (p.x())), _y(T (p.y())) {}

		template <class U>
		point & operator = (const point<U> & p)
		{
			_x = T (p.x());
			_y = T (p.y());
			return *this;
		}

		T x() const { return _x; }
		T y() const { return _y; }
};

#endif
