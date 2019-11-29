#include <iostream>
#include <nanomsg/nn.h>
#include <nanomsg/pair.h>
#include <nanomsg/pipeline.h>
#include <nanomsg/ipc.h>
#include <nanomsg/inproc.h>
#include <nanomsg/tcp.h>
#include <math.h>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

constexpr size_t N = 1'073'741'824; // 1GB

int main()
{
    cout << "Hello World!" << endl;


    int sock_1 = nn_socket(AF_SP, NN_PAIR);
    //int sock_2 = nn_socket(AF_SP, NN_PAIR);

    auto ok = nn_bind(sock_1, "ipc:///asdasd");
    //cout << ok << endl;
    //ok = nn_connect(sock_2, "ipc:///asdasd");
//cout << ok << endl;

std::vector<int> vec(N + N, 4);
    //char const bufSend[] = "aaaa";
    //auto send = nn_send(sock_1, bufSend, sizeof(bufSend), 0);
    auto send = nn_send(sock_1, vec.data(), vec.size() * sizeof(decltype(vec)::value_type), 0);
cout << send << endl;

    //auto s = nn_recv(sock_2, &bufSend, N, NN_DONTWAIT);
//cout << bufSend << endl;

//char bufSend[1];
//while (nn_recv(sock_2, &bufSend, 1, NN_DONTWAIT) != 0)
//{
//    cout << bufSend << endl;
//}
//
//    cout << "Hello World!" << endl;

std::this_thread::sleep_for(std::chrono::seconds(50));
    return 0;
}
