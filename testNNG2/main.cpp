#include <iostream>
#include <nanomsg/nn.h>
#include <nanomsg/pair.h>
#include <nanomsg/pipeline.h>
#include <nanomsg/ipc.h>
#include <nanomsg/inproc.h>
#include <nanomsg/tcp.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

constexpr size_t N = 1'073'741'824; // 1GB

int main()
{
    cout << "Hello World!" << endl;

    int sock_2 = nn_socket(AF_SP, NN_PAIR);
    auto ok = nn_connect(sock_2, "ipc:///asdasd");
    cout << ok << endl;

//    double x;
//while (nn_recv(sock_2, &x, sizeof(x), NN_DONTWAIT) != 0)
//{
//    cout << x << endl;
//}
   std::vector<int> vec(N + N, 0);
    char buf[5];
    buf[4] = '\0';
    //auto recv = nn_recv(sock_2, &buf, sizeof(buf), NN_DONTWAIT);
    //auto recv = nn_recv(sock_2, buf, 4, 0);

    //cout << recv << buf << endl;
    auto recv = nn_recv(sock_2, vec.data(), vec.size()*sizeof(int), 0);

    cout << recv << endl; 
    std::ostream_iterator<int> out_it(std::cout, ", ");
    std::copy(vec.begin(), vec.end(), out_it);// << endl;

    cout << "Hello World!" << endl;
    return 0;
}
