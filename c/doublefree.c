#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int **ptr;
    int i = 0;
    ptr = malloc(5 * sizeof(int));
    for (i = 0; i < 5; i++)
    {
        ptr[i] = malloc(sizeof(int));
    }
    for (i = 0; i < 5; i++)
    {
        free(ptr[i]);
    }
    free(ptr);
}
