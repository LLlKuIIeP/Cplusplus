#include <iostream>
#include <vector>

int find_elem(std::vector<int> &A, int elem) {
	auto left = 0;
	auto rigth = A.size();
	auto middle = rigth / 2;

	while(left < rigth) {
		if(elem > A[middle]) {
			left = middle + 1;
		}
		else if(elem < A[middle]) {
			rigth = middle;
		}
		else {
			return middle + 1;
		}
		middle = left + (rigth - left) / 2;
	}
	return -1;
}



int main(int argc, char const *argv[])
{
	int n, k;
	std::cin >> n;
	std::vector<int> A(n);
	for(auto &elem : A) {
		std::cin >> elem;
	}

	std::cin >> k;
	std::vector<int> b(k);
	for(auto &elem : b) {
		std::cin >> elem;
	}

	for (auto i = 0; i < b.size(); i++) {
		std::cout << find_elem(A, b[i]) << " ";//std::endl;
	}
	std::cout << std::endl;

	return 0;
}