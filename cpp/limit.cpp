#include <iostream>
#include <limits>

int main()
{
    std::cout << "Largest float == " << numeric_limits<float>::max()
        << ", char is signed == " << numeric_limits<char>::is_signed << std::endl;
}
