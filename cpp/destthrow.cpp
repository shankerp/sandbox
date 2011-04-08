#include <iostream>

class Sample
{
    public:
        ~Sample()
        {
            throw 1;
        }
};

int main()
{
    try
    {
        Sample   sample;
    }
    catch(...)
    {
        std::cout << "Print This" << std::endl;
    }

    try
    {
        Sample   sample;
        throw 2;
    }
    catch(...)
    {
        std::cout << "Second print " << std::endl;
    }
}
