#include "stdio.h"

static char* func(int i)
{
    switch(i)
    {
        case 1:
            return "ONE";
        case 2:
            return "TWO";
    }
}

int main()
{
    printf("%s %s\n", func(1), func(2));
}
