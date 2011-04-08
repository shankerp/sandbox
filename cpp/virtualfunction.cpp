#include <iostream>

class Base {
    public:
    virtual void virtualFunction() { std::cout << "Inside Base Class" << std::endl; }
    void nonVirtualFunction() { std::cout << "Non Virtual Inside Base Class" << std::endl; }
};

class Derived : public Base {
    public:
    virtual void virtualFunction() { std::cout << "Inside Derived Class" << std::endl; }
    void nonVirtualFunction() { std::cout << "Non Virtual Inside Derived Class" << std::endl; }
};

class SecondBase : public Base {
    public:
    virtual void virtualFunction() { std::cout << "Inside SecondBase Class" << std::endl; }
    void nonVirtualFunction() { std::cout << "Non Virtual Inside SecondBase Class" << std::endl; }
};

class SecondDerived : public Derived {
    public:
    virtual void virtualFunction() { std::cout << "Inside SecondDerived Class" << std::endl; }
    void nonVirtualFunction() { std::cout << "Non Virtual Inside SecondDerived Class" << std::endl; }
};

int main()
{
    Base *a, *b, *c, *d;
    a = new Base();
    b = new Derived();
    c = new SecondBase();
    d = new SecondDerived();

    a->virtualFunction();
    b->virtualFunction();
    c->virtualFunction();
    d->virtualFunction();

    a->nonVirtualFunction();
    b->nonVirtualFunction();
    c->nonVirtualFunction();
    d->nonVirtualFunction();

    static_cast<Base *>(a)->nonVirtualFunction();
    static_cast<Derived *>(b)->nonVirtualFunction();
    static_cast<SecondBase *>(c)->nonVirtualFunction();
    static_cast<SecondDerived *>(d)->nonVirtualFunction();
}
