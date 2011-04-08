#include <stdio.h>
#include <string.h>

int main()
{
    char array[50];
    char *ptr = array;

    strcpy(ptr, "Hello");
    printf("%s\n", ptr);
}
