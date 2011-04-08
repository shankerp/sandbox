#include <locale.h>
#include <gtk/gtk.h>


/******************************************************************************
*                                                                             *
* メニュー                                                                    *
*                                                                             *
******************************************************************************/
void
menu_activate (GtkMenuItem *menuitem, gpointer user_data)
{
	g_print ("menu exit\n");
}


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
	guint key;
	GdkModifierType mods;
	GtkAccelGroup *accel_group;
	GtkWidget *window, *drawing_area, *vbox;
	GtkWidget *menu_bar, *menu_shell, *menu_item;

	/* 初期化 */
	setlocale (LC_ALL, "");
	gtk_set_locale ();
	gtk_init (&argc, &argv);

	/* ウインドウ */
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT (window), "destroy",
											G_CALLBACK (gtk_main_quit), NULL);

	/* DrawingArea */
	drawing_area = gtk_drawing_area_new ();
	g_signal_connect (G_OBJECT (drawing_area), "key-press-event",
										G_CALLBACK (signal_key_press), NULL);
	gtk_widget_add_events (drawing_area,
									GDK_KEY_PRESS_MASK | GDK_KEY_RELEASE_MASK);
	GTK_WIDGET_SET_FLAGS (drawing_area, GTK_CAN_FOCUS);

	/* メニュー */
	accel_group = gtk_accel_group_new ();
	menu_item = gtk_menu_item_new_with_mnemonic ("E_xit");
	gtk_accelerator_parse ("<Control>q", &key, &mods);
	gtk_widget_add_accelerator (menu_item, "activate", accel_group, key, mods,
										GTK_ACCEL_VISIBLE | GTK_ACCEL_LOCKED);
	g_signal_connect (G_OBJECT (menu_item), "activate",
										G_CALLBACK (menu_activate), NULL);
	menu_shell = gtk_menu_new ();
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_shell), menu_item);
	menu_item = gtk_menu_item_new_with_mnemonic ("_File");
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menu_item), menu_shell);
	menu_bar = gtk_menu_bar_new ();
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), menu_item);
	gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);

	/* ボックス */
	vbox = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), menu_bar, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), drawing_area, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	/* 表示 */
	gtk_widget_show_all (window);
	gtk_window_set_policy (GTK_WINDOW (window), TRUE, TRUE, TRUE);

	gtk_main();

	return 0;
}
