#include <iconv.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    iconv_t iconvt;
    iconvt = iconv_open("UTF-16", "UTF-8");
    unsigned char *array = (unsigned char *)malloc(10);
    unsigned char *array2 = (unsigned char *)malloc(20);
    memset(array, 0, 10);
    memset(array2, 0, 20);
    int arraylen = strlen("f40b");
    int array2len = 20;
    strcpy((char *)array, "f40b");
    unsigned char *ptr = array2;
    iconv(iconvt, (char **)(&array), &arraylen, (char **)(&array2), &array2len);
    int i =0;
    for (i = 0; i < 20; i++)
        printf("%x ", ptr[i]);
    printf("\n");
    free(array);
    free(array2);
    array = NULL;
    array2 = NULL;
}
