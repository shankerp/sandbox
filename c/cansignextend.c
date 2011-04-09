#include <stdio.h>

int main()
{
    int i = 1;
    if (i == (int)(signed char)i)
        printf("Yes! Can sign extend!\n");
    else
        printf("No! Cannot sign extend!\n");
    return 1;
}
