#include <stdio.h>

int main()
{
    const char *a = "Hello";
    const char *b;
    b = a;
    char array[50];
    char * const c = array;
    printf("%s\n", b);
}
