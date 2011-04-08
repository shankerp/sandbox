#include <stdio.h>
#include <stdlib.h>

#define TSSKIP 4

int main(int argc, char *argv[])
{
    FILE *read, *write;
    unsigned char buf[188];
    if (argc < 3)
    {
        printf("Usage <exe> <inputfile> <o/p file>\n");
        exit(-1);
    }

    read = fopen(argv[1], "rb");
    write = fopen(argv[2], "wb");

    if(read == NULL || write == NULL)
    {
        printf("Error opeining file\n");
        exit(-1);
    }

    fseek(read, TSSKIP, SEEK_CUR);
    while(188 == fread(buf, 1, 188, read))
    {
        fwrite(buf, 1, 188, write);
        fseek(read, TSSKIP, SEEK_CUR);
    }
}
