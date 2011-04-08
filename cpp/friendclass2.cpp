#include <iostream>

using namespace std;

class abc;

class xyz
{
    int x;
    public:
    void setvalue(int i) {
        x = i;
    }
    friend void max(xyz, abc);
};

class abc
{
    int a;
    public:
    void setvalue(int i) {a = i;}
    friend void max(xyz, abc);
};

void max(xyz m, abc n)
{
    if(m.x >= n.a) {
        cout << m.x;
    } else {
        cout << n.a;
    }
    cout << "\n";
}

int main()
{
    abc a;
    a.setvalue(10);
    xyz x;
    x.setvalue(20);
    max(x, a);
    return 0;
}
