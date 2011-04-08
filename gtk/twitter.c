#include <gtk/gtk.h>

int main( int argc, char *argv[])
{
    GtkWidget *p_s_window = NULL;
    GdkColor s_color;

    s_color.red = 0x0000;
    s_color.green = 0x0000;
    s_color.blue = 0xFFFF;

    gtk_init(&argc, &argv);

    /* Prepare the window */
    p_s_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(p_s_window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(p_s_window), "twitter");


//    gdk_window_set_background       (G_OBJECT(p_s_window), &s_color);
    gtk_widget_modify_bg (p_s_window, GTK_STATE_NORMAL, &s_color);
    
    g_signal_connect_swapped(G_OBJECT(p_s_window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(p_s_window);

    gtk_main();

    return 0;

}
