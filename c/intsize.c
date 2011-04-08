#include <stdio.h>
#include <math.h>

int main()
{
    unsigned long long a = (8 * (sizeof(int)));
    printf("Sizeof int is %d\n", sizeof(int));
    printf("a is %lld\n", a);
    a = pow(2, a);
    a = pow(2, (8 * sizeof(int)));
    printf("Max value is %lld\n", a);
}
