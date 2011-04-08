#include <iostream>

class overload
{
    public:
    void func(int a, int b)
    //void func(int a, int b = 0)  This will throw compilation error
    {
        std::cout << "Two params " << a << " " << b << std::endl;
    }

    void func(int a)
    {
        std::cout << "One param " << a << " " << std::endl;
    }
};

int main()
{
    overload a;
    a.func(1);
    a.func(1, 2);
}
