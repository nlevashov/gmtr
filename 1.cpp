#include <iostream>
#include <cmath>
#include "2.cpp"
using namespace std;

class Segment;
class Circle;
class Poly;

class Point {
	private:
		double x, y;

	public:
		Point() {
			cin >> x >> y;
		}

		Point(double p, double q) {
			x = p;
			y = q;
		}

		double Get_x() { return x; }
		double Get_y() { return y; }

		friend Segment;
		friend Circle;
		friend Poly;
};

class Segment {
	private:
		double x1, y1, x2, y2;

	public:
		Segment() {
			cin >> x1 >> y1 >> x2 >> y2;
		}

		Segment(double ax, double ay, double bx, double by) {
			x1 = ax;
			y1 = ay;
			x2 = bx;
			y2 = by;
		}

		double Get_x1() { return x1; }
		double Get_y1() { return y1; }
		double Get_x2() { return x2; }
		double Get_y2() { return y2; }

		bool isContain(Point p) {
			return ( ((p.x >= x1 && p.x <= x2) || (p.x <= x1 && p.x >= x2))
				&& ((p.y >= y1 && p.y <= y2) || (p.y <= y1 && p.y >= y2))
				&& (abs((p.y - y1) * (x1 - x2) - (p.x - x1) * (y1 - y2)) <= 0.000000000000001));
		}

		int isIntersect(Segment b) {	// 0 - не паралельны, пересечений нет; 1 - не паралельны, есть пересечение; 2 - паралельны, нет общих точек; 3 - паралельны, имеют общую область;
			double parallel = (y1 - y2) * (b.x1 - b.x2) - (b.y1 - b.y2) * (x1 - x2);
			if (parallel == 0) {
				if (this -> isContain(Point(b.x1, b.y1)) || this -> isContain(Point(b.x2, b.y2))) return 3;
				else return 2;
			} else {
				double
					x = ((b.y1 - y1) * (x1 - x2) * (b.x1 - b.x2) + x1 * (y1 - y2) * (b.x1 - b.x2) - b.x1 * (b.y1 - b.y2) * (x1 - x2)) / parallel,
					y = (x1 == x2) ? ((b.y1 - b.y2) * (x - b.x1) / (b.x1 - b.x2) + b.y1) : ((y1 - y2) * (x - x1) / (x1 - x2) + y1);
				return (this -> isContain(Point(x, y)) && b.isContain(Point(x, y)));
			}
		}

		friend Circle;
};

class AFigure {
	protected:
		double square;

	public:
		virtual bool isContain(Point) = 0;
		virtual bool isIntersect(Segment) = 0;

		double getSquare() { return square; }
};

class Poly : public AFigure {
	private:
		unsigned int angleNum;
		MyVector a;
		MyVector aSorted;
		double * aAngles;

		void aSort() {
			unsigned int iMin = 0;
			for (int i = 1; i < angleNum; ++i)
				if ((a[i].y < a[iMin].y) || (a[i].y == a[iMin].y && a[i].x < a[iMin].x)) iMin = i;

			MyVector r;
			unsigned int j = 0, k = 0;
			for (int i = 0; i < angleNum; ++i) {
				if (a[i].x <= a[iMin].x) aSorted[j++] = a[i];
				else r[k++] = a[i];
			}

			aSorted.sort();
			r.sort();
			for (int i = k - 1; i >= 0; --i) aSorted[j++] = r[i];

			unsigned int aSortedNum = aSorted.getNum();
			for (int i = 1; i < aSortedNum; ++i)
				aAngles[i] = (aSorted[i].x - aSorted[0].x)
						/ sqrt((aSorted[i].x - aSorted[0].x) * (aSorted[i].x - aSorted[0].x)
							 + (aSorted[i].y - aSorted[0].y) * (aSorted[i].y - aSorted[0].y));
		}

	public:
		Poly() {
			cin >> angleNum;
			for (int i = 0; i < angleNum; ++i) cin >> a[i].x >> a[i].y;
			aAngles = new double[angleNum];
			aSort();
			square = 0;
			for (int i = 2; i < angleNum; ++i)
				square += abs( (aSorted[i-1].x - aSorted[0].x) * (aSorted[i].y - aSorted[0].y)
						- (aSorted[i].x - aSorted[0].x) * (aSorted[i-1].y - aSorted[0].y) ) / 2;
		}

		Poly(int n, double * b) {
			angleNum = n;
			for (int i = 0; i < 2 * n; i += 2) {
				a[i].x = b[i];
				a[i].y = b[i + 1];
			}
			aAngles = new double[angleNum];
			aSort();
			square = 0;
			for (int i = 2; i < angleNum; ++i)
				square += abs( (aSorted[i-1].x - aSorted[0].x) * (aSorted[i].y - aSorted[0].y)
						- (aSorted[i].x - aSorted[0].x) * (aSorted[i-1].y - aSorted[0].y) ) / 2;
		}

		~Poly() {
			delete aAngles;
			//удалятся ли остальные?
		}

		unsigned int getAngleNum() { return angleNum; }
		unsigned int getAx(unsigned int i) { return a[i].x; }
		unsigned int getAy(unsigned int i) { return a[i].y; }

		bool isContain(Point p) {
			if (p.y >= aSorted[0].y) {
				double cosP = (p.x - aSorted[0].x) / sqrt((p.x - aSorted[0].x) * (p.x - aSorted[0].x) + (p.y - aSorted[0].y) * (p.y - aSorted[0].y));
				bool flag = false;
				int i;
				for (i = 1; i < angleNum; ++i) {
					if (cosP <= aAngles[i]) {
						flag = true;
						break;
					}
				}

				if (flag && ((i != 1) || (i == 1) && Segment(aSorted[0].x, aSorted[0].y, aSorted[1].x, aSorted[1].y).isContain(p))) {	//i-1, i
					Segment s(aSorted[i-1].x, aSorted[i-1].y, aSorted[i].x, aSorted[i].y);
					return ( s.isContain(p) || (! s.isIntersect(Segment(aSorted[0].x, aSorted[0].y, p.x, p.y))) );
				} else return false;

			} else return false;
		}

		bool isIntersect(Segment s) {
			bool flag;
			for (int i = 0; i < angleNum - 1; ++i) {
				flag = s.isIntersect(Segment(aSorted[i].x, aSorted[i].y, aSorted[i+1].x, aSorted[i+1].y));
				if (flag) return true;
			}
			if (! flag) return s.isIntersect(Segment(aSorted[angleNum-1].x, aSorted[angleNum-1].y, aSorted[0].x, aSorted[0].y));
		}
};

class Circle : public AFigure {
	private:
		double radius, x, y;

	public:
		Circle() {
			cin >> radius >> x >> y;
			square = M_PI * radius;
		}

		Circle(double rad, double centerX, double centerY) {
			radius = rad;
			x = centerX;
			y = centerY;
			square = M_PI * radius;
		}

		double getRadius() { return radius; }
		double getX() { return x; }
		double getY() { return y; }

		bool isContain(Point p) {
			return ((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) <= radius * radius);
		}

		bool isIntersect(Segment s) {
			double xt, yt;

			if (s.x1 == s.x2) {
				xt = s.x1;
				yt = y;
			} else {
				double k = (s.y1 - s.y2) / (s.x1 - s.x2);
				xt = (x + (y - s.y1) * k + s.x1 * k * k) / (1 + k * k);
				yt = (s.y1 + (x - s.x1) * k + y * k * k) / (1 + k * k);
			}

			return ( (s.isContain(Point(xt, yt)) && ((x - xt) * (x - xt) + (y - yt) * (y - yt) <= radius * radius) )
				|| ((x - s.x1) * (x - s.x1) + (y - s.y1) * (y - s.y1) <= radius * radius)
				|| ((x - s.x2) * (x - s.x2) + (y - s.y2) * (y - s.y2) <= radius * radius) );
		}
};

int main()
{
	return 0;
}
