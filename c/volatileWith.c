#include <stdio.h>

int main() {
    int a = 10, b = 100, c = 0, d = 0;

    printf("%d", a + b);

    a = b;
    c = b;
    d = b;

    printf("%d", c + d);

    return 0;
}

