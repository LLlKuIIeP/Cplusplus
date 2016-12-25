#include <iostream>
#include <string>
#include <map>


int main(int argc, char const *argv[])
{
	char c, symbol;
	unsigned int k, m;
	std::string str_in, str_out;
	std::map<char, std::string> map;

	std::cin >> k >> m;

	for(auto i = 0; i < k; i++) {
		std::cin >> c >> symbol >> str_in;
		map[c] = str_in;
	}

/*	for(auto &elem : map) {
		std::cout <<
					elem.first << " " <<
					elem.second <<
		std::endl;
	}*/

	std::cin >> str_in;

	while(!str_in.empty()) {
		for(auto it = map.begin(); it != map.end(); it++) {
			//std::cout << "str_in: " << str_in << std::endl;
			if(str_in.find((*it).second) == 0) {
				//std::cout << (*it).first << std::endl;
				str_out += (*it).first;
				str_in.erase(0, (*it).second.size());
				break;
			}
		}
	}
	std::cout << str_out << std::endl;

	return 0;
}