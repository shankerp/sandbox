#include <iostream>
#include <Widgets.h>

class WidgetFactory
{
    Window* createWindow();
    Button* createButton();
    void run();
};
