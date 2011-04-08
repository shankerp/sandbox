#include <gtk/gtk.h>

gboolean dialog_fn(void)
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, 0, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO, "%s", "This is a dialog!");
    gtk_widget_hide(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    g_print("Response %d\n", response);
    return FALSE;
}

int main( int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    g_timeout_add(1, (GSourceFunc)(dialog_fn), NULL);
    gtk_main();
    return 1;
}

