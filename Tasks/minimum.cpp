#include <iostream>
#include <cstddef>

template <class T>
class Array {
	public:
		explicit Array(size_t size = 0, const T& value = T()) {
			sz = size;
			mas = static_cast<T*>(operator new[] (size * sizeof(T)));
			size_t i;
			for(i = 0; i < size; i++) {
				new(mas + i) T(value);
			}
		}

		Array(const Array &arr) {
			size_t i;
			sz = arr.sz;
			
			mas = static_cast<T*>(operator new[] (sz * sizeof(T)));
			for(i = 0; i < sz; i++) {
				new(mas + i) T(arr.mas[i]);
			}
		}

		size_t size() const {
			return sz;
		}

		Array<T>& operator=(const Array<T> &arr) {
			if(this != &arr && &arr != NULL) {
				size_t i, size;

				for(i = 0; i < sz; i++) {
					mas[i].~T();
				}
				operator delete[] (mas);

				sz = arr.sz;
				mas = static_cast<T*>(operator new[] (sz * sizeof(T)));
				for(i = 0; i < sz; i++) {
					new(mas + i) T(arr.mas[i]);
				}
			}
			return *this;
		}

		T& operator[](size_t n) {
			return mas[n];
		}
		const T& operator[](size_t n) const {
			return mas[n];
		}


	/// Add prnt() to Array class public methods:
		void prnt()
		{
			for (size_t i = 0; i < sz; ++i)
				std::cout << mas[i];
			std::cout << std::endl;
		}

		~Array() {
			size_t i;

			for(i = 0; i < sz; i++) {
				mas[i].~T();
			}
			operator delete[] (mas);
		}
	private:
		size_t sz;
		T *mas;
};

bool less(int a, int b) {
	return a < b;
}

struct Greater {
	bool operator()(int a, int b) const {
		return b < a;
	}
};
//	1 - шаблон для указателя на функцию
template<class T>
T minimum(const Array<T> &arr, bool (*com)(T a, T b)) {
	T min = arr[0];
	
	for(size_t i = 1; i < arr.size(); i++) {
		if(com(arr[i], min)) {
			min = arr[i];
		}
	}
	return min;
}
//	2 - шаблон для перегруженного оператора (int, int) класса
template<class T, class U>
T minimum(const Array<T> &arr, const U &oper) {
	T min = arr[0];
	
	for(size_t i = 1; i < arr.size(); i++) {
		if(oper(arr[i], min)) {
			min = arr[i];
		}
	}
	return min;
}
//	3 - шаблон, и для указателя на функцию, и для перегруженного оператора (int, int) класса
//	т.е. объединяет 1 и 2 вариант
template<class T, class U>
T minimum(const Array<T> &arr, U comp) {
	T min = arr[0];
	
	for(size_t i = 1; i < arr.size(); i++) {
		if(comp(arr[i], min)) {
			min = arr[i];
		}
	}
	return min;
}


int main(int argc, char const *argv[])
{
	Array<int> ints(3);
	ints[0] = 10;
	ints[1] = 2;
	ints[2] = 15;

	int min = minimum(ints, less);
	std::cout << min << std::endl;

	int max = minimum(ints, Greater());
	std::cout << max << std::endl;

	return 0;
}
