#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

void print(std::istream &is, std::istream &is2)
{
    std::merge(std::istream_iterator<int>(is), std::istream_iterator<int>(), std::istream_iterator<int>(is2), std::istream_iterator<int>(), std::ostream_iterator<int>(std::cout));
    //std::copy(std::istream_iterator<int>(is), std::istream_iterator<int>(), std::ostream_iterator<int>(std::cout));
}


int main()
{
    std::ifstream ifile("/home/user/QtProgs/untitled1/file");
    std::ifstream ifile2("/home/user/QtProgs/untitled1/file2");
print(ifile, ifile2);

    cout << "Hello World!" << endl;
    return 0;
}
