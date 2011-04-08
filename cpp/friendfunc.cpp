#include <iostream>
using namespace std;
class A;

class B
{
    public:
        B()
        {
            b = 20;
        }
    private:
        int b;
        friend int operator* (const A&, const B&);
        friend class A;
};

class A
{
    friend class B;
    public:
        A()
        {
            a = 10;
        }
        void printb (B& b) { cout << b.b << endl; }
    private:
        int a;
        friend int operator*(const A&, const B&);
};

int operator* (const A& a, const B& b)
{
    return (a.a * b.b);
}

int main()
{
    A a;
    B b;
    cout << (a*b) << endl;
    a.printb(b);
}
