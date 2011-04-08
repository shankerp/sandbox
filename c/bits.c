#include <stdio.h>
#include <math.h>

int main()
{
    unsigned char array[4] = {0x0, 0x0, 0x02, 0xa0};
    printf("%d %c\n", array[3], (int)(array[3]));
    printf("%d\n", array[2] << 8 | (int)(array[3]));
    printf("%d\n", atoi(array));
    return 1;
}
