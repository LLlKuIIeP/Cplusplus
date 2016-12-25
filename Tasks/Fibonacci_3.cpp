#include <iostream>
#include <vector>

long long find(long long n, long long m) {
	std::vector<long long> v;
	v.push_back(0);
	v.push_back(1);

	for(auto i = 2; i < 6*m; i++) {
		v.push_back((v[i-2] + v[i-1]) % m);

		if(i > 2 && v[i - 1] == 0 && v[i] == 1) {
			break;
		}
	}
	v.pop_back();
	v.pop_back();


/*	for(auto i = 0; i < v.size(); i++) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
*/
	auto i = n % v.size();
	return v[i];
}



int main(int argc, char const *argv[])
{
	unsigned int n, m;
	std::cin >> n >> m;

	std::cout << find(n, m) << std::endl;

	return 0;
}