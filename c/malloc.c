#include <stdio.h>
#include <stdlib.h>

char *g_ptr;

int main()
{
    char *ptr = NULL;
    if (g_ptr != NULL)
    {
        printf("Global doesn't initialize to null\n");
    }
    else
    {
        printf("global initializes to null\n");
    }
    ptr = (char *)malloc(sizeof(char));
    if (ptr == NULL)
    {
        printf("Good\n");
    }
    else
    {
        printf("bad\n");
    }
    perror("");
}
