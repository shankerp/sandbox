#include <locale.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>


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
	gint n;
	GdkRectangle *area;

	if (gtk_im_context_filter_keypress (im_context, event))
		return TRUE;
	area = g_object_get_data (G_OBJECT (widget), "user_data");
	n = (event->state & GDK_SHIFT_MASK) == 0 ? 1 : 10;
	switch (event->keyval)
	  {
		case GDK_Home:		area->x = area->y = 0; area->height = 10; break;
		case GDK_Left:		area->x -= n; break;
		case GDK_Right:		area->x += n; break;
		case GDK_Up:		area->y -= n; break;
		case GDK_Down:		area->y += n; break;
		case GDK_Page_Up:	area->height += n; break;
		case GDK_Page_Down:	area->height = MAX (area->height - n, 1); break;
		default:
			g_print ("key_press:keyval=%02X\n", event->keyval);
			return TRUE;
	  }
	gtk_im_context_set_cursor_location (im_context, area);
	g_print ("key_press:keyval=%02X,cursor=%d,%d,%d\n",
								event->keyval, area->x ,area->y, area->height);
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
signal_preedit_changed (GtkIMContext *im_context, GtkWidget *drawing)
{
	int width, height;
	gchar *str;
	gint x, y;
	PangoAttrList *attrs;
	PangoLayout *layout;
	GtkWidget *preedit,*window;
	GdkRectangle rc, *area;

	preedit = gtk_widget_get_parent (drawing);
	window = g_object_get_data (G_OBJECT (preedit), "user_data");
	area = g_object_get_data (G_OBJECT (window), "user_data");
	gtk_im_context_get_preedit_string (im_context, &str, &attrs, NULL);
	if (strlen (str) > 0)
	  {
		layout = gtk_widget_create_pango_layout (window, str);
		pango_layout_set_attributes (layout, attrs);
		pango_layout_get_pixel_size (layout, &width, &height);
		g_object_unref (layout);
		gdk_window_get_origin (window->window, &x, &y);
		gtk_window_move (GTK_WINDOW (preedit), x + area->x, y + area->y);
		gtk_window_resize (GTK_WINDOW (preedit), width, height);
		gtk_widget_show (preedit);
		gtk_widget_queue_draw_area (preedit, 0, 0, width, height);
	  }
	else
	  {
		gtk_widget_hide (preedit);
	  }
	g_free (str);
	pango_attr_list_unref (attrs);
}


gboolean signal_expose (GtkWidget *widget,
							GdkEventExpose *event, GtkIMContext *im_context)
{
	gchar *str;
	gint cursor_pos;
	GdkGC *gc;
	PangoAttrList *attrs;
	PangoLayout *layout;
	GdkColor color[2] = {	{0, 0x0000, 0x0000, 0x0000},
							{0, 0xffff, 0xffff, 0xffff}};

	gtk_im_context_get_preedit_string (im_context, &str, &attrs, &cursor_pos);
	layout = gtk_widget_create_pango_layout (g_object_get_data
				(G_OBJECT (gtk_widget_get_parent (widget)), "user_data"), str);
	pango_layout_set_attributes (layout, attrs);

	gc = gdk_gc_new (widget->window);
	gdk_color_alloc (gdk_colormap_get_system (), color);
	gdk_color_alloc (gdk_colormap_get_system (), color + 1);

	/* 背景 */
	gdk_gc_set_foreground (gc, color + 1);
	gdk_draw_rectangle (widget->window, gc, TRUE, event->area.x, event->area.y,
										event->area.width, event->area.height);

	/* 前景 */
	gdk_gc_set_foreground (gc, color);
	gdk_gc_set_background (gc, color + 1);
	gdk_draw_layout (widget->window, gc, 0, 0, layout);

	gdk_gc_unref (gc);
	g_free (str);
	pango_attr_list_unref (attrs);
	g_object_unref (layout);
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
	GdkRectangle area;
	GtkIMContext *im_context;
	GtkWidget *preedit, *drawing, *window;

	/* 初期化 */
	setlocale (LC_ALL, "");
	gtk_set_locale ();
	gtk_init (&argc, &argv);

	/* カーソル位置 */
	area.x = area.y = area.width = 0;
	area.height = 10;

	im_context = gtk_im_multicontext_new ();
	preedit = gtk_window_new (GTK_WINDOW_POPUP);
	drawing = gtk_drawing_area_new ();
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	/* preeditウインドウ */
	gtk_window_move (GTK_WINDOW (preedit), 0, 0);
	gtk_container_add (GTK_CONTAINER (preedit), drawing);
	g_object_set_data (G_OBJECT (preedit), "user_data", window);

	/* DrawingArea */
	g_signal_connect (G_OBJECT (drawing), "expose-event",
								G_CALLBACK (signal_expose), im_context);
	gtk_widget_show (drawing);

	/* InputMethod */
	gtk_im_context_set_cursor_location (im_context, &area);
	g_signal_connect (im_context, "commit", G_CALLBACK (signal_commit), NULL);
	g_signal_connect (im_context, "preedit_changed",
								G_CALLBACK (signal_preedit_changed), drawing);

	/* ウインドウ */
	g_object_set_data (G_OBJECT (window), "user_data", &area);
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
