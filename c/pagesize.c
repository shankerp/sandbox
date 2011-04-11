#include <stdio.h>
#include <unistd.h>


size_t roundUpAllocationSize(size_t request, size_t granularity)
{
    // Round up to next page boundary
    size_t size = request + (granularity - 1);
    size = size & ~(granularity - 1);
    return size;
}

int main()
{
    size_t pageSize = getpagesize();
    printf("PAGESIZE is %d\n", pageSize);
    printf("Rounded Allocation Size is %d\n", 4 * pageSize, pageSize);
    return 1;
}
