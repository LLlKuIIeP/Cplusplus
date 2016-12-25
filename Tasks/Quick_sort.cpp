#include <iostream>
#include <map>
#include <vector>
//#include <utility>

using namespace std;

int main(int argc, char const *argv[])
{
	int n, m, a, b;
	cin >> n >> m;

	multimap<int, int> map;
	vector<int> v(m), v_point(m);
	
	for(auto i = 0; i < n; ++i) {
		cin >> a >> b;
		map.insert(make_pair(a, b));
	}

/*	for(auto &it : map) {
		cout << it.first << " " << it.second << endl;
	}*/

	for(auto i = 0; i < m; ++i) {
		cin >> a;
		v[i] = a;
	}


	for(auto it = map.begin(); it != map.end(); it++) {
		for(auto i = 0; i < m; i++) {
			if(it->first <= v[i] && v[i] <= it->second) {
				++v_point[i];
			}
		}

	}

	for(auto i = 0; i < m; i++) {
		cout << v_point[i] << " ";
	}
	cout << endl;
/*
	auto x = 0;
	auto count = 0;
	for(auto i = 0; i < m; i++) {
		cin >> x;
		count = 0;

		auto it = map.begin();
		while(it != map.end()) {
			if(it->first <= x && x <= it->second) {
				count++;
			}
			else if(it->first > x) {
				break;
			}
			it++;
		}

		cout << count << " ";
	}
	cout << endl;
*/

	return 0;
}