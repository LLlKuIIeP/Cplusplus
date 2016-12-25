int strstr(const char *text, const char *pattern) {
	if(pattern == "") {
		return 0;
	}

	int size = 0;
	while(pattern[size]) { size++; }

	int i = 0;
	int j = 0;

	while(text[i]) {
		if(text[i] == pattern[0]) {
			int ii = i;
			while(text[ii] == pattern[j]) {
				ii++;
				j++;
				if(j == size) {
					return ii-j+1;
				}
			}
			j = 0;
		}
		i++;
	}
	return -1;
}



#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> fun(const int N) {
	std::vector<int> v(N - 2);
	for (auto i = 2; i < N; i++) {
		v[i - 2] = i;
	}

	for (auto i = 0; i < N - 2; i++) {
		for (auto j = i + 1; j < N - 2; j++) {
			if (v[i] != 0 && v[j] % v[i] == 0) {
				v[j] = 0;
			}
		}
	}
	std::sort(v.begin(), v.end());

	while (v[0] == 0) {
		v.erase(v.begin());
	}
	v.shrink_to_fit();
	return v;
}




int main(int argc, char *argv[])
{
	const int N = 13628;
	auto v = fun(N);
	//for (auto &elem : v) {
	//	std::cout << elem << " ";
	//}
	//std::cout << std::endl;

	int arr[N][N] = {0};
	for(std::size_t i = 0; i < N; i++) {
        arr[0][i] = i;
        arr[i][0] = i;
	}
	std::cout << "GGGG" << std::endl;
	for(std::size_t i = 0; i < N; i++) {
	    std::cout << arr[0][i] << " ";
        //for(std::size_t j = 0; j < N; j++) {
            //std::cout << arr[i][j] << " ";
        //}
        //std::cout << std::endl;
	}
	
	//system("pause");
	return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> fun(const int N) {
	std::vector<int> v(N - 2);
	for (auto i = 2; i < N; i++) {
		v[i - 2] = i;
	}

	for (auto i = 0; i < N - 2; i++) {
		for (auto j = i + 1; j < N - 2; j++) {
			if (v[i] != 0 && v[j] % v[i] == 0) {
				v[j] = 0;
			}
		}
	}
	std::sort(v.begin(), v.end());

	while (v[0] == 0) {
		v.erase(v.begin());
	}
	v.shrink_to_fit();
	return v;
}




int main(int argc, char *argv[])
{
	int N = 13628;
	//int N = 1001;


	auto v = fun(N);

/*	for (auto &elem : v) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;*/

/*	std::ofstream file("file");
	
	for(std::size_t i = 0; i < N; i++) {
        for(std::size_t j = 0; j < N; j++) {
        	if(i == 0) {
        		file << j << " ";
        	}
        	else if(j == 0) {
        		file << i << " ";
        	}
        	else {
        		file << 0 << " ";
        	}
        }
        file << std::endl;
	}
	file.close();*/







	int **arr = new int* [N];
	for(std::size_t i = 0; i < N; i++) {
		arr[i] = new int[N - i];
	}
	
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N - i; j++) {
			arr[i][j] = 0;
		}
	}
	

	//std::cout << N*N << std::endl;

	for(int i = 0; i < N; i++) {
		arr[0][i] = N - 1 - i;
	}

/*	for(int i = 0; i < N; i++) {
		std::cout << arr[0][i] << " ";
	}
	std::cout << std::endl;*/

	int k = v.size() - 1;
	for(int i = 0; i < N - 1; i++) {
		if(arr[0][i] == v[k]) {
			arr[1][i] = 1;
			k--;
		}
	}

/*	for(int i = 0; i < N - 1; i++) {
		std::cout << arr[1][i] << " ";
	}
	std::cout << std::endl;*/

	for(int i = N - 2 - 1; i >= 0; i--) {;
		if(arr[1][i] == 1) {
			int x;
			for(int j = 0; j < v.size(); j++) {
				x = arr[0][i] + v[j];
				if(x <= arr[0][0]) {
					//std::cout << x << " ";
					arr[2][N - 1 - x] = 1;
				}
			}
			//std::cout << std::endl;
		}
	}

/*	for(int i = 0; i < N - 2; i++) {
		std::cout << arr[2][i] << " ";
	}
	std::cout << std::endl;*/


for(int t = 3; t < N; t++) {
	for(int i = N - t - 1; i >= 0; i--) {;
		if(arr[t - 1][i] == 1) {
			int x;
			for(int j = 0; j < v.size(); j++) {
				x = arr[0][i] + v[j];
				if(x <= arr[0][0]) {
					//std::cout << x << " ";
					arr[t][N - 1 - x] = 1;
				}
			}
			//std::cout << std::endl;
		}
	}

/*	for(int i = 0; i < N - t; i++) {
		std::cout << arr[t][i] << " ";
	}
	std::cout << std::endl;*/
}

int max = 0;
for(int i = 0; i < N - 1; i++) {
	for(int j = 0; j < i; j++) {
		if(arr[N - 1 - i][j] == 1) {
			max++;
		}
	}
}

std::cout << max << std::endl;

/*
	for(std::size_t i = N - 1; i >= 0; i--) {
        for(std::size_t j = N - 1; j >= 0; j--) {
            if(i > 0) {
            	arr[i][j] = 0;
            }
            else if(i == 0) {
            	arr[i][j] = j;
            }
        }
	}
*/

/*	for(std::size_t i = 0; i < N; i++) {
        for(std::size_t j = i; j < N; j++) {
        	std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
	}*/

	
	//system("pause");
	return 0;
}

46406564





#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>

std::vector<uint64_t> fun(uint64_t N) {
    std::vector<uint64_t> v;
    v.push_back(2);
    v.push_back(3);

    auto flag = true;
    unsigned int  M = std::sqrt(N);
    for(uint64_t i = 5; i < M; ++i) {
        for(auto &elem : v) {
            if(i % elem == 0) {
                flag = false;
                break;
            }
        }
        if(flag) {
            v.push_back(i);
        }
        flag = true;
    }
    
        for(auto &elem : v) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
}


int main(int argc, char *argv[])
{
	//int N = 13628;
	std::uint64_t max = 950000000;
	fun(max);
	std::cout << UINTMAX_MAX << "\n" << std::sqrt(max) << max;

	return 0;
}










