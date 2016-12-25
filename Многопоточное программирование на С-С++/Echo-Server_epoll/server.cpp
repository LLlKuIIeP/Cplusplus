#include <iostream>
#include <set>
#include <algorithm>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

#define MAX_EVENTS 32

using namespace std;

int set_nonblock(int fd) {
    int flags;
#if defined(O_NONBLOCK)
    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    flags = 1;
    return ioctl(fd, FIOBIO, &flags);
#endif
} 

int main(){
	int MasterSocket = socket(
							AF_INET, /* IPv4 */
							SOCK_STREAM, /* TCP */
							IPPROTO_TCP);
	
	struct sockaddr_in SockAddr;
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port = htons(12345);
	SockAddr.sin_addr.s_addr = htonl(INADDR_ANY); //0.0.0.0
	
	bind(MasterSocket, (struct sockaddr *)(&SockAddr), sizeof(SockAddr));
	
	set_nonblock(MasterSocket);
	
	listen(MasterSocket, SOMAXCONN);

	int EPoll = epoll_create1(0);
	
	struct epoll_event Event;
	Event.data.fd = MasterSocket;
	Event.events = EPOLLIN;
	
	epoll_ctl(EPoll, EPOLL_CTL_ADD, MasterSocket, &Event);
	
	while(true) {
		struct epoll_event Events[MAX_EVENTS];
		
		int N = epoll_wait(EPoll, Events, MAX_EVENTS, -1);
		
		for(unsigned int i = 0; i < N; i++) {
			if(Events[i].data.fd == MasterSocket) {
				int SlaveSocket = accept( MasterSocket, 0, 0 );
				set_nonblock(SlaveSocket);
					
				struct epoll_event Event;
				Event.data.fd = SlaveSocket;
				Event.events = EPOLLIN;
					
				epoll_ctl(EPoll, EPOLL_CTL_ADD, SlaveSocket, &Event);
			}
			else {
				static char Buffer[1024];
				int RecvResult = recv(Events[i].data.fd, Buffer, 1024, MSG_NOSIGNAL);
				if(RecvResult == 0 && errno != EAGAIN) {
					shutdown(Events[i].data.fd, SHUT_RDWR);
					close(Events[i].data.fd);
				}
				else if (RecvResult > 0) {
					send(Events[i].data.fd, Buffer, RecvResult, MSG_NOSIGNAL);
				}
			}
		}
	}
return 0;
}
