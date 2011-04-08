#include <iostream>
#include <memory>
using namespace std;
 
int main(int argc, char **argv)
{
    int *i = new int;
    auto_ptr<int> x(i);
    auto_ptr<int> y;
 
    y = x;
 
    cout << x.get() << endl; // Print NULL
    cout << y.get() << endl; // Print non-NULL address i
}
