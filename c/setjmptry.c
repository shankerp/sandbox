#include <stdio.h>
#include <setjmp.h>
 
static jmp_buf buf;
 
void second(void) {
    printf("second\n");         // prints
    longjmp(buf,1);             // jumps back to where setjmp was called - making setjmp now return 1
    printf("After longjmp\n");  // does not print
}
 
void first(void) {
    second();
    printf("first\n");          // does not print
}
 
int main() {   
    if ( ! setjmp(buf) ) {
        first();                // when executed, setjmp returns 0
    } else {                    // when longjmp jumps back, setjmp returns 1
        printf("main\n");         // prints
        first();                // when executed, setjmp returns 0
    }
 
    return 0;
}

