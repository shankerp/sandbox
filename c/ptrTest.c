#include <stdio.h>

void fun1(char *, char *);

int main()
{
    char arr[] = "Hello";
    char *ptr;
    fun1(ptr, arr);
    printf("%s\n", ptr);
    return 1;
}

void fun1(char *ptr, char *arr)
{
    ptr = arr;
    printf("%s\n", ptr);
}

