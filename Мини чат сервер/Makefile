build_all: chat_server client_1 client_2 clean

chat_server: chat_server.o new_client_connection.o client_disconnection.o messages.o
	g++ -std=c++14 -o chat_server chat_server.o new_client_connection.o client_disconnection.o messages.o

chat_server.o: chat_server.cpp chat_server.h new_client_connection.h client_disconnection.h messages.h
	g++ -std=c++14 -c chat_server.cpp

new_client_connection.o: new_client_connection.cpp new_client_connection.h chat_server.h
	g++ -std=c++14 -c new_client_connection.cpp

client_disconnection.o: client_disconnection.cpp client_disconnection.h chat_server.h
	g++ -std=c++14 -c client_disconnection.cpp

messages.o: messages.cpp messages.h chat_server.h
	g++ -std=c++14 -c messages.cpp



client_1: client_1.cpp
	g++ -std=c++14 -o client_1 client_1.cpp

client_2: client_2.cpp
	g++ -std=c++14 -o client_2 client_2.cpp






clean:
	-rm *.o
#	-rm chat_server client_1 client_2
