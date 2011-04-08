#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func(char *keymap[], int rows)
{
#if 0
    char *map[rows];
#endif
    char **map = (char **) malloc (sizeof(char *) * rows);

    int count = 0;
    while(count < rows)
    {
        (map[count]) = (char *)malloc(strlen(keymap[count]));
        strcpy((map[count]), (keymap[count]));
        count++;
    }

    int i = 0, j=0;
    while(1)
    {
        if(map[i][j] == '\0')
        {
            j = 0;
            i++;
            printf("\n");
        }
        else
        {
            printf("%c", map[i][j]);
            j++;
        }
        if (i == rows)
        {
            break;
        }
    }
}

int main()
{
    char *keymap[] =
    {
        "2abcABC",
        "3defDEF",
        "4ghiGHI",
        "5jklJKL",
        "6mnoMNO",
        "7pqrsPQRS",
        "8tuvTUV",
        "9wxyzWXYZ",
    };

    func(keymap, 8);
}
