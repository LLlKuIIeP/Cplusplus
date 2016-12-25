#include <iostream>
#include <cstddef>
#include <map>
#include <set>
#include <vector>

template<class Key, class Value>
void printf_multimap(std::multimap<Key, Value> &m_map){
	std::cout << "\nStart printf_multimap:\n";
	for(auto &elem : m_map) {
		std::cout << elem.first << " " << elem.second << std::endl;
	}
	std::cout << "End printf_multimap:\n\n";
}

void printf_set(std::set<size_t> &set) {
	std::cout << "\nStart printf_set:\n";
	for(auto &elem : set) {
		std::cout << elem << std::endl;
	}
	std::cout << "End printf_set:\n\n";
}

template<class T>
void printf_vector(std::vector<T> &v) {
	std::cout << "\nStart printf_vector:\n";
	for(auto &elem : v) {
		std::cout << elem << std::endl;
	}
	std::cout << "End printf_vector:\n\n";
}


size_t find_min_rigth_value(std::multimap<size_t, size_t> &m_map) {
	auto it = m_map.begin();
	size_t min_rigth = (*it).second;

	for(auto &elem : m_map) {
		if(elem.second < min_rigth) {
			min_rigth = elem.second;
		}
	}

	return min_rigth;
}

void del_values_multimap(std::multimap<size_t, size_t> &m_map, size_t min) {
	for(auto it : m_map) {
		if(it.first <= min) {
			m_map.erase(it.first);
		}
	}
}



int main(int argc, char const *argv[])
{
	size_t n, a, b;
	std::multimap<size_t, size_t> m_map;
	//std::set<size_t> set;
	std::vector<size_t> v;


	std::cin >> n;
	for(auto i = 0; i < n; i++) {
		std::cin >> a >> b;
		m_map.insert(std::pair<size_t, size_t>(a, b));
	}
	//printf_multimap<size_t, size_t>(m_map);

	//set.insert(find_min_rigth_value(m_map));
	//printf_set(set);
	for(auto i = 0; !m_map.empty(); i++) {
		v.push_back(find_min_rigth_value(m_map));
		//printf_vector<size_t>(v);

		del_values_multimap(m_map, v[i]);
		//printf_multimap(m_map);
	}

	std::cout << v.size() << std::endl;
	for(auto i : v) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	return 0;
}