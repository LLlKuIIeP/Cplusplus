all:
	gcc -fPIC -shared solution.c -o libsolution.so

main: main.c solution.h
	gcc main.c -fPIC -L. -o main -lsolution



clean:
	-rm main *.so 2>/dev/null
