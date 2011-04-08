#include <stdio.h>
#include <stdlib.h>

int hextodec(int num)
{
    int j = num%16;
    char arr[30];
    sprintf(arr, "%d", num);
    sscanf(arr, "%d", &num);
    return num;
}

int main()
{
    int i;
    printf("enter the hex:\n");
    scanf("%x", &i);
    i = hextodec(i);
    printf("Decimal value is %d\n", i);
}
