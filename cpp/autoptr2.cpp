
#include <iostream>
#include <memory>
using namespace std;

class X {
public:
  X() { 
     cout << "constructing\n"; 
  }
  ~X() { 
     cout << "destructing\n"; 
  }
  void f() { 
     cout << "Inside f()\n"; 
  }
};

int main()
{
  auto_ptr<X> p1(new X), p2;

  p2 = p1;            // transfer ownership
  p1->f();
  cout << p1.get() << endl;
  p2->f();

  
  X *ptr = p2.get();  // can assign to a normal pointer
  ptr->f();

  return 0;
}
