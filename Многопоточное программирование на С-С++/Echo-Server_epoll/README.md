###Сервер - реализация epoll 
**epoll** - работает в ядре, без постоянного копирования данных, в отличие от **fd_set** или **poll**. Также решает проблему **С10К** (на одном сервере *10000* подключений).
**KQueue** - тоже что **epoll**, только для **FreeBSD** и **OS X** (***epoll - Linux***).

**epoll_create1(0)** - создается дескриптор епола.

	int EPoll = epoll_create1(0);

**struct epoll_event** - структура события для **epoll**
	
	struct epoll_event Event;
	/* Event.data.fd - дескриптор сокета */
	Event.data.fd = MasterSocket;
	/* EPOLLIN - доступность на чтение */
	Event.events = EPOLLIN;

**epoll_ctl** - регистрация события

	epoll_ctl(EPoll, EPOLL_CTL_ADD, MasterSocket, &Event);

**EPoll** - где регистрируем.

**EPOLL_CTL_ADD** - константа, обозначает "добавить дескриптор в епол".

**MasterSocket** - сам дескриптор.

**Event** - событие, которое регистрируем

**epoll_event** - структура одновременных событий.

	struct epoll_event Events[MAX_EVENTS];

**MAX_EVENTS** - число одновременных событий.

**epoll_wait** - ждем, когда насупит событие, которое зарегистрировали ранее.

	int N = epoll_wait(EPoll, Events, MAX_EVENTS, -1);

**MAX_EVENTS** - максимальное число одновременных событий.

-1 - ждать бесконечно.
