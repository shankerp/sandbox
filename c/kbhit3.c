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
    changemode(1);

    while(1)
    {
        kbhit();
        ch = getchar();
        printf("%c", ch);
        if (ch == 'q')
        {
            printf("\nQuitting...\n");
            break;
        }
    }

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
    fd_set rdfs;

    FD_ZERO(&rdfs);
    FD_SET (STDIN_FILENO, &rdfs);

    select(STDIN_FILENO+1, &rdfs, NULL, NULL, NULL);
    return FD_ISSET(STDIN_FILENO, &rdfs);

}

