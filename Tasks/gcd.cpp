#include <iostream>

long long gcd(long long a, long long b) {
	if(a == 0) {
		return b;
	}
	else if(b == 0) {
		return a;
	}
	else if(a > b) {
		return gcd(a % b, b);
	}
	else {
		return gcd(b % a, a);
	}
}


int main(int argc, char const *argv[])
{
	std::cout << gcd(18, 35) << std::endl;
	std::cout << gcd(14159572, 63967072) << std::endl;
	return 0;
}