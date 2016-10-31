#include <stdio.h>
#include <dlfcn.h>    //	dlopen() dlsym() 
#include <stdbool.h>  //	bool
#include <string.h>
#include <stdlib.h>


bool load_library(const char *lib_name, const char *func_name, const int n) {
	int (*fun)(int);
	char lib[strlen(lib_name) + 2];
	lib[0] = '.';
	lib[1] = '/';
	lib[2] = '\0';

	strcat(lib, lib_name);
	void *hdl = dlopen(lib, RTLD_LAZY);
	if(hdl == NULL) {
		printf("Cannot load library: %s\n", lib_name);
		return false;
	}

	fun = (int (*)(int))dlsym(hdl, func_name);
	if(fun == NULL) {
		printf("Cannot load function \"%s\" in library \"%s\"\n", func_name, lib_name);
		return false;
	}

	printf("%d\n", fun(n));
	return true;
}


int main(int argc, char* argv[])
{
	load_library(argv[1], argv[2], atoi(argv[3]));

	return 0;
}
