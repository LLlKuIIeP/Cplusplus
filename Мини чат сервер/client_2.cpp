#include <iostream>
#include <string>

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SIZE 1024

//#include <stdio.h>
/*int set_nonblock(int fd) {
    int flags;
#if defined(O_NONBLOCK)
    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    flags = 1;
    return ioctl(fd, FIOBIO, &flags);
#endif
}*/


int read_socket(int fd) {
	//std::string str(SIZE, '\0');
	int recv_size = 0;

	//static char buf[SIZE];
		while(true) {
			//std::cout << str.capacity() << std::endl;
			char buf[SIZE];
			std::string str(SIZE, '\0');
			//recv_size = recv(fd, buf, sizeof(buf), MSG_NOSIGNAL);
			recv_size = recv(fd, &(str.front()), str.capacity(), MSG_NOSIGNAL);
			if(recv_size > 0) {
				//std::cout << buf << std::endl;
				//memset(buf, '\0', SIZE);
				//printf("\r\n\r%s", &(str.front()));
				std::cout << str << std::endl;
				//str.clear();
			}
			else {
				std::cout << "buf" << std::endl;
			}

		}


	
}



int main()
{
	int MasterSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
							
	struct sockaddr_in SockAddr;
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port = htons(12345);
	SockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 127.0.0.1

/*	set_nonblock(MasterSocket);

	int EPoll = epoll_create1(0);
	
	struct epoll_event Event;
	Event.data.fd = MasterSocket;
	Event.events = EPOLLIN;
	
	epoll_ctl(EPoll, EPOLL_CTL_ADD, MasterSocket, &Event);*/
	
	if(connect(MasterSocket, (struct sockaddr *)(&SockAddr), sizeof(SockAddr)) == 0) {
		std::string str(32, '\0');

/*		struct epoll_event Events[1];
		unsigned N = epoll_wait(EPoll, Events, MAX_EVENTS, -1);*/

		int recv_size = recv(MasterSocket, &(str.front()), str.size(), MSG_NOSIGNAL);

		if(recv_size > 0) {
			std::cout << str << std::endl;
		}
		read_socket(MasterSocket);
		//recv_size = recv(MasterSocket, &(str.front()), str.size(), MSG_NOSIGNAL);
		//char out_buf[] = "Client 1";
		//send(MasterSocket, out_buf, sizeof(out_buf), MSG_NOSIGNAL);
		//cout << "Out: " << out_buf << endl;

/*		char in_buf[BUF_SIZE];
		recv(MasterSocket, in_buf, BUF_SIZE, MSG_NOSIGNAL);
		std::cout << in_buf << std::endl;*/

		shutdown( MasterSocket, SHUT_RDWR );
		close( MasterSocket );
		
	}

	return 0;
}
