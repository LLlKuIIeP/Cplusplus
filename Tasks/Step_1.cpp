#include <iostream>
#include <string>
#include <sstream>
#include <math.h> 

int main()
{
    std::string str;
    getline (std::cin, str);
    
    if(str[0] == '+') {
        str.erase(str.begin());
    }

    if(str[str.length() - 1] == '\n') {
        str.erase(str.length() - 1);
    }
    
    double d;
    std::istringstream ist(str);
    ist >> d;
    
    if(d < 1.0) {
        std::cout << 0;
        return 0;
    }
    
    for(size_t i = 1; ; i++) {
        if(d == ((i * (i + 1)) / 2)) {
            std::cout << i;
            return 0;
        }
        else if(d < ((i * (i + 1)) / 2)) {
            std::cout << 0;
            return 0;
        }
    }
    return 0;
}
