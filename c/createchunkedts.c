#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef unsigned char uchar;

int main(int argc, char *argv[])
{
    FILE *read, *write;
    uint seed;
    uint chunklength;
    uint filesize;
    uchar buf[32768];
    uchar *ptr = buf;

    if (argc != 3)
    {
        printf("Usage <Exe> <inputfile> <outputfile>\n");
        exit(1);
    }
    read = fopen(argv[1], "rb");
    write = fopen(argv[2], "wb");
    if (read == NULL || write == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    fseek(read, 0, SEEK_END);
    filesize = (uint)ftell(read);
    fseek(read, 0, SEEK_SET);

    while(1)
    {
        chunklength = rand_r(&seed)%32768;
        if (chunklength == 0)
        {
            continue;
        }
        fprintf(write, "%x\r\n", chunklength);
        if (chunklength != fread(ptr, 1, chunklength, read))
        {
            break;
        }
        fwrite(buf, 1, chunklength , write);
        fprintf(write, "\r\n");
    }
}
