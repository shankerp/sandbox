#include <iostream>
#include "RefPtr.h"
#include "RefCounted.h"

class BsClass : public RefCounted<BsClass> {
    public:
        void assign(int i) { variable = i; }
        int variable;
};

void moms_real_key()
{
}

template <class super, class duper>
void print_info(super& soup, duper& dupe)
{
    BsClass *raw = soup.get();
    std::cout << "Main object points to " << raw << " ";
    if (raw) { // Guess yourself why this check is done. (Hint: if not checked will seg fault)
        std::cout << "Referenced by " << soup->refCount() << " objects" << " Value " << soup->variable;
    } else {
        std::cout << "----------------------------------> [BOOM!!]";
    }
    std::cout << std::endl;
    raw = dupe.get();
    std::cout << "Main object points to " << raw << " ";
    if (raw) { // Guess yourself why this check is done. (Hint: if not checked will seg fault)
        std::cout << "Referenced by " << dupe->refCount() << " objects" << " Value " << dupe->variable;
    } else {
        std::cout << "----------------------------------> [BOOM!!]";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void intro()
{
    PassRefPtr<BsClass> passRef1(new BsClass);
    RefPtr<BsClass> ref11;

    RefPtr<BsClass> ref2(new BsClass);
    PassRefPtr<BsClass> passref22;

    RefPtr<BsClass> ref3(new BsClass);
    RefPtr<BsClass> ref33;

    PassRefPtr<BsClass> passref4(new BsClass);
    PassRefPtr<BsClass> passref44;

    std::cout << std::endl;
    std::cout << "Before assigning RefPtr = PassRefPtr " << std::endl;
    std::cout << "=====================================" << std::endl;
    print_info(passRef1, ref11);

    std::cout << "Before assigning PassRefPtr = RefPtr " << std::endl;
    std::cout << "=====================================" << std::endl;
    print_info(ref2, passref22);

    std::cout << "Before assigning RefPtr = RefPtr " << std::endl;
    std::cout << "=================================" << std::endl;
    print_info(ref3, ref33);
 
    std::cout << "Before assigning PassRefPtr = PassRefPtr " << std::endl;
    std::cout << "=========================================" << std::endl;
    print_info(passref4, passref44);

    passRef1->assign(10);
    ref11 = passRef1;

    ref2->assign(20);
    passref22 = ref2;

    ref3->assign(30);
    ref33 = ref3;

    passref4->assign(40);
    passref44 = passref4;

    std::cout << std::endl;
    std::cout << "After assigning RefPtr = PassRefPtr " << std::endl;
    std::cout << "====================================" << std::endl;
    print_info(passRef1, ref11);

    std::cout << "After assigning PassRefPtr = RefPtr " << std::endl;
    std::cout << "====================================" << std::endl;
    print_info(ref2, passref22);

    std::cout << "After assigning RefPtr = RefPtr " << std::endl;
    std::cout << "================================" << std::endl;
    print_info(ref3, ref33);
 
    std::cout << "After assigning PassRefPtr = PassRefPtr " << std::endl;
    std::cout << "========================================" << std::endl;
    print_info(passref4, passref44);
}

int main()
{
    intro();
}
