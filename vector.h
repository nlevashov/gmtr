#include <cstdlib>
#include <cstring>

namespace myVector {
	template <typename T = double>
	class vector {
		private:
			typedef struct {
				T x, y;
			} SPoint;

			SPoint * startPoint;
			unsigned int num, memory;

			void qsort(unsigned int, unsigned int);

		public:
			vector();
			vector(unsigned int n);
			vector(vector const & v);
			~vector();

			unsigned int getNum() { return num; }

			vector operator=(vector const & v);
			SPoint & operator[](unsigned int i);

			void sort() { if (num > 1) qsort(0, num - 1); }
	};

	template <typename T>
	void vector<T> :: qsort(unsigned int low, unsigned int high)
		{
			long l = low, r = high;
			T midY = startPoint[(l + r) / 2].y;
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

	template <typename T>
	vector<T> :: vector() {
			startPoint = new SPoint[64];
			memory = 64;
			num = 0;
		}

	template <typename T>
	vector<T> :: vector(unsigned int n)
	{
		startPoint = new SPoint[n];
		memory = n;
		num = n;
	}

	template <typename T>
	vector<T> :: vector(vector const & v)
	{
		startPoint = new SPoint[v.num];
		memcpy(startPoint, v.startPoint, sizeof(SPoint) * v.num);
		memory = v.num;
		num = v.num;
	}

	template <typename T>
	vector<T> :: ~vector()
	{
		delete startPoint;
	}

	template <typename T>
	vector<T> vector<T> :: operator=(vector<T> const & v)
	{
		startPoint = (SPoint *) realloc(startPoint, sizeof(SPoint) * v.num);
		memcpy(startPoint, v.startPoint, sizeof(SPoint) * v.num);
		memory = v.num;
		num = v.num;
		return *this;
	}

	template <typename T>
	typename vector<T>::SPoint & vector<T> :: operator[](unsigned int i)
	{
		if (i >= num) {
			unsigned int newMemory = 64;
			while (newMemory <= i) newMemory <<= 1;
			startPoint = (SPoint *) realloc(startPoint, sizeof(SPoint) * newMemory);
			memory = newMemory;
			num = i + 1;
		}
		return startPoint[i];
	}
}
