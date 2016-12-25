#include <iostream>
#include <vector>


using namespace std;

int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	vector<int> v(n);
	for(auto &elem : v) {
		cin >> elem;
	}

/*	for(auto &elem : v) {
		cout << elem << " ";
	}*/

	vector<int> d(n);
	for(auto i = 0; i < n; i++) {
		d[i] = 1;
		for(auto j = 0; j < i; j++) {
			if(v[i] % v[j] == 0 && d[j] + 1 > d[i]) {
				d[i] = d[j] + 1;
			}
		}
	}
/*	for(auto &elem : d) {
		cout << elem << " ";
	}
	cout << endl;*/
	int max = 0;
	for(auto &elem : d) {
		if(elem > max) {
			max = elem;
		}
	}

	cout << max << endl;

	return 0;
}