#ifndef _MYVECTOR

#define _MYVECTOR

#include <cstdlib>
#include <cstring>

namespace myvector {
	template <typename T = double>
	class vector {
		private:
			T * _begin;
			size_t _size, _memory;

		public:
			vector();
			vector(size_t);
			vector(vector const &);
			~vector();

			size_t size() const { return _size; }
			size_t memory() const { return _memory; }

			vector operator = (vector const &);
			T & operator [] (size_t i);
			T operator () (size_t i) const;
			void resize(size_t n);
	};

	template <typename T>
	vector<T> :: vector() : _memory(64), _size(0)
	{
		_begin = new T[64];
	}

	template <typename T>
	vector<T>::vector(size_t n) : _memory(n), _size(n)
	{
		_begin = new T[n];
		_memory = n;
		_size = n;
	}

	template <typename T>
	vector<T>::vector(vector const & v)
	{
		_begin = new T[v._memory];
		memcpy(_begin, v._begin, sizeof(T) * v._memory);
		_memory = v._memory;
		_size = v._size;
	}

	template <typename T>
	vector<T>::~vector()
	{
		delete _begin;
	}

	template <typename T>
	vector<T> vector<T>::operator = (vector<T> const & v)
	{
		_begin = (T *) realloc(_begin, sizeof(T) * v._memory);
		memcpy(_begin, v._begin, sizeof(T) * v._memory);
		_memory = v._memory;
		_size = v._size;
		return *this;
	}

	template <typename T>
	T & vector<T>::operator [] (size_t i)
	{
		if (i >= _size) {
			_size = i + 1;
			if (i >= _memory) {
				while (_memory <= i) _memory <<= 2;
				_begin = (T *) realloc(_begin, sizeof(T) * _memory);
			}
		}
		return _begin[i];
	}

	template <typename T>
	T vector<T>::operator () (size_t i) const
	{
		if (i < _size) return _begin[i];
	}

	template <typename T>
	void vector<T>::resize(size_t n)
	{
		_begin = (T *) realloc(_begin, sizeof(T) * n);
		_memory = n;
		if (_size > n) _size = n;
	}
}

#endif
