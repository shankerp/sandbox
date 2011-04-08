#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *ptr = getenv("TESTENV");
    if (ptr) {
        printf("TESTENV=%s\n", ptr);
    }
}
