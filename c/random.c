#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rnd = 0;
    while(1)
    {
        rnd=(rand()%((2<<15) - 1 - 5001));
        printf("%d - %d\n", rnd, (rnd + 5001));
        sleep(1);
    }
}
