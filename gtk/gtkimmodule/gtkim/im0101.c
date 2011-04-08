#include <locale.h>
#include <gtk/gtk.h>


/******************************************************************************
*                                                                             *
* キー入力イベント                                                            *
*                                                                             *
******************************************************************************/
static gboolean
signal_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
	gint i;

	g_print ("key_press:keyval=%02X", event->keyval);
	if (event->state & GDK_SHIFT_MASK)
		g_print (" Shift");
	if (event->state & GDK_CONTROL_MASK)
		g_print (" Ctrl");
	if (event->state & GDK_MOD1_MASK)
		g_print (" Alt");
	g_print (" length=%d", event->length);
	if (event->length > 0)
	  {
		for (i = 0; event->string[i] != '\0'; i++)
			g_print (" %02X", event->string[i]);
		g_print (" string=%s", event->string);
	  }
	g_print ("\n");

	return TRUE;
}


/******************************************************************************
*                                                                             *
*                                                                             *
*                                                                             *
******************************************************************************/
int
main (int argc, char *argv[])
{
	GtkWidget *window;

	/* 初期化 */
	setlocale (LC_ALL, "");
	gtk_set_locale ();
	gtk_init (&argc, &argv);

	/* ウインドウ */
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT (window), "destroy",
											G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect (G_OBJECT (window), "key-press-event",
										G_CALLBACK (signal_key_press), NULL);

	/* 表示 */
	gtk_widget_show_all (window);
	gtk_window_set_policy (GTK_WINDOW (window), TRUE, TRUE, TRUE);

	gtk_main();

	return 0;
}
