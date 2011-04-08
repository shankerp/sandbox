#include <stdio.h>

typedef void (*member)(void);

void localmember(void)
{
    printf("Inside local member\n");
}

typedef struct tag
{
    member ptr;
} a;

a function(void)
{
    a var;
    var.ptr = (member)localmember;
    return var;
}

int main()
{
    a var;
    function().ptr();
}
