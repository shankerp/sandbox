#include <glib.h>

static gboolean cb1 (gpointer data)
{
    g_print("Sleep for 10 secs\n");
    sleep(10);
    g_print("Out of sleep\n");
    return TRUE;
}

static gboolean cb2 (gpointer data)
{
    g_print("cb2  ");
    return TRUE;
}
int main(int argc, char **argv)
{
    g_type_init();
    g_thread_init(NULL);
    gtk_init(NULL, NULL);
    g_print("cb1 init\n");
    g_timeout_add(100, cb1, NULL);
    g_print("cb2 init\n");
    g_timeout_add(100, cb2, NULL);
    g_print("done\n");
    gtk_main();
}
