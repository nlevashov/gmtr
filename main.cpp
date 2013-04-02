#include "gmtr.h"

#include <iostream>
using namespace std;

//poly testing (с памятью твориться что-то странное, но она не растет)

int main ()
{
//	while (1) {
		int p[10] = {0, 0, -1, 2, 0, 4, 2, 4, 3, 2};
		poly<int> a(5, p);

		poly<int> b = a;
		poly<float> c = a;

		poly<float> d; d = a;

		cout << "square = " << d.square() << endl;
		for (size_t i = 0; i < 5; i++) cout << (i+1) << ") " << d.x(i) << ' ' << d.y(i) << endl;
		cout << endl;

		cout << a.isIntersect(segment<float> (-1, -1, 1.5, -1)) << endl;
		cout << a.isIntersect(segment<long> (-1, 4, 2, 0)) << endl;

		cout << a.isContain(point<double> (0.5, 2.5)) << endl;
		cout << a.isContain(point<long> (3, 1)) << endl;
//	}

	return 0;
}



/* circle testing

int main ()
{
//	while (1) {
		circle<float> a(5.5, 0, 0);
		cout << a.radius() << ' ' << a.x() << ' ' << a.y() << ' ' << a.square() << endl;

		circle<int> b = a;
		circle<int> c; c = a;
		circle<float> d = a;
		circle<float> e; e = a;

		cout << b.radius() << ' ' << b.x() << ' ' << b.y() << ' ' << b.square() << endl;
		cout << c.radius() << ' ' << c.x() << ' ' << c.y() << ' ' << c.square() << endl;
		cout << d.radius() << ' ' << d.x() << ' ' << d.y() << ' ' << d.square() << endl;
		cout << e.radius() << ' ' << e.x() << ' ' << e.y() << ' ' << e.square() << endl;

		point<int> p(0, 1);
		point<double> q(5.5, 0.5);
		cout << a.isContain(p) << ' ' << a.isContain(q) << endl;

		segment<int> s(-1, 4, 3, 6);
		segment<double> t(-0.5, 5.5, 3.5, 4.5);
		cout << a.isIntersect(s) << ' ' << a.isIntersect(t) << endl;
//	}

	return 0;
}

*/

/* segment testing

int main ()
{
//	while (1) {
		segment<int> a(1, 2, 3, 4);
		segment<int> b = a;
		segment<int> c; c = a;
		segment<float> d = a;
		segment<float> e; e = a;

		point<int> p(2, 3);
		point<float> q(2.5, 3.5);

		cout << a.isContain(p) << ' ' << a.isContain(q) << endl;

		cout << a.isIntersect(b) << endl;

		segment<int> f(1, 4, 3, 2);
		cout << a.isIntersect(f) << endl;

		segment<float> g(1.5, 3, 3.5, 1.5);
		cout << a.isIntersect(g) << endl;
//	}
}

*/

/* point testing

int main()
{
//	while (1) {
		point<int> a(2, 3);
		point<int> b = a;
		point<int> c; c = a;
		point<int> d(4, 5); d = a;

		point<float> e = a;
		point<float> f; f = a;

		cout << a.x() << ' ' << a.y() << endl;
		cout << b.x() << ' ' << b.y() << endl;
		cout << c.x() << ' ' << c.y() << endl;
		cout << d.x() << ' ' << d.y() << endl;
		cout << e.x() << ' ' << e.y() << endl;
		cout << f.x() << ' ' << f.y() << endl;
//	}
}

*/
