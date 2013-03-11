#include "point.h"
#include "segment.h"
#include "poly.h"
#include "circle.h"

#include <iostream>
using namespace std;

int main()
{
	Point<> p;
	Segment<> s;
	Poly<> t;

	cout << t.isContain(p) << ' ' << t.isIntersect(s) << endl;
	return 0;
}
