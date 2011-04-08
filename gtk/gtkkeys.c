#include <gtk/gtk.h>

static gboolean
signal_key_press (GtkWidget * widget, GdkEventKey * event, gpointer data)
{
    g_print("key pressed %s\n", gdk_keyval_name(event->keyval));
    //g_print ("key_press: keyval =%02X \n", event-> keyval);
    return TRUE;
}


static gboolean
signal_key_release (GtkWidget * widget, GdkEventKey * event, gpointer data)
{
    g_print("key released %s\n", gdk_keyval_name(event->keyval));
    //g_print ("key_release: keyval =%02X \n", event-> keyval);
    return TRUE;
}


int
main (int argc, char * argv [])
{
    GtkWidget * window;

    gtk_init (& argc, & argv);

    /* Window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_resize(GTK_WINDOW(window), 1920, 1080);
    g_signal_connect (G_OBJECT (window), "key-press-event",
                                G_CALLBACK (signal_key_press), NULL);
    g_signal_connect (G_OBJECT (window), "key-release-event",
                                G_CALLBACK (signal_key_release), NULL);
    g_signal_connect (G_OBJECT (window), "destroy",
                                G_CALLBACK (gtk_main_quit), NULL);
    gtk_widget_show_all (window);
    gtk_main ();
    return 0;
}
