#include <iostream>
#include <string>
#include <unordered_map>
#include <cerrno>			// макрос errno
#include <cstring>			//	char * strerror( int errornum );



//		Library for
//	int socket(int domain, int type, int protocol);
//	send(), sendto(), sendmsg()
#include <sys/socket.h>


//		Library for
//	AF_INET 	IPv4 Internet protocols		ip(7)
//	AF_INET6	IPv6 Internet protocols		ipv6(7)
//
//	SOCK_STREAM
//	SOCK_DGRAM
#include <sys/types.h>

//		Library for
//	const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
#include <arpa/inet.h>


#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
