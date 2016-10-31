all: hello libHello.so

hello: main.c hello.h libHello.so
	gcc main.c -fPIC -L. -lHello -o hello

libHello.so: hello.c hello.h
	gcc -fPIC -shared -o libHello.so hello.c