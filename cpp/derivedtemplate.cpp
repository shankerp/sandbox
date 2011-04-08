#include <iostream>

template <typename T>
class base
{
    public:
    T a;
    void printbase() { std::cout << a << std::endl ; }
};

template <typename T>
class derived : public base<T>
{
    public:
        void assign(T b) { base<T>::a = b ; }
        void printval() { base<T>::printbase(); } 
};

template <typename T, typename other = derived<T> >
class newderived
{
    public:
        other c;
        void assignother(T d) { c.assign(d); }
        void printother() { c.printval(); }
};

int main()
{
    derived<int> a;
    a.a = 4;
    a.printval();
    newderived<int> b;
    b.assignother(5);
    b.printother();
}
