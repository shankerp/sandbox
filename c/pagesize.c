#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("PAGESIZE is %d\n", getpagesize());
    return 1;
}
