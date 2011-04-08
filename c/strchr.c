#include <string.h>
#include <stdio.h>

int main()
{
    char arr[] = "arib-dc://10.16.22;25.24/40/1000";
    char arr2[] = "/40/0000/";
    char arr3[] = "arib-dc://10.16.22;25.24/40;1000";
    char arr4[] = "/40;0000/";
    char *ptr = NULL;

    ptr = arr + 10;
    do {
    ptr = strchr(ptr, '/');
    ptr++;
    printf("1 Came here\n");
    printf("%s %d\n", ptr, atoi(ptr));
    printf("Came here\n");
    } while(ptr);
}
