#include <iostream>
#include <nanomsg/nn.h>
#include <nanomsg/pair.h>
#include <nanomsg/pipeline.h>
#include <nanomsg/ipc.h>
#include <nanomsg/inproc.h>
#include <nanomsg/tcp.h>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;


    int sock_1 = nn_socket(AF_SP, NN_PAIR);
    int sock_2 = nn_socket(AF_SP, NN_PAIR);

    auto ok = nn_bind(sock_1, "inproc://asdasd");
    cout << ok << endl;
    ok = nn_connect(sock_2, "inproc://asdasd");
cout << ok << endl;
    ok = nn_send(sock_1, "a", 1, 0);
cout << ok << endl;
    char buf[1];
    auto s = nn_recv(sock_2, &buf, 1, NN_DONTWAIT);
cout << buf << endl;
    cout << "Hello World!" << endl;
    return 0;
}
