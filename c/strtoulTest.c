#include <stdio.h>
#include <stdlib.h>

int main()
{
    char arr[] = "40/0000/9";
    int i = strtoul(arr, NULL, 16);
    printf("%d %x\n", i, i);
    char *ptr = arr+8;
    i = strtoul(ptr, NULL, 16);
    printf("%d %x\n", i, i);
}
