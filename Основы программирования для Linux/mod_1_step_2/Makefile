all:
	gcc -fPIC -shared solution.c -o libsolution.so

main: main.c solution.h solution.so
	gcc main.c -fPIC -L. -o main -lsolution
solution.so: solution.c solution.h
	gcc -fPIC -shared solution.c -o libsolution.so


clean:
	-rm main *.so 2>/dev/null
