#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

void changemode(int);
int  kbhit(void);
int main(void)
{
    int ch;
    while ( !kbhit() )
    {
        putchar('.');
    }

    ch = getchar();

    printf("\nGot %02x %c %d \n", ch, ch, ch);

    changemode(0);
    return 0;
}

void changemode(int dir)
{
    static struct termios oldt, newt;

    if ( dir == 1 )
    {
        tcgetattr( STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    }
    else
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

int kbhit (void)
{
    changemode(1);
    struct timeval tv;
    fd_set rdfs;

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&rdfs);
    FD_SET (STDIN_FILENO, &rdfs);

    select(STDIN_FILENO+1, &rdfs, NULL, NULL, NULL);
    return FD_ISSET(STDIN_FILENO, &rdfs);

}

