#include <iostream>

using namespace std;

class myclass
{
    int a;
    public:
    myclass():
        a(10)
    {
    }
    void printa(void) { cout << a << endl; }
};

//myclass::myclass():a(10) {}

int main ()
{
    myclass b;
    b.printa();
}
