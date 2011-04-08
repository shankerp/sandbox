#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct my_msgbuf
{
    long mtype;
    char *mtext;
};

static void receiver(void)
{
    struct my_msgbuf buf;
    int msqid;
    key_t key;
    if ((key = ftok("isense", 'B')) == -1) 
    {
        /* same key as kirk.c */
        perror("ftok");
        exit(1);
    }
    if ((msqid = msgget(0x2423207, 0644)) == -1) 
    {
        /* connect to the queue */
        perror("msgget");
        exit(1);
    }
    printf("spock: ready to receive messages, captain.\n");

    for(;;) 
    { /* Spock never quits! */
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 2, IPC_NOWAIT) == -1) 
        {
            if (errno == ENOMSG)
            {
                usleep(10*1000);
                continue;
            }
            printf("%d\n", errno);
            perror("msgrcv");
            exit(1);
        }
        printf("Out of msgrcv\n");
        printf("Address of mtext is %p\n", buf.mtext);
        printf("spock: \"%s\"\n", buf.mtext);
    }
}

int main(void)
{
    pthread_t receiverId;
    struct my_msgbuf buf;
    char *ptr = (char *)malloc(sizeof(char) * 200);
    int msqid;
    key_t key;
    if ((key = ftok("isense", 'B')) == -1)
    {
        perror("ftok");
        exit(1);
    }
    if ((msqid = msgget(0x2423207, 0644 | IPC_CREAT)) == -1)
    {
        perror("msgget");
        exit(1);
    }
    printf("MSG Q ID IS %d\n", msqid);
    printf("Enter lines of text, ^D to quit:\n");
    buf.mtype = 2; /* we don't really care in this case */
    printf("Address of ptr is %p\n", ptr);
    buf.mtext = (void *)ptr;
    printf("Address of mtext is %p\n", buf.mtext);

    pthread_create( &receiverId, NULL, (void* (*) (void *))receiver, NULL );
    while(fgets(ptr, (sizeof(char) * 200), stdin) != NULL)
    {
        int len = strlen(ptr);
        /* ditch newline at end, if it exists */
        if (ptr[len-1] == '\n')
        {
            ptr[len-1] = '\0';
        }

        if (msgsnd(msqid, &buf, sizeof(buf.mtext), 0) == -1) /* +1 for '\0' */
        {
            perror("msgsnd");
        }
    }
    if (msgctl(msqid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        exit(1);
    }
    return 0;
}

