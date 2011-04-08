#include <locale.h>
#include <gtk/gtk.h>


/******************************************************************************
*                                                                             *
*                                                                             *
*                                                                             *
******************************************************************************/
static void
signal_realize (GtkWidget *widget, GtkIMContext *im_context)
{
	gtk_im_context_set_client_window (im_context, widget->window);
}


static void
signal_unrealize (GtkWidget *widget, GtkIMContext *im_context)
{
	gtk_im_context_set_client_window (im_context, NULL);
}


static gboolean
signal_focus_in (GtkWidget *widget, GdkEventFocus *event,
													GtkIMContext *im_context)
{
	GTK_WIDGET_SET_FLAGS (widget, GTK_HAS_FOCUS);
	gtk_im_context_focus_in (im_context);
	return FALSE;
}


static gboolean
signal_focus_out (GtkWidget *widget, GdkEventFocus *event,
													GtkIMContext *im_context)
{
	GTK_WIDGET_UNSET_FLAGS (widget, GTK_HAS_FOCUS);
	gtk_im_context_focus_out (im_context);
	return FALSE;
}


/******************************************************************************
*                                                                             *
* キー入力イベント                                                            *
*                                                                             *
******************************************************************************/
static gboolean
signal_key_press (GtkWidget *widget, GdkEventKey *event,
													GtkIMContext *im_context)
{
	if (gtk_im_context_filter_keypress (im_context, event))
		return TRUE;
	g_print ("key_press:keyval=%02X\n", event->keyval);
	return TRUE;
}


static gboolean
signal_key_release (GtkWidget *widget, GdkEventKey *event,
													GtkIMContext *im_context)
{
	if (gtk_im_context_filter_keypress (im_context, event))
		return TRUE;
	g_print ("key_release:keyval=%02X\n", event->keyval);
	return TRUE;
}


/******************************************************************************
*                                                                             *
* GtkIMContext                                                                *
*                                                                             *
******************************************************************************/
static void
signal_commit (GtkIMContext *im_context, gchar *arg1, gpointer user_data)
{
	g_print ("commit:%d,%s\n", strlen (arg1), arg1);
}


static void
signal_preedit_start (GtkIMContext *im_context, gpointer user_data)
{
	g_print ("preedit_start\n");
}


static void
signal_preedit_end (GtkIMContext *im_context, gpointer user_data)
{
	g_print ("preedit_end\n");
}


static void
signal_preedit_changed (GtkIMContext *im_context, gpointer user_data)
{
	gchar *str;
	gint cursor_pos;

	gtk_im_context_get_preedit_string (im_context, &str, NULL, &cursor_pos);
	g_print ("preedit_change:%d,%d,%s\n", cursor_pos, strlen (str), str);
	g_free (str);
}


/******************************************************************************
*                                                                             *
*                                                                             *
*                                                                             *
******************************************************************************/
int
main (int argc, char *argv[])
{
	GtkIMContext *im_context;
	GtkWidget *window;

	/* 初期化 */
	setlocale (LC_ALL, "");
	gtk_set_locale ();
	gtk_init (&argc, &argv);

	/* InputMethod */
	im_context = gtk_im_multicontext_new ();
	g_signal_connect (im_context, "commit", G_CALLBACK (signal_commit), NULL);
	g_signal_connect (im_context, "preedit_start",
									G_CALLBACK (signal_preedit_start), NULL);
	g_signal_connect (im_context, "preedit_end",
									G_CALLBACK (signal_preedit_end), NULL);
	g_signal_connect (im_context, "preedit_changed",
									G_CALLBACK (signal_preedit_changed), NULL);

	/* ウインドウ */
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

	/* 表示 */
	gtk_widget_show_all (window);
	gtk_window_set_policy (GTK_WINDOW (window), TRUE, TRUE, TRUE);

	gtk_main();

	g_object_unref (im_context);

	return 0;
}
