#include <iostream>
#include <set>
#include <algorithm>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

#define POLL_SIZE 2048

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
	
	set<int> SlaveSockets;
	
	struct sockaddr_in SockAddr;
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port = htons(12345);
	SockAddr.sin_addr.s_addr = htonl(INADDR_ANY); //0.0.0.0
	
	bind(MasterSocket, (struct sockaddr *)(&SockAddr), sizeof(SockAddr));
	
	set_nonblock(MasterSocket);
	
	listen(MasterSocket, SOMAXCONN);

	struct pollfd Set[POLL_SIZE];
	Set[0].fd = MasterSocket;
	Set[0].events = POLLIN;
	
	while(true) {
		unsigned int Index = 1;
		for(auto Iter = SlaveSockets.begin(); 
				 Iter != SlaveSockets.end(); 
				 Iter++) {
			Set[Index].fd = *Iter;
			Set[Index].events = POLLIN;
			Index++;
		}
		
		unsigned int SetSize = 1 + SlaveSockets.size();
		
		poll(Set, SetSize, -1);
		
		for(unsigned int i = 0; i < SetSize; i++) {
			if(Set[i].revents & POLLIN) {
				if(i) {
					static char Buffer[1024];
					int RecvSize = recv(Set[i].fd, Buffer, 1024, MSG_NOSIGNAL);
					if(RecvSize == 0 && errno != EAGAIN) {
						shutdown(Set[i].fd, SHUT_RDWR);
						close(Set[i].fd);
						SlaveSockets.erase(Set[i].fd);
					}
					else if (RecvSize > 0) {
						send(Set[i].fd, Buffer, RecvSize, MSG_NOSIGNAL);
					}
				}
				else {
					int SlaveSocket = accept( MasterSocket, 0, 0 );
					set_nonblock(SlaveSocket);
					SlaveSockets.insert(SlaveSocket);
				}
			}
		}
	}
return 0;
}
