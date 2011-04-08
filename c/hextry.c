#include <stdio.h>

int main()
{
    int i;
    char arr[] = "\r\n2";
    sscanf(arr, "%x", &i);
    printf("%d\n", i);
}
