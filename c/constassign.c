#include <stdio.h>

int main()
{
    const char *a = "Hello";
    const char *b;
    b = a;
    char * const c;
    printf("%s\n", b);
}
