#include <stdio.h>

#ifdef CUSTOM_APP
#define TEST_APP \
    /*Macro */
    1
#endif

int main()
{
#ifdef TEST_APP
    printf("Local Definition More Priority\n");
#else
    printf("Compile Flags more priority\n");
#endif
}
