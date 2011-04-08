#include <iostream>

template <typename T>
class Hello {
    friend T;
    int m_variable;
};

int main()
{
    Hello<int> a;
    a.m_variable = 1;
}
