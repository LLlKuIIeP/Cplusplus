#include <iostream>
#include <type_traits>
#include <cstring>

using namespace std;

namespace section_1_1_1 {
template<typename T>
T max(T a, T b) { return b < a ? a : b; }
} // namespace section_1_1_1

namespace section_1_3_1 {
template<typename RT, typename T1, typename T2>
RT max(T1 a, T2 b) { return b < a ? a : b; }
} // namespace section_1_3_1

namespace section_1_3_2 {
template<typename T1, typename T2>
auto max(T1 a, T2 b) { return b < a ? a : b; }
} // namespace section_1_3_2

namespace section_1_3_3 {
template<typename T1, typename T2>
common_type_t<T1, T2> max(T1 a, T2 b) { return b < a ? a : b; } // common_type_t - не сможет вернуть ссылку
} // namespace section_1_3_3

// перегрузка шаблона
namespace section_1_4 {
template<typename T1, typename T2>
auto max(T1 a, T2 b)
{
    cout << "max_1 return ";
    return b < a ? a : b;
}
template <typename RT, typename T1, typename T2>
RT max(T1 a, T2 b)
{
    cout << "max_2 return ";
    return b < a ? a : b;
}
// don`t work for C-style string-----------
template<typename T>
const T& max(const T &a, const T &b)
{
    cout << "T const& ";
    return b < a ? a : b;
}
const char* max(const char *a, const char *b)
{
    cout << "char const* ";
    return strcmp(b, a) < 0 ? a : b;
}
template<typename T>
const T& max(const T &a, const T &b, const T &c)
{
    cout << "3 T const& ";
    return max(max(a, b), c);
}
//-----------------------------------------

} // namespace section_1_4





int main()
{
    cout << "namespace section_1_1_1: " << section_1_1_1::max(3, 2) << endl;
    cout << "namespace section_1_3_1: " << section_1_3_1::max<double>(3.3, 2) << endl;
    cout << "namespace section_1_3_2: " << section_1_3_2::max<double>(3.3, 7.2) << endl;
    cout << "namespace section_1_3_3: " << section_1_3_3::max<double>(3.3, 7.2) << endl;
    cout << "namespace section_1_4: " << section_1_4::max(4, 7.2) << endl;
    cout << "namespace section_1_4: " << section_1_4::max<long double>(4, 7.2) << endl;

    //const char *s1 = "s_1";
    //const char *s2 = "s_2";
    //const char *s3 = "s_3";
    //auto res = section_1_4::max(s1, s2, s3);
    return 0;
}
