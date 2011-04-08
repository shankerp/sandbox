#include <iostream>

using namespace std;

/* Class template */
template <class type, class type2>
class arith
{
    public:
        type add(type a, type b); 
        type2 multiply(type2 a, type2 b);
        type2 multiply(type a, type2 b) { return (a * b); }
};

template <class type, class type2>
type arith<type, type2>::add(type a, type b)
{ 
    return a + b ;
}

template <class type, class type2>
type2 arith<type, type2>::multiply(type2 a, type2 b)
{
    return (a * b);
}

/* Function template */
template <typename type>
type maximum(type a, type b)
{
    return (a > b)?a:b;
}

template <typename type, typename type2>
type maximum2(type a, type2 b)
{
    return (a > b)?a:b;
}

int main()
{
    arith<int, double> a;
    arith<int, double> b;
    cout << a.add(2, 3) << endl;
    cout << b.add(2.1, 3.5) << endl;
    cout << a.multiply(2, 3) << endl;

    cout << b.multiply(2.1, 3.5) << endl;

    cout << b.multiply(2, 3.5) << endl;
    cout << maximum(1,2) << endl;
    cout << maximum(3,2) << endl;
    cout << maximum2(3.1,2.1) << endl;
}
