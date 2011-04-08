#include <iostream>

class A
{
    public:
        A(int b) { a = b; }
        void print() { std::cout << a << std::endl ; }
    private:
        int a;
};

int main()
{
    A a = 37;
    a.print();
}
