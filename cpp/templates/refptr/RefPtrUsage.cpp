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

#if 0
template <typename super, typename duper>
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
#endif

/* print_info is written as template purposely */
template <typename super>
void print_info(super soup, RefPtr<BsClass> &var)
{
    BsClass *raw = var.get();
    std::cout << "RefPtr's Main object points to " << raw << " ";
    if (raw) { // Guess yourself why this check is done. (Hint: if not checked will seg fault)
        std::cout << "Referenced by " << var->refCount() << " objects" << ", Value " << var->variable;
    } else {
        std::cout << "----------------------------------> [BOOM!!]";
    }
    std::cout << std::endl;
}

template <typename duper>
void print_info(duper dupe, PassRefPtr<BsClass> &var)
{
    BsClass *raw = var.get();
    std::cout << "PassRefPtr's Main object points to " << raw << " ";
    if (raw) { // Guess yourself why this check is done. (Hint: if not checked will seg fault)
        std::cout << "Referenced by " << var->refCount() << " objects" << ", Value " << var->variable;
    } else {
        std::cout << "----------------------------------> [BOOM!!]";
    }
    std::cout << std::endl;
}

template <typename super, typename duper>
void process_intro_assign(super soup, duper dupe, int value)
{
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
    std::cout << "Before assigning PassRefPtr to RefPtr ie.[RefPtr = PassRefPtr] " << std::endl;
    std::cout << "===============================================================" << std::endl;
    print_info(0, passRef1);
    print_info(0, ref11);
    std::cout << std::endl;

    passRef1->assign(10);
    ref11 = passRef1;

    std::cout << "After assigning PassRefPtr to RefPtr ie.[RefPtr = PassRefPtr] " << std::endl;
    std::cout << "==============================================================" << std::endl;
    print_info(0, passRef1);
    print_info(0, ref11);
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Before assigning RefPtr to PassRefPtr ie.[PassRefPtr = RefPtr] " << std::endl;
    std::cout << "===============================================================" << std::endl;
    print_info(0, ref2);
    print_info(0, passref22);
    std::cout << std::endl;

    ref2->assign(20);
    passref22 = ref2;

    std::cout << "After assigning RefPtr to PassRefPtr ie.[PassRefPtr = RefPtr] " << std::endl;
    std::cout << "==============================================================" << std::endl;
    print_info(0, ref2);
    print_info(0, passref22);
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Before assigning RefPtr to RefPtr ie.[RefPtr = RefPtr] " << std::endl;
    std::cout << "=======================================================" << std::endl;
    print_info(0, ref3);
    print_info(0, ref33);
    std::cout << std::endl;
 
    ref3->assign(30);
    ref33 = ref3;

    std::cout << "After assigning RefPtr to RefPtr ie.[RefPtr = RefPtr] " << std::endl;
    std::cout << "======================================================" << std::endl;
    print_info(0, ref3);
    print_info(0, ref33);
    std::cout << std::endl;
 
    std::cout << std::endl;
    std::cout << "Before assigning PassRefPtr to PassRefPtr ie.[PassRefPtr = PassRefPtr] " << std::endl;
    std::cout << "=======================================================================" << std::endl;
    print_info(0, passref4);
    print_info(0, passref44);
    std::cout << std::endl;

    passref4->assign(40);
    passref44 = passref4;

    std::cout << "After assigning PassRefPtr to PassRefPtr ie.[PassRefPtr = PassRefPtr] " << std::endl;
    std::cout << "======================================================================" << std::endl;
    print_info(0, passref4);
    print_info(0, passref44);
    std::cout << std::endl;
}

void transfer()
{
    RefPtr<BsClass> ref2(new BsClass);
    PassRefPtr<BsClass> passref22;

    std::cout << "Before transferring PassRefPtr = RefPtr " << std::endl;
    std::cout << "========================================" << std::endl;
    print_info(0, ref2);
    print_info(0, passref22);
    std::cout << std::endl;

    ref2->assign(20);

    /* Transfer to passrefptr */
    passref22 = ref2.release();

    std::cout << "After transferring PassRefPtr = RefPtr " << std::endl;
    std::cout << "========================================" << std::endl;
    print_info(0, ref2);
    print_info(0, passref22);
    std::cout << std::endl;
}

int main()
{
    intro();
    //transfer();
}
