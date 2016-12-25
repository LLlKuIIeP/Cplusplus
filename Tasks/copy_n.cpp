#include <iostream>
#include <cstddef>

template<class T, class U>
void copy_n(T *a, U *b, size_t size) {
	size_t i;
	for(i = 0; i < size; i++) {
		a[i] = (T)b[i];

	}
}



int main(int argc, char const *argv[])
{
	size_t n = 4;
	int ints[] = {1, 2, 3, 4};
	double doubles[4] = {};
	copy_n(doubles, ints, n);

	for(size_t i = 0; i < n; i++) {
		std::cout << doubles[i] << " " << std::endl;
	}
	return 0;
}
