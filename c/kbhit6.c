#include <stdio.h>
#include <termios.h> 
#include <unistd.h>

#define END_FILE_CHARACTER 0x04  /* ctrl-d is unix-style eof input key*/


int linux_getch(void) 
{
  struct termios oldstuff;
  struct termios newstuff;
  int    inch;
  
  tcgetattr(STDIN_FILENO, &oldstuff);
  newstuff = oldstuff;                  /* save old attributes               */
  newstuff.c_lflag &= ~(ICANON | ECHO); /* reset "canonical" and "echo" flags*/
  tcsetattr(STDIN_FILENO, TCSANOW, &newstuff); /* set new attributes         */
  inch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldstuff); /* restore old attributes     */

  if (inch == END_FILE_CHARACTER) {
    inch = EOF;
  }
  return inch;
}


int main()
{
  int kb_char;

  printf("\n\n  This is a test of a function that (more-or-less)\n");
  printf("  emulates the classic DOS \"getch()\" function.\n\n");
  printf("  The keyboard input is not echoed; each character is\n");
  printf("  is returned to the calling program as a key is pressed.\n\n");
  printf("  For test purposes, this program echos the hex value returned\n");
  printf("  from the keyboard input routine.\n\n");
  printf("Press any key(s)");
  printf(" (the keyboard routine is set so that ctlr-d is EOF).\n\n");
  while ((kb_char = linux_getch()) != EOF) {
      if (kb_char == 27) {
          linux_getch();
          kb_char = linux_getch();
          switch(kb_char) {
          case 65:
              printf("Up Arrow Key\n");
              break;
          case 66:
              printf("Down Arrow Key\n");
              break;
          case 67:
              printf("Right Arrow Key\n");
              break;
          case 68:
              printf("Left Arrow Key\n");
              break;
          default:
              printf("%d\n", kb_char);
              break;
          }
      } else {
    printf("%02X %c %d\n", kb_char, kb_char, kb_char);
      }
  }
  printf("\n\n  Function linux_getch() says that you entered EOF\n\n");
  return 0;
}



