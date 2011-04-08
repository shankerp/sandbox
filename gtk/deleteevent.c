
#include <gtk/gtk.h>

static gboolean on_window_delete_event (GtkWidget*, GdkEvent*, gpointer);
GtkResponseType confirm_quit_dialog();

    int
main (int argc, char *argv[])
{

    GtkWidget *window;

    /* initialize the GTK+ library */
    gtk_init (&argc, &argv);

    /* create main window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Quit Dialog Example");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 200, 100);

    /* connect signals */
    g_signal_connect (G_OBJECT(window), "destroy",
            G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (G_OBJECT(window), "delete-event",
            G_CALLBACK (on_window_delete_event), NULL);       

    /* show the main window */
    gtk_widget_show (window);

    gtk_main ();

    return 0;     
}

    static gboolean
on_window_delete_event (GtkWidget *w, GdkEvent *e, gpointer user_data)
{
    if (confirm_quit_dialog() == GTK_RESPONSE_NO)
    {
        return TRUE;    /* do not quit */
    }
    else return FALSE;      /* quit */
}

    GtkResponseType
confirm_quit_dialog()
{
    GtkWidget *dialog;
    GtkResponseType response;

    /* create the dialog */
    dialog = gtk_message_dialog_new (NULL,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_QUESTION,
            GTK_BUTTONS_YES_NO,
            "Are you sure you want to quit?");

    gtk_window_set_title(GTK_WINDOW(dialog), "Really Quit?");

    /* run the dialog */
    response = gtk_dialog_run (GTK_DIALOG (dialog));
    if (response == GTK_RESPONSE_DELETE_EVENT)
    {
        response = GTK_RESPONSE_NO;
    }

    gtk_widget_destroy (dialog);   

    return response;
} 
