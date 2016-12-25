/*


Нужно сгенерировать все возможные k-сочетания из n элементов.

Формат входных данных:
Два числа k и n через пробел. Для них гарантированно выполняется условие: 0≤k≤n0≤k≤n. 

Формат выходных данных:
Необходимое число строк, в каждой из которых содержится k чисел из диапазона от 0 до n-1 включительно, разделенных пробелом. 



Sample Input 1:
2 3
Sample Output 1:
0 1
0 2
1 2

Sample Input 2:
1 1
Sample Output 2:
0
*/



#include <iostream>
#include <vector>



bool next_combination(std::vector<int> &v, const int n) {
	int k = v.size();
	for (int i = k - 1; i >= 0; --i) {
		if (v[i] < n - k + i) {
			++v[i];
			for (int j = i + 1; j < k; ++j) {
				v[j] = v[j - 1] + 1;
			}
			return true;
		}
	}
	return false;
}



int main(int argc, char const *argv[])
{
	int k;
	int n;

	std::cin >> k >> n;

	std::vector<int> v(k, 0);

	for(auto i = 0; i < k; ++i) {
		v[i] = i;
	}

    do {
		for(auto &elem : v) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;
    }
	while(next_combination(v, n));

	return 0;
}


//	Python3
/*
import itertools

(k, n) = input().split()
k = int(k)
n = int(n)
#print(k, n)

lst = list()
for i in range(n):
	lst.append(i)
#print(lst)

lst = list(itertools.combinations(lst, k))
#print(len(lst))
#if len(lst) == 1:
	#print(0)
#elif len(lst) > 1:
for i in lst:
	if len(i) == 0:
		break;
	for j in i:
		print(j, end=' ')
*/
	print()







