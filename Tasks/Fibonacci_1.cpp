#include <iostream>
#include <memory>

using namespace std;


int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	n++;
	unique_ptr<int[]> u_ptr(new int[n]);

	u_ptr[0] = 0;
	u_ptr[1] = 1;

	for(int i = 2; i < n; i++) {
		u_ptr[i] = u_ptr[i - 2] + u_ptr[i - 1];
	}

	cout << u_ptr[n - 1] << endl;
	return 0;
}
