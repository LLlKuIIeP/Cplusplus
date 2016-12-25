#include <iostream>
#include <list>

using namespace std;

template<class T>
unsigned int fun(T &longList) {
	unsigned int res = 0;
	for (auto it = longList.rbegin(); it != longList.rend(); it++ ) {
		auto nextIter = it;
		nextIter++;
		if (nextIter != longList.rend() && **nextIter < 0) {
			**it *= -1;
			res++;
		}
	}
	if (longList.size() > 1){
		cout << "(";
		auto it = longList.begin();
		cout << **it;
		it++;
		while (it != longList.end()) {
			cout << "," << **it;
			it++;
		}
		cout << ")";
	}
	else if (longList.size() == 1){
		cout << "(";
		auto it = longList.begin();
		cout << **it <<")";
	}
	return res;
}

void Input(list<long int*> &longList) {
	char symbol;
	long int elem;

	cin >> symbol;
	while (symbol != '(') {
			cin >> symbol;
		}

	while (symbol != ')') {
		switch (symbol) {
			case '-': case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				cin.putback(symbol);
				cin >> elem;
				longList.push_back(new long int(elem));
				break;
			default:
				break;
		}
		cin >> symbol;
	}
}

int main()
{
	list<long int*> longList;
	Input(longList);

	unsigned int res = fun<list<long int*>>(longList);

	return 0;
}
