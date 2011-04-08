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
int main(void)
{
    struct my_msgbuf buf;
    char *ptr = (char *)malloc(sizeof(char) * 200);
    int msqid;
    key_t key;
    if ((key = ftok("isense", 'B')) == -1)
    {
        perror("ftok");
        exit(1);
    }
    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1)
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

    while(fgets(ptr, sizeof ptr, stdin) != NULL)
    {
        int len = strlen(ptr);
        /* ditch newline at end, if it exists */
        if (ptr[len-1] == '\n')
        {
            ptr[len-1] = '\0';
        }

        if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
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

