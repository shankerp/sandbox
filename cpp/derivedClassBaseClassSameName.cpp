#include <iostream>

namespace base 
{
    class klass
    {
        public:
        int a;
    };

    int y;
}

namespace derived
{
    class klass:public base::klass
    {
        public:
            int b;
    };

    int y;
}

int main()
{
    derived::klass a;
    derived::y = 40;
    using namespace base;
    {
    //using derived::y;
    y = 50;
    klass b;
    a.a = 10;
    a.b = 20;
    b.a = 30;
    derived::klass c;
    c.a = 10;
    c.b = 20;
    std::cout << a.a << " " << a.b << std::endl;
    std::cout << b.a << " " << std::endl;
    std::cout << y << " " << base::y << " " << derived::y << std::endl;
    }
    //using base::y;
    using namespace derived;
    {
    std::cout << y << " " << base::y << " " << derived::y << std::endl;
    }
}
