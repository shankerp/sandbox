#include <iostream>
#if GTK_WIDGET
#include <gtk/gtk.h>
#endif

class Window {
public:
    enum {
        None,
        Center,
        Mouse,
        CenterAlways,
        CenterOnParent
    } Position;
    Window();
    ~Window();
    void setTitle(char *title);
    void setPosition(Position position);
    void setSize(int width, int height);
    void show();

private:
#if GTK_WIDGET
    GtkWindow* m_window;
#endif
#if QT_WIDGET
#endif
};

class Button {
public:
    Button();
    Button(char *label);
    ~Button();
    void setLabel(char *label);
    void add(Window* window);
private:
#if GTK_WIDGET
    GtkButton* m_button;
#endif
#if QT_WIDGET
#endif
};
