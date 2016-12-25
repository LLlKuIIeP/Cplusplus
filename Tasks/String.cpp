#include <iostream>
#include <cstddef>		//	size_t
#include <cstring>		//	функции строк в стиле С

using namespace std;

struct SubString {
	SubString(char *s, int st) :start(st), end(-1), flag(false), str(s) {}
	char* operator[](int e) const {
		char *c = new char[e - start + 1];
		int i, k;
		k = 0;
		for(i = start; i < e; i++) {
			c[k] = str[i];
			k++;
		}
		c[k] = '\0';
		return c;
		//return fun_2(e);
	}

	int start, end;
	bool flag;
	char *str;
};

//SubString sub_str;

struct String {
	String(const char *str = "") {
		size = strlen(str);
		this->str = new char[size + 1];
		strcpy(this->str, str);
		this->str[size] = '\0';
	}
	
	String(const char *str, int st) {
		size = strlen(str);
		this->str = new char[size + 1];
		strcpy(this->str, str);
		this->str[size] = '\0';
		start = st;
	}

	String(const String &other) {
		size = other.size;
		str = new char[size + 1];
		int i;
		for(i = 0; i < size; i++) {
			str[i] = other.str[i];
		}
		str[size] = '\0';
	}
	
	String & operator=(const String &other) {
		if (this != &other) {
			delete[] str;
			size = other.size;
			str = new char[size + 1];
			for (int i = 0; i < size; i++) {
				str[i] = other.str[i];
			}
			str[size] = '\0';
		}
		return *this;
	}
	
	void append(String &other) {
		size_t sz = this->size + other.size + 1;
		char *s = new char[sz];
		strcat(s, this->str);
		strcat(s, other.str);
		s[sz] = '\0';
		delete [] this->str;
		this->str = s;
		this->size = sz - 1;
	}
	
	String operator[](int n) const {
		if(start > -1 && start <= n) {
			char *c = new char[n - start + 1];
			int i, k;
			k = 0;
			for(i = start; i < n; i++) {
				c[k] = str[i];
				k++;
			}
			c[k] = '\0';
			String new_str(c);
			delete [] c;
			return new_str;
		}
		return String(str, n);
	}

	size_t size;
	char *str;
	int start;

};







int main(int argc, char const *argv[])
{
String const hello("hello");
cout << hello[0].str << endl;
cout << hello[0][4] << endl;
cout << hello[1][4] << endl;
cout << hello[1][1] << endl;


/*	String greet("Hello");
	char ch1 = greet.at(0);

	String const const_greet("Hello, Const!");
	char const &ch2 = const_greet.at(0);*/


	/*{
		String s1("Hello");
		String s2(", world!");
		s1.append(s2);

		std::cout << 
					"String: " << s1.str << std::endl <<
					"Size: " << s1.size <<
		std::endl;
	}

	{
		String s("");

		std::cout << 
					"String: " << s.str << std::endl <<
					"Size: " << s.size <<
		std::endl; 
	}

	{
		String s("123456   WIN!!!");

		std::cout << 
					"String: " << s.str << std::endl <<
					"Size: " << s.size <<
		std::endl; 
	}

	{
		String s;

		std::cout << 
					"String: " << s.str << std::endl <<
					"Size: " << s.size <<
		std::endl; 
	}*/

	return 0;
}
