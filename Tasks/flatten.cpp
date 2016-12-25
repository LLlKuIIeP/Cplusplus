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

template<class T>
void flatten(const T &n, std::ostream &out) {
	out << n << " ";
}


template<class T>
void flatten(const Array<T> &arr, std::ostream &out) {
	for(size_t i = 0; i < arr.size(); i++) {
		flatten(arr[i], out);
	}
}


int main(int argc, char const *argv[])
{
	Array<int> ints(2, 0);
	ints[0] = 10;
	ints[1] = 20;
	flatten(ints, std::cout);
	std::cout << std::endl;

	Array< Array<int> > array_of_ints(2, ints);
	flatten(array_of_ints, std::cout);
	std::cout << std::endl;
	return 0;
}