#ifndef CLASS_A
#define CLASS_A

#include "classb.h"

class B;

class A {
    B* b;
    public:
    int val() { return 0; }
};
#endif
