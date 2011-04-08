#include <iostream>

class base {
    public:
    virtual void hello() { std::cout << "base" << std::endl; }
};

class derived : public base {
    public:
    virtual void hello() { std::cout << "derived" << std::endl; }
    virtual void myderived() { std::cout << "derived function" << std::endl; }
};

class derived2 : public base {
    public:
    virtual void hello() { std::cout << "derived2" << std::endl; }
};

int main()
{
    derived a;
    derived2 b;
    base *c = static_cast<base *>(&a);
    c->hello();
    derived2 *d = static_cast<derived2 *>(c);
    static_cast<derived *>(static_cast<base *>(d))->myderived();
}
