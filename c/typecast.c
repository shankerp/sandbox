#include <stdio.h>

static void func(int *a)
{
    printf("%d\n", *a);
}

int main()
{
    unsigned long long int b = 2;
    func((int *)(&b));
}
