#include <stdio.h>

int main() {
    int a = 10, b = 100, c = 0, d = 0;

    printf("%d\n", a + b);

    a = b;
    printf("a must be 100 but it is %d\n", a);
    c = b;
    printf("c must be 100 but it is %d\n", c);
    d = b;
    printf("d must be 100 but it is %d\n", d);

    printf("Sum of c and d is %d\n", c + d);

    return 0;
}

