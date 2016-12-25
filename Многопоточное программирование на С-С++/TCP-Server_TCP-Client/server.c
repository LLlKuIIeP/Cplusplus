#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

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
	
	listen(MasterSocket, SOMAXCONN);

	while(1) {
		int SlaveSocket = accept( MasterSocket, 0, 0 );
		
		char Buffer[5] = {0, 0, 0, 0, 0};
		
		unsigned int counter = 0;
		while(counter < 4) {
			int res = recv( SlaveSocket, Buffer + 4 - counter, counter, MSG_NOSIGNAL );
			if(res < 4) {
				counter += res;
			}
		
		}
		send( SlaveSocket, Buffer, 4, MSG_NOSIGNAL );
		
		shutdown( SlaveSocket, SHUT_RDWR );
		close( SlaveSocket );
		
		printf( "%s\n", Buffer);
	}
	
return 0;
}
