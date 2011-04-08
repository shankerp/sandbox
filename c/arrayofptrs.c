#include <stdio.h>

void func(char *a[], char *b[], int length)
{
    int i = 0;
    for (i = 0; i < length; i++) {
        printf("%s %s\n", a[i], b[i]);
    }
}

void func2(char *a[], char *b[], int length)
{
    func(a, b, length);
}

int main()
{
    char *a[10] = {
        "1Hello",
        "2Hello",
        "3Hello",
        "4Hello",
        "5Hello",
        "6Hello",
        "7Hello",
        "8Hello",
        "9Hello",
        "10Hello"
    };
    func2(a, a, 10);
}
