#include <iostream>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include <errno.h>
#include <cstring>
#include <string>

#include <pthread.h>


#define MAX_EVENTS 32

struct Settings {
	char *ip;
	unsigned int port;
	char *directory;
};

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

void *thread_func(void *value) {
		
	Settings *settings = (Settings *)value;
	 
	 // создаем соединение	
        int MasterSocket = socket(AF_INET, /* IPv4 */
				SOCK_STREAM, /* TCP */
				IPPROTO_TCP);
						
        struct sockaddr_in SockAddr;
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port = htons(settings->port);
		
	int res = inet_pton(AF_INET, settings->ip, &SockAddr.sin_addr.s_addr);
		
	if(res <= 0) {
		std::cerr << "Error: IP address." << std::endl;
	}
		
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
				memset(Buffer, 0, sizeof(Buffer));
				int RecvResult = recv(Events[i].data.fd, Buffer, 1024, MSG_NOSIGNAL);
				if(RecvResult == 0 && errno != EAGAIN) {
					shutdown(Events[i].data.fd, SHUT_RDWR);
					close(Events[i].data.fd);
				}
				else if (RecvResult > 0) {
					static char Buf_OK[] = "HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n";
					static char Buf_NO[] = "HTTP/1.0 404  Not Found\r\n\r\n";
						
					int e = 0;
					while(Buffer[e] != '/') {
						e++;
					}
					
					static char Buf_file[1024];
					memset(Buf_file, 0, sizeof(Buf_file));
					strcat(Buf_file, settings->directory);
						
					int lenDir = strlen(Buf_file);
					if(Buf_file[lenDir - 1] == '/') {
						Buf_file[lenDir - 1] = '\0';
					}

					int k;
					for(k = strlen(Buf_file); Buffer[e] != ' ' && Buffer[e] != '?'; k++) {
						Buf_file[k] = Buffer[e];
						e++;
					}
					Buf_file[k] = '\0';
						
					int fdFile = open(Buf_file, O_RDONLY);
					if(fdFile >= 0) {
						char Buf_read[2048];
						memset(Buf_read, 0, sizeof(Buf_read));
						read(fdFile, Buf_read, sizeof(Buf_read));
							
						char Buf_send[2048];
						memset(Buf_send, 0, sizeof(Buf_send));
							
						strcat(Buf_send, Buf_OK);
						strcat(Buf_send, Buf_read);
						std::cerr << "Buffer_send: " << Buf_send << std::endl;
						send(Events[i].data.fd, Buf_send, strlen(Buf_send), MSG_NOSIGNAL);
						close (fdFile);
					}
					if(fdFile == -1) {
						send(Events[i].data.fd, Buf_NO, strlen(Buf_NO), MSG_NOSIGNAL);
					}

					shutdown(Events[i].data.fd, SHUT_RDWR);
					close(Events[i].data.fd);
				}
			}
		}
	}
}



int main(int argc, char *argv[])
{
	// разбор команд
	Settings settings;
	int opt = getopt(argc, argv, ":h:p:d:");
	
	while(opt != -1) {
		switch(opt) {
			case 'h':
				settings.ip = optarg;
				break;
			case 'p':
				settings.port = atoi(optarg);
				break;
			case 'd':
				settings.directory = optarg;
				break;
			default:
				break;
		}
		opt = getopt(argc, argv, ":h:p:d:");
	}
	
	//создаею потомка
	pid_t pid = fork();

   	// если не удалось запустить потомка
   	if(pid == -1) {
        // вывести на экран ошибку и её описание
        	std::cerr << "Error: Start Daemon failed " 
			<<  std::strerror(errno) << std::endl;
        	return -1;
    	}
    	// если потомок
	if(pid == 0) {
		umask(0);
		
		// создаём новый сеанс, чтобы не зависеть от родителя
		pid_t sid = setsid();
        	// переходим в корень диска, т.е. меняем рабочую директорию
        	chdir("/");
		
		close(STDIN_FILENO);
        	close(STDOUT_FILENO);
        	close(STDERR_FILENO);
        
        	pthread_t thread;
		int x = 1;
		pthread_create(&thread, NULL, thread_func, &settings);
		pthread_join(thread, NULL);
	}

return 0;
}
