all: main.o log.o
	g++ -std=c++14 -o main main.o LOG.o 

main.o: main.cpp LOG.h
	g++ -std=c++14 -c main.cpp

log.o: LOG.cpp LOG.h
	g++ -std=c++14 -c LOG.cpp





clean:
	rm -f main.o LOG.o MyLogFile* log_*.log
