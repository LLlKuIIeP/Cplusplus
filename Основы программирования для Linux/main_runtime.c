#include <stddef.h>     //  определение нулевого указателя NULL
#include <stdbool.h>    //  зарезервированные слова true false
#include <stdio.h>
#include <dlfcn.h>      //  фунции dlopen() и dlsym()

void (*hello_message)(const char *);

//  загрузка библиотеки libHello.so и загрузка функции hello_message
bool init_library()
{
    void *hdl = dlopen("./libHello.so", RTLD_LAZY);
    if(NULL == hdl)
        return false;

    hello_message = (void(*)(const char *))dlsym(hdl, "hello_message");
    if(NULL == hello_message)
        return false;

    return true;
}

int main()
{
    if(init_library())
        hello_message("Vasya");
    else
        printf("Library was not loaded\n");
    return 0;
}
