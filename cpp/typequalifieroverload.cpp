#include <iostream>

void func(int a)
{
    std::cout << "Unqualified a" << std::endl;
}

// Compiler error : Redefinition
void func(const int a)
{
    std::cout << "Qualified a" << std::endl;
}

int main()
{
    int a;
    const int b = 2;
    func(a);
    func(b);
}
