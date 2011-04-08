#include <iostream>

class Frame
{
    public:
        static Frame* create()
        {
            Frame *ptr =  new Frame();
            std::cout << "Printing from create " << ptr << std::endl;
            return ptr;
        }

        void setName(char *ptr) { this->frameName = ptr; }
        const char* name() { return this->frameName; }
    private:
        Frame()
        {
            std::cout << "Printing this " << this << std::endl;
        }
        char *frameName;
};

int main()
{
    Frame* ptr = Frame::create();
    ptr->setName("Frame");
    std::cout << ptr->name() << std::endl;
}
