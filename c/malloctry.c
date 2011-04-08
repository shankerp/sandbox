#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int malloctry(char *array)
{
    array = (char *)malloc(10 * sizeof(char));
    strcpy(array, "Hello");
}

int main()
{
    char *array;
    malloctry(array);
    printf("%s", array);
}
