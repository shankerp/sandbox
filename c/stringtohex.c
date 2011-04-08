#include <stdio.h>

int main()
{
    char array[] = {"1abcdef"};
    int num;
    sscanf(array,"%x",&num);
    printf("%d %x\n", num, num);
}
