#include <glib.h>

int main()
{
    gchar *p_ch_uri = g_strdup_printf("%i%i%i",1,2,3);
    g_print("%s\n", p_ch_uri);
}
