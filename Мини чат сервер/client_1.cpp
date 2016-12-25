#include <iostream>
#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SIZE 1024

int read_socket(int fd) {
	std::string str(SIZE, '\0');
	int recv_size = 0;
		while(true) {
			recv_size = recv(fd, &(str.front()), str.size(), MSG_NOSIGNAL);

			if(recv_size > 0) {
				std::cout << str << std::endl;
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
	
	if(connect(MasterSocket, (struct sockaddr *)(&SockAddr), sizeof(SockAddr)) == 0) {
		std::string str(32, '\0');

		int recv_size = recv(MasterSocket, &(str.front()), str.size(), MSG_NOSIGNAL);

		if(recv_size > 0) {
			std::cout << str << std::endl;
		}
		
		//recv_size = recv(MasterSocket, &(str.front()), str.size(), MSG_NOSIGNAL);
		char out_buf[] = "Hello";
		send(MasterSocket, out_buf, sizeof(out_buf), MSG_NOSIGNAL);
		//cout << "Out: " << out_buf << endl;

/*		char in_buf[BUF_SIZE];
		recv(MasterSocket, in_buf, BUF_SIZE, MSG_NOSIGNAL);
		std::cout << in_buf << std::endl;*/

		shutdown( MasterSocket, SHUT_RDWR );
		close( MasterSocket );
		
	}

	return 0;
}
