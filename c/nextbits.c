#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

/* Swap bytes in 32 bit value.  */
#define SWAP(x) \
     ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) |           \
      (((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24))

#ifndef QUIET
#define PRINT_ARGS(param, rest...)              printf(param, ##rest)
#else
#define PRINT_ARGS(param, rest...)
#endif

int offset = 0;
//char buf[] = {0x47, 0x40 , 0x00 , 0x30 , 0xA6 , 0x00 , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF};
char *ptr;

unsigned int nextbits(unsigned int number, char **ptr)
{
    unsigned int out;
    out = SWAP((int) (*(int *)(*ptr)));
    out = (out << offset)>>(32 - number);
    *ptr += (offset + number)/8;
    offset = (offset + number)%8;
    return out;
}

int bytealigned(void)
{
    return (!offset) ? 1 : 0;
}

void next_start_code(void)
{
    while(!bytealigned())
    {
        nextbits(1, &ptr);
    }
    while(0x000001 != nextbits(24, &ptr))
    {
        ;
    }
}

int main(int argc, char *argv[])
{
    unsigned int i;
    int fd, outFd;
    int count = 0, bytesRead, offset = 0, retValue;
    struct stat statusbuf;
    int filesize;

    if (argc != 3)
    {
        PRINT_ARGS("Usage wrong\n");
        exit(1);
    }
    fd = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    outFd = open(argv[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    retValue = fstat(fd, &statusbuf);
    if (retValue == -1)
    {
        perror("Error in file status\n");
        exit(1);
    }
    ptr = (char *)mmap(NULL, statusbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("Error in memory mapping\n");
        exit(1);
    }
    filesize = statusbuf.st_size;
    while(filesize > 0)
    {
//        bytesRead = pread(fd, buf, 188, offset);
        while(count != 188)
        {
            i = nextbits(8, &ptr);
            PRINT_ARGS("%02x  ", i);
            (bytealigned()) ?  PRINT_ARGS("byte aligned\n") : PRINT_ARGS("\tbyte not aligned\n");
            count += 1;
            if(!(count%18))
            {
                PRINT_ARGS("\n");
            }
        }
        PRINT_ARGS("\n");
//        pwrite(outFd, buf, 188, offset);
        count = 0;
        offset += 188;
//        ptr = buf;
        if (bytesRead != 188)
        {
            break;
        }
        break;
    }
    PRINT_ARGS("\n");
    return 1;
}
#if 0
long long int globalQueue;
int bitsFree = 64;

nextbits(unsigned int number)
{
    int bitstream;

    if (bitsFree >= 32)
    {
        //Add bits to cache
    }
    bitstream = (globalQueue >> ( number))
}
#endif

#if 0
/*
 * K & R
 */
unsigned int nextbits(unsigned int x, int p, int n) 
{
    return (x >> (p + 1 - n)) & ~(~0 << n);
}

int main(void) 
{
    int x = 0xF994, p = 4, n = 3;
    int z = nextbits(x, p, n);
    PRINT_ARGS("nextbits(%u (%x), %d, %d) = %u (%X)\n", x, x, p, n, z, z);

    return 0;
}
#endif

