#include <iostream>
#include <memory>


int main(int argc, char const *argv[])
{
	int n;
	std::cin >> n;
	std::unique_ptr<int[]> u_ptr(new int[n + 1]);

	u_ptr[0] = 0;
	u_ptr[1] = 1;

	for(int i = 2; i <= n; i++) {
		u_ptr[i] = (u_ptr[i - 2] + u_ptr[i - 1]) % 10;
	}

	std::cout << u_ptr[n] << std::endl;
	return 0;
}