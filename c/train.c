#include <stdio.h>
#include <unistd.h>

int main()
{
    int i = 0;
    printf("\n");
    for (i = 0; i < 10 ; i++ )
    {
        printf("-");
        fflush(stdout);
        usleep(1000*100);
    }
    printf("\n");
}
