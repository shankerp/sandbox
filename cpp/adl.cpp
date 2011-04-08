#include <iostream>

class NS {
public:
   class T { 
   public:
       void f(T)
       {
           std::cout << "there" << std::endl;
       }
   };

   void f1(T a)
   {
       a.f(a);
       std::cout << "here" << std::endl;
   }
};

NS::T parm;
NS param;

int main() {
   parm.f(parm);                    //  OK: calls  NS::f
   param.f1(parm);                    //  OK: calls  NS::f
   return 0;
}
