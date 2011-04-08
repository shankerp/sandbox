#include <iostream>

class Base
{
    public:
    void hello() { std::cout << "Hello! This is base." << std::endl; awesome();}
    virtual void awesome() { std::cout << "Awesome is base." << std::endl;}
};

class Derived : public Base
{
    public:
    void hello() { std::cout << "Hello! This is derived." << std::endl; awesome();}
    void awesome() { std::cout << "Awesome is derived." << std::endl;}
};

int main()
{
    Base* x = new Derived();
    Derived* y = new Derived();
    x->hello();
    y->hello();
}
