#include "solution.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    char *c = "Hello";
    int x = 1;
    stringStat(c, 5, &x);
    printf("Result = %d\n", x);
    printf("Result = %d\n", stringStat(c, 5, &x));
    return 0;
}
