#include <signal.h>
#include <stdio.h>

void terminate (int signal)
{
//    printf("Caught signal %d \n", signal);
//    printf("Caught signal %d \n", signal);
//    printf("Caught signal %d \n", signal);
}

int main()
{
    signal(SIGTERM, (void *)terminate);
    signal(SIGINT, (void *)terminate);
    while(1)
    {
//        printf("Sleeping in while loop\n");
//        sleep(1);
    }
}
