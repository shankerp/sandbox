#include <stdio.h>
#include <stdint.h>

void WTFReportAssertionFailure(const char* file, int line, const char* function, const char* assertion);
#define CRASH() do { \
        *(int *)(uintptr_t)0xbbadbeef = 0; \
        ((void(*)())0)(); /* More reliable, but doesn't say BBADBEEF */ \
} while(0)


#define ASSERT(assertion) do \
        if (!(assertion)) { \
                    WTFReportAssertionFailure(__FILE__, __LINE__, __FUNCTION__, #assertion); \
                    CRASH(); \
                } \
while (0)


void WTFReportAssertionFailure(const char* file, int line, const char* function, const char* assertion)
{
    if (assertion)
        printf("ASSERTION FAILED: %s\n", assertion);
    else
        printf("SHOULD NEVER BE REACHED\n");
    printf("%s %d %s\n", file, line, function);
}

int main()
{
    int *ptr = NULL;
    ASSERT(ptr);
    CRASH();
}
