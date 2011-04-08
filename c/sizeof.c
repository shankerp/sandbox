#include <stdio.h>

int main()
{
#if 0
    size_t size = (size_t)(1 + ((int *)0));
    printf("%d\n", size);
#endif
#if 0
    int *a,*s, v=11;
    a=&v;
    s=a;
    a++;
    int intsize=(int)a-(int)s;
    printf("%d",intsize);
#endif
    int a; printf("%u\n",(int)(&a+1)-(int)(&a));
}
