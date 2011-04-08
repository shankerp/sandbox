#include <stdio.h>

typedef enum
{
    zero,
    one,
    two,
    three,
    five = 5,
    six = 7,
    eight,
    minusone = -1,
    minustwo,
    minusthree
}values;

int main()
{
    printf("zero = %d\n \
            one = %d\n \
            two = %d\n \
            three = %d\n \
            five = %d\n \
            six = %d\n \
            eight = %d\n \
            minusone = %d\n \
            minustwo = %d\n \
            minusthree = %d\n",
            zero,
            one,
            two,
            three,
            five,
            six,
            eight,
            minusone,
            minustwo,
           minusthree);
}
