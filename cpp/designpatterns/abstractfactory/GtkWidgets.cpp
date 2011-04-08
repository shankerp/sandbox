#include <gtk/gtk.h>
#include "Widgets.h"

Window::Window()
{
    m_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
}

Window::~Window()
{
    gtk_widget_destroy(m_window);
}

void Window::setTitle(char *title)
{
    gtk_window_set_title(GTK_WINDOW(m_window), title);
}

void Window::setPosition(Position position)
{
    GtkWindowPosition pos;
    switch(position) {
    case None:
        pos = GTK_WIN_POS_NONE;
        break;
    case Center:
        pos = GTK_WIN_POS_CENTER;
        break;
    case Mouse:
        pos = GTK_WIN_POS_MOUSE;
        break;
    case CenterAlways:
        pos = GTK_WIN_POS_CENTER_ALWAYS;
        break;
    case CenterOnParen:
        pos = GTK_WIN_POS_CENTER_ON_PARENT;
        break;
    }
    gtk_window_set_position(GTK_WINDOW(m_window), pos);
}

void Window::setSize(int width, int height)
{
    gtk_widget_set_size_request (m_window, width, height);
}

void Window::show()
{
    gtk_widget_show_all(m_window);
}

Button::Button()
{
    m_button = gtk_button_new();
}

Button::Button(char *label)
{
    m_button = gtk_button_new_with_label(label);
}

Button::~Button()
{
    gtk_widget_destroy(m_button);
}

void Button::setLabel(char *label)
{
}

void Button::add(Window* window)
{
}
