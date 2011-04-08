#include <iostream>
#include <memory>
using namespace std;

auto_ptr<int> y;

void func(auto_ptr<int> z)
{
    cout << __LINE__ << "\t" << "Printing y "<< y.get() << endl; // Print non-NULL address i
    cout << __LINE__ << "\t" << "Printing z "<< z.get() << endl; // Print non-NULL address i
    y = z;
    cout << __LINE__ << "\t" << "Printing z "<< z.get() << endl; // Print non-NULL address i
}
int main(int argc, char **argv)
{
    int *i = new int;
    auto_ptr<int> x(i);
    cout << __LINE__ << "\t" << "Printing x "<< x.get() << endl;
 
    y = x;
 
    cout << __LINE__ << "\t" << "Printing x "<< x.get() << endl; // Print NULL
    cout << __LINE__ << "\t" << "Printing y "<< y.get() << endl; // Print non-NULL address i
    func(y);
    cout << __LINE__ << "\t" << "Printing y "<< y.get() << endl; // Print non-NULL address i
    int *raw = y.release();
    cout << __LINE__ << "\t" << "Printing y "<< y.get() << endl; // Print non-NULL address i
    delete raw;
}

