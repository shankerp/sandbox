#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
    FILE *fp = NULL;
    char array[20];
    unsigned long long int s64_first = 0, s64_next = 0, s64_count = 0;

    if (argc != 2)
    {
        printf("Usage: <Exe> <Seq. File>\n");
        exit (1);
    }

    fp = fopen(argv[1], "rb");
    if (fp == NULL)
    {
        printf("Unable to open file\n");
        exit(1);
    }

    fgets(array, 20, fp);
    s64_first = atoll(array);

    while(1)
    {
        memset(array,0,20);
        if (NULL == fgets(array, 20, fp))
        {
            break;
        }
        s64_next = atoll(array);
        if ((s64_next - s64_first) != 1)
        {
            printf("Sequence mismatch in line %lld\n", s64_count);
            printf("Prev seq num = %lld\n", s64_first);
            printf("Current seq num = %lld\n", s64_next);
        }
        s64_first = s64_next;
        s64_count ++;
    }
}
