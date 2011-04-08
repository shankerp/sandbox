#include <gtk/gtk.h>

int main( int   argc,
          char *argv[] )
{
    GtkWidget *window;

    /* Sets up default visual and color map.
     * Calls gdk_init
     * Initializes gtk library for use.
     * Sets up default signal handlers.
     * Checks argument passed on command line for the following
     * --gtk-module
     * --g-fatal-warnings
     * --gtk-debug
     * --gtk-no-debug
     * --gdk-debug
     * --gdk-no-debug
     * --display
     * --sync
     * --name
     * --class
     *
     *  Other arguments are left for the application to parse
     */
    gtk_init (NULL, NULL);

    /*
     * GTK_WINDOW_TOPLEVEL - specifies that we want to
     * undergo window manager decoration and placement.
     */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_show  (window);

    gtk_main ();

    return 0;
}
