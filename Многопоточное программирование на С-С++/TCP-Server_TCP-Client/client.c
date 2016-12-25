#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int MasterSocket = socket(
							AF_INET, /* IPv4 */
							SOCK_STREAM, /* TCP */
							IPPROTO_TCP);
							
	struct sockaddr_in SockAddr;
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port = htons(12345);
	SockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	
	connect(MasterSocket, (struct sockaddr *)(&SockAddr), sizeof(SockAddr) );

		
		char Buffer[] = "PING";
		send( MasterSocket, Buffer, 4, MSG_NOSIGNAL );
		recv( MasterSocket, Buffer, 4, MSG_NOSIGNAL );
		
		shutdown( MasterSocket, SHUT_RDWR );
		close( MasterSocket );
		
		printf( "%s\n", Buffer);
	
return 0;
}
