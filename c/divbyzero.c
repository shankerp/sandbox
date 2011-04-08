#include <stdio.h>

int main()
{
    float i = 0;
    float j = 1;

    float k = j/i;
    float l = i/k;
    float m = k/i;
    float n = k/k;

    printf("K value is %f\n", k);
    printf("L value is %f\n", l);
    printf("M value is %f\n", m);
    printf("N value is %f\n", n);
}
