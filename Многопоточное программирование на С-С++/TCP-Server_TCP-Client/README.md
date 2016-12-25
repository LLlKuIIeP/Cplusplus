
### socket()

Создает сокет и возвращает дескриптор сокета.

    int socket(int domain, int type, int protocol);
**domain**(домен) может быть следующим:
 
 - AF_INET - для IPv4,
 - AF_INET6 - для IPv6,
 - AF_UNIX - для Unix-сокетов

**type**(тип) может быть следующий:

 - SOCK_STREAM - для TCP,
 - SOCK_DGRAM - для UDP.

**proto**(протокол)

 - IPPROTO_TCP - TCP (явное указание, может быть и - 0)


### bind()

Осуществляет "привязку" IP-адреса и порта к серверному сокету (в том числе дейтаграмному).

    bind(int sockfd, 
		 struct sockaddr *addr, 
		 socklet_t addrlen);

Первый параметр - дескриптор сокета.

    int sockfd = socket(...);

Второй параметр - структура (IPv4).

Структура называется **sockaddr_in** ---> **_in** означает **INET** (AF_INET).

    struct sockaddr_in sa;

Первым делом указывается "домен" - **AF_INET**. Это необходимо сделать для того, чтобы было понимание, к какому типу впоследствии приводить **sockaddr**.

    sa.sin_family = AF_INET;

Далее, указывается порт. Указывать его нужно в виде числа в сетевом порядке байт. Для того, чтобы этот порядок байт получить, используем функцию **htons** (для 16-битного числа, коим и является порт. А для 32-битного числа, например, для адреса - **htonl**).

    sa.sin_port = htons(12345);

И, наконец, указывается адрес, к которому привязываем сокет.
Можно использовать константы, пример работы на одной машине.

В случае клиента подключение идет к собственной машине - 127.0.0.1

    sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

Сервер привязывает сокет на все сетевые интерфейсы сервера (в том числе локальному клиенту - 0.0.0.0).

    sa.sin_addr.s_addr = htonl(INADDR_ANY); 

Устаревшая функция **inet_addr** (только для AF_INET):

    sa.sin_addr.s_addr = inet_addr("10.0.0.1");

Современная функция **inet_pton** (AF_INET и AF_INET6):

    inet_pton(AF_INET, "10.0.0.1", &sa);

### Unix

    struct sockaddr_un sa;
    sa.sun_family = AF_UNIX;
    strcpy(sa.sun_path, "/tmp/demo.sock"); // Путь до сокета.

Третий параметр - размер структуры, которая была передана вторым параметром.

    sizeof(sa)

Возвращает:

0 - успех

-1 - ошибка

### listen()
Переводит сокет в режим приема новых соединений (TCP). Два параметра:

    int listen(int sockfd, int backlog);

**sockfd** - дескриптор сокета
**backlog** - максимальное длина очереди ожидающих соединения. Предельное значение - **SOMAXCONN** = 128.
Возвращает:

0 - успех

-1 - ошибка

###accept()

Принимает новое соединение и возвращает дескриптор на него.
Слушает сокет.

    int accept(int sockfd, 
			   struct sockaddr *addr, 
			   socklen_t *addrlen);

Тут важно акцентировать внимание на параметрах **addr** и **addrlen**. Они могут быть NULL и NULL, а могут быть указателями, и тогда по **addr** станет доступна структура (например, **sockaddr_in**), описывающая клиента (в т.ч. его IP-адрес), а по addrlen будет доступна длина этой структуры.

###connect()

Противоположность **accept()**. 

    int connect(int sockfd, 
			    const struct sockaddr *addr, 
			    socklen_t addrlen);

 
Вызывается на клиентском сокете, запускает процесс соединения с сервером. Адрес сервера передается через **addr** и **addrlen**.

###send()/recv()

    size_t send(int sockfd, 
				 const void *buf, 
			     size_t len, 
			     int flags);
			     
    size_t recv(int sockfd, 
			     void *buf, 
			     size_t len, 
			     int flags);

 
Запись в сокет и чтение из сокета. Главное отличие от **read/write** (которые, кстати, тоже допустимы) - наличие флагов **flags**. Мы обычно заинтересованы в флаге **MSG_NOSIGNAL**, который подавляет сигнал **SIGPIPE** при попытке работы с разорванным соединением.

###shutdown()

Разрываем соединение - на чтение или/и на запись.
Два параметра, дескриптор и на что разрываем соединение.

    int shutdown(int sockfd, 
			     int how /* SHUT_RD 
					SHUT_WR 
					SHUT_RDWR */
				 );
	 
SHUT_RD - чтение

SHUT_WR - запись

SHUT_RDWR - на чтение и запись

###sendto()/recvfrom()

Это версии **send/recv** для **UPD**. Они содержат параметры **addr** и **addrlen**, необходимые для **UDP** (адрес получателя или отправителя).

    size_t sendto(int sockfd, 
				   const void *buf, 
				   size_t len, 
				   int flags, 
				   const struct sockaddr *dest_addr, 
				   socklen_t addrlen);
    
    size_t recvfrom(int sockfd, 
					 void *buf, 
					 size_t len, 
    				 int flags, 
    				 struct sockaddr *src_addr, 
    				 socklen_t *addrlen);


###Перевод сокетов в неблокирующий режим

    int set_nonblock(int fd)
    {
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

[Полезно](https://rsdn.ru/article/unix/sockets.xml)


----------
###Отладка
 - Утилита **screen** для терминала
 - **man** - мануал (пример: **man socket** - мануал по сокету)

 **man strace** - полезно

 - **strace** - отладчик (пример: **strace ./server** - работает ли сервер, выводит все системные вызовы)

**strace ./server 2> server.log** - сохранить в лог

 - **gdb** - тоже отладчик (пример: **gdb ./server**)
 - **telnet** - утилита для отладки программы (подключается по **IP** и порту к серверу)

`telnet 127.0.0.1 12345`

`Trying 127.0.0.1...`

`Connected to 127.0.0.1.`

`Escape character is '^]'`
	
 - **ps aux | fgrep server** - вторая колонка - дескриптор сервера
выводит в формате:

`user      4915  0.0  0.3  10656  1916 pts/9    S+   20:07   0:00 fgrep --color=auto server`

`user      4769  0.0  0.2  12776  1432 pts/0    S+   19:55   0:00 ./server` - важна вторая колонка

 - **lsof -p №дескриптора** больше деталей 
 пример: **lsof -p 4769**  и её вывод

`server  4769 user    3u  IPv4  26932      0t0    TCP *:12345 (LISTEN)`

`server  4769 user    4u  IPv4  27099      0t0    TCP localhost:12345->localhost:56188 (ESTABLISHED)`

`server  4769 user    5u  IPv4  27366      0t0    TCP localhost:12345->localhost:56189 (ESTABLISHED)`

3 - сервер

4 и 5 - клиенты
