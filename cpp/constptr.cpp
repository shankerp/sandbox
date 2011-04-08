#include <stdio.h>
int main()
{
        int a = 2;
            int * const ptr = &a;
                *ptr = 3;
                printf("%d\n", a);
}
