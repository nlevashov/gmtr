#include <cstdlib>
#include <cstring>

typedef struct {
	double x, y;
} SPoint;

class MyVector {
	private:
		SPoint * startPoint;
		unsigned int num, memory;

		void qsort(int low, int high)
		{
			int l = low, r = high;
			double midY = startPoint[(l + r) / 2].y;
			SPoint temp;
			do {
				while (startPoint[l].y < midY) ++l;
				while (startPoint[r].y > midY) --r;
				if (l <= r) {
					temp = startPoint[l];
					startPoint[l] = startPoint[r];
					startPoint[r] = temp;
					++l; --r;
				}
			 } while (l < r);

			if (low < r) qsort(low, r);
			if (l < high) qsort(l, high);
		}

	public:
		MyVector() {
			startPoint = new SPoint[64];
			memory = 64;
			num = 0;
		}

		MyVector(unsigned int n) {
			startPoint = new SPoint[n];
			memory = n;
			num = n;
		}

		MyVector(MyVector const & v) {
			startPoint = new SPoint[v.num];
			memcpy(startPoint, v.startPoint, sizeof(SPoint) * v.num);
			memory = v.num;
			num = v.num;
		}

		~MyVector() {
			delete startPoint;
		}

		unsigned int getNum() { return num; }

		MyVector operator=(MyVector const & v) {
			startPoint = (SPoint *) realloc(startPoint, sizeof(SPoint) * v.num); //аналог в с++?
			memcpy(startPoint, v.startPoint, sizeof(SPoint) * v.num);
			memory = v.num;
			num = v.num;
		}

		SPoint & operator[](unsigned int i) {
			if (i >= num) {
				unsigned int newMemory = 64;
				while (newMemory <= i) newMemory <<= 1;
				startPoint = (SPoint *) realloc(startPoint, sizeof(SPoint) * newMemory);
				memory = newMemory;
				num = i + 1;
			}
			return startPoint[i];
		}

		void sort() {
			qsort(0, num - 1);
		}
};
