#include <iostream>

using namespace std;

class mycomplex {
    private:
    float x, y;
    public:
    mycomplex() {}
    mycomplex(float a) {x = y = a;}
    mycomplex(float real, float imag) { x = real ; y = imag;}

    friend mycomplex sum(mycomplex, mycomplex);
    friend void show(mycomplex);
};

mycomplex sum(mycomplex c1, mycomplex c2)
{
    mycomplex c3;
    c3.x = c1.x + c2.x;
    c3.y = c1.y + c2.y;
    return c3;
}

void show(mycomplex c)
{
    cout << c.x << " + j" << c.y << endl;
}

int main()
{
    mycomplex A(2.7, 3.5);
    mycomplex B(1.6);
    mycomplex C;

    C = sum(A, B);
    cout << "A = "; show(A);
    cout << "B = "; show(B);
    cout << "C = "; show(C);

    mycomplex P, Q, R;
    P = mycomplex(2.5, 3.9);
    Q = mycomplex(1.6, 2.5);
    R = sum(P, Q);

    cout << "P = "; show(P);
    cout << "Q = "; show(Q);
    cout << "R = "; show(R);
}
