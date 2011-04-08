#include <stdio.h>
#include <stdarg.h>

#define PARAM_CHECK(func)                   \
    result = func;                        \
    if(result != 1)                         \
    {                                       \
        printf("Error [%d]\n", result);     \
        goto End;            \
    }else { \
        printf("Success\n");\
    }

#define wrong_macro(format,...) fprintf(stderr, format, __VA_ARGS__)
#define right_macro(format,...) fprintf(stderr, format, ##__VA_ARGS__)

#define CHECK_PARAM(...)    \
    result = check_input_param(0, __VA_ARGS__, 0x2423207);   \
    if(result != 1)                         \
    {                                       \
        printf("Error [%d]\n", result);     \
        goto other_end; \
    }else { \
        printf("Success\n");\
    }


int check_input_param(int count, ...)
{
    int rv = 1;
    va_list ap;
    va_start(ap, count);
    while(1)
    {
        void *ptr = va_arg(ap, void*);
        if(ptr == NULL)
        {
            printf("Warning: Argument is NULL\n");
            rv = 0;
            break;
        } else if (ptr == (void *)(0x2423207))
        {
            printf("End of va args\n");
            break;
        }
    }
        va_end(ap);
        return rv;
}

int function(void)
{
    return 0;
}

int function2(void)
{
    return 1;
}

int main()
{
    int result;
    int *a = NULL, *b = NULL, *c = NULL, *d = NULL, *e = NULL;
    PARAM_CHECK(function2())
    PARAM_CHECK(function())

    End:
    wrong_macro("%s\n", "Success\n");
    right_macro("Success\n");
    CHECK_PARAM(a, b, c, d, e)
other_end:        
    return 1;
}
