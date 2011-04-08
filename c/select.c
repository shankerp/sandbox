#if 0
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define STDIN 0  /* file descriptor for standard input */

int main()
{
    struct timeval tv;
    fd_set readfds;

    for(;;){
        FD_ZERO(&readfds);
        FD_SET(STDIN, &readfds);

        /* don't care about writefds and exceptfds: */
        select(STDIN+1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(STDIN, &readfds))
            printf("A key was pressed!\n");
        else
            printf("Timed out.\n");
    }
}
#else
#include <stdio.h>
#include <sys/select.h>

int main()
{
    fd_set s_readfds;
    struct timeval s_timeout;
    int i = 0, rv = 0;

    while(1)
    {
        FD_ZERO(&s_readfds);
        FD_SET(0, &s_readfds); //stdin descriptor is 0

        s_timeout.tv_sec = 0;
        s_timeout.tv_usec = (500 * 1000); // Fifty milli seconds

        rv = select(1, &s_readfds, NULL, NULL, &s_timeout);
        perror("");
//        select(1, &s_readfds, NULL, NULL, NULL);
        printf("RV %d\n", rv);

//        if(rv)
        if (1)
        {
            if(FD_ISSET(0, &s_readfds)) //stdin descriptor is 0
            {
                printf("A key was pressed!\n");
                scanf("%d", &i);
                break;
            }
        }
        else
        {
            printf("Select returns -1\n");
        }
    }
}
#endif
