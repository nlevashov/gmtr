#include "head.h"
#include "figure.h"
#include "vector.h"
using namespace myVector;

#include <iostream>
#include <cmath>
using std::cin;

template <typename T>
class Poly : public AFigure {
	private:
		unsigned int angleNum;
		vector<T> a;
		vector<T> aSorted;
		double * aAngles;

		void aSort() {
			unsigned int iMin = 0;
			for (int i = 1; i < angleNum; ++i)
				if ((a[i].y < a[iMin].y) || (a[i].y == a[iMin].y && a[i].x < a[iMin].x)) iMin = i;

			vector<> r;
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

		Poly(int n, T * b) {
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
		}

		unsigned int getAngleNum() { return angleNum; }
		T getAx(unsigned int i) { return a[i].x; }
		T getAy(unsigned int i) { return a[i].y; }

		bool isContain(Point<> p) {
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

				if (flag && ((i != 1) || (i == 1) && Segment<T>(aSorted[0].x, aSorted[0].y, aSorted[1].x, aSorted[1].y).isContain(p))) {	//i-1, i
					Segment<T> s(aSorted[i-1].x, aSorted[i-1].y, aSorted[i].x, aSorted[i].y);
					return ( s.isContain(p) || (! s.isIntersect(Segment<>(aSorted[0].x, aSorted[0].y, p.x, p.y))) );
				} else return false;

			} else return false;
		}

		bool isIntersect(Segment<> s) {
			bool flag;
			for (int i = 0; i < angleNum - 1; ++i) {
				flag = s.isIntersect(Segment<T>(aSorted[i].x, aSorted[i].y, aSorted[i+1].x, aSorted[i+1].y));
				if (flag) return true;
			}
			if (! flag) return s.isIntersect(Segment<T>(aSorted[angleNum-1].x, aSorted[angleNum-1].y, aSorted[0].x, aSorted[0].y));
		}
};
