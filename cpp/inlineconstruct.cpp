#include <iostream>

class Base
{
    int m_value;
protected:
    Base(int);
};

inline Base::Base(int a)
    :m_value(a)
{
}

class Derived : public Base
{
public:
    Derived();
};

Derived::Derived()
    :Base(10)
{
}

int main()
{
    Derived var;
}
