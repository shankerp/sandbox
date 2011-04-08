#include <locale.h>
#include <gtk/gtk.h>
#include <string.h>


/************************************************* *****************************
*
*
*
************************************************** ****************************/
static void
signal_realize (GtkWidget * widget, GtkIMContext * im_context)
{
    gtk_im_context_set_client_window (im_context, widget-> window);
}


static void
signal_unrealize (GtkWidget * widget, GtkIMContext * im_context)
{
    gtk_im_context_set_client_window (im_context, NULL);
}


static gboolean
signal_focus_in (GtkWidget * widget, GdkEventFocus * event,
                                                    GtkIMContext * im_context)
{
    GTK_WIDGET_SET_FLAGS (widget, GTK_HAS_FOCUS);
    gtk_im_context_focus_in (im_context);
    return FALSE;
}


static gboolean
signal_focus_out (GtkWidget * widget, GdkEventFocus * event,
                                                    GtkIMContext * im_context)
{
    GTK_WIDGET_UNSET_FLAGS (widget, GTK_HAS_FOCUS);
    gtk_im_context_focus_out (im_context);
    return FALSE;
}


/************************************************* *****************************
*
* * Key events
*
************************************************** ****************************/
static gboolean
signal_key_press (GtkWidget * widget, GdkEventKey * event,
                                                    GtkIMContext * im_context)
{
    g_print ("key_press: keyval =% 02X \n", event-> keyval);
    if (gtk_im_context_filter_keypress (im_context, event))
        return TRUE;
    return TRUE;
}


static gboolean
signal_key_release (GtkWidget * widget, GdkEventKey * event,
                                                    GtkIMContext * im_context)
{
    if (gtk_im_context_filter_keypress (im_context, event))
        return TRUE;
    g_print ("key_release: keyval =% 02X \n", event-> keyval);
    return TRUE;
}


/************************************************* *****************************
*
* GtkIMContext *
*
************************************************** ****************************/
static void
signal_commit (GtkIMContext * im_context, gchar * arg1, gpointer user_data)
{
    g_print ("commit:% d,% s \n", strlen (arg1), arg1);
}


/************************************************* *****************************
*
*
*
************************************************** ****************************/
int
main (int argc, char * argv [])
{
    GtkIMContext * im_context;
    GtkWidget * window;

    /* Initialize */
    setlocale (LC_ALL, "");
    gtk_set_locale ();
    gtk_init (& argc, & argv);

    /* InputMethod */
    im_context = gtk_im_multicontext_new ();
    g_signal_connect (im_context, "commit", G_CALLBACK (signal_commit), NULL);

    /* Window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (G_OBJECT (window), "destroy",
                                G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (G_OBJECT (window), "key-press-event",
                                G_CALLBACK (signal_key_press), im_context);
    g_signal_connect (G_OBJECT (window), "key-release-event",
                                G_CALLBACK (signal_key_release), im_context);
    g_signal_connect (G_OBJECT (window), "realize",
                                G_CALLBACK (signal_realize), im_context);
    g_signal_connect (G_OBJECT (window), "unrealize",
                                G_CALLBACK (signal_unrealize), im_context);
    g_signal_connect (G_OBJECT (window), "focus-in-event",
                                G_CALLBACK (signal_focus_in), im_context);
    g_signal_connect (G_OBJECT (window), "focus-out-event",
                                G_CALLBACK (signal_focus_out), im_context);

    /* Display */
    gtk_widget_show_all (window);
    gtk_window_set_policy (GTK_WINDOW (window), TRUE, TRUE, TRUE);

    gtk_main ();

    g_object_unref (im_context);

    return 0;
}
