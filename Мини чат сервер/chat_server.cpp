#include "chat_server.h"
#include "new_client_connection.h"
#include "client_disconnection.h"
#include "messages.h"


#define BUF_SIZE 1024
#define MAX_EVENTS 10000


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





int main(int argc, char *argv[])
{
	std::unordered_map<int, std::string> fd_map;

	int MasterSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
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
		
		unsigned N = epoll_wait(EPoll, Events, MAX_EVENTS, -1);
		
		for(unsigned i = 0; i < N; i++) {

			if(Events[i].data.fd == MasterSocket) {
				
				struct sockaddr_in Client_info;
				socklen_t size = sizeof(Client_info);
				int SlaveSocket = accept(MasterSocket, (struct sockaddr *)(&Client_info), &size);
				set_nonblock(SlaveSocket);
					
				struct epoll_event Event;
				Event.data.fd = SlaveSocket;
				Event.events = EPOLLIN;
					
				epoll_ctl(EPoll, EPOLL_CTL_ADD, SlaveSocket, &Event);


				new_client_connection(SlaveSocket, &Client_info, fd_map);
			}
			else {
				static char Buffer[BUF_SIZE];
				memset(Buffer, '\0', BUF_SIZE);


				int RecvResult = recv(Events[i].data.fd, Buffer, BUF_SIZE, MSG_NOSIGNAL);

				if(RecvResult == 0 && errno != EAGAIN) {
					shutdown(Events[i].data.fd, SHUT_RDWR);
					close(Events[i].data.fd);

					shutdown_client_connection(Events[i].data.fd, fd_map);
				}
				else if (RecvResult > 0) {
					std::string letter(Buffer);
					send_message_all(Events[i].data.fd, fd_map, letter);
				}
			}
		}
	}
return 0;
}
