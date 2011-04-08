#include <stdio.h>

#if 0
    #define eprintf(cool, ...) \
        fprintf(stderr, "[ERR] %d %s %s ", __LINE__, __FUNCTION__, __FILE__); \
        fprintf(stderr, __VA_ARGS__)
    
    #define eeprintf(cool, ...) \
        fprintf(stderr, "[ERR] %d %s %s \n", __LINE__, __FUNCTION__, __FILE__);
#else
    #define eprintf(cool, ...)
    #define eeprintf(cool, ...)
#endif

int main()
{
    eprintf(222, "%s %s\n", "This is", "cool");
    eeprintf();
}
