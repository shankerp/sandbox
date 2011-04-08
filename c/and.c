#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *ptr = NULL;
    int a = 10;

    printf("Address of ptr %p\n", ptr);

    printf("%d\n", (ptr && a));

    ptr = (char *)malloc(sizeof(char));

    printf("%d\n", (ptr && a));

    a = 0;

    printf("Address of ptr %p\n", ptr);

    printf("%d\n", (ptr && a));

    free(ptr);
}
