#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stddef.h>			//	дает определение нулевого указателя hdl == NULL


void printf_IPv4(struct hostent *h) {
	int i;
	char buf[INET_ADDRSTRLEN];
	for(i = 0; h->h_addr_list[i] != NULL; i++) {
		memset(buf, '\0', INET_ADDRSTRLEN);
		printf("%s\n", inet_ntop(AF_INET, h->h_addr_list[i], buf, sizeof(buf)));
	}
}

void printf_IPv6(struct hostent *h) {
	int i;
	char buf[INET6_ADDRSTRLEN];
	for(i = 0; h->h_addr_list[i] != NULL; i++) {
		memset(buf, '\0', INET6_ADDRSTRLEN);
		printf("%s\n", inet_ntop(AF_INET6, h->h_addr_list[i], buf, sizeof(buf)));
	}
}



int main(int argc, char const *argv[])
{
	if(argc == 1) {
		printf("Error1\n");
	}
	else {
		struct hostent *host = gethostbyname(argv[1]);
		if(host == NULL) {
			printf("Error2\n");
		}
		else {
			if(host->h_addrtype == AF_INET) {
				printf_IPv4(host);
			}
			else if(host->h_addrtype == AF_INET6) {
				printf_IPv6(host);
			}
		}
	}
	return 0;
}
