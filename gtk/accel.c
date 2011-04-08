#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#if 0
int main( int argc, char *argv[])
{

    GtkWidget *window;
    GtkWidget *vbox;

    GtkWidget *menubar;
    GtkWidget *filemenu;
    GtkWidget *file;
    GtkWidget *new;
    GtkWidget *open;
    GtkWidget *quit;

    GtkWidget *sep;

    GtkAccelGroup *accel_group = NULL;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
    gtk_window_set_title(GTK_WINDOW(window), "menu");

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    menubar = gtk_menu_bar_new();
    filemenu = gtk_menu_new();

    accel_group = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

    file = gtk_menu_item_new_with_mnemonic("_File");
    new = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
    open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, NULL);
    sep = gtk_separator_menu_item_new();
    quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group);

    gtk_widget_add_accelerator(quit, "activate", accel_group, 
            GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE); 


    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), new);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), sep);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);

    g_signal_connect_swapped(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(quit), "activate",
            G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
#else

int main( int argc, char *argv[])
{
    GtkWidget *p_s_window = NULL;
    GtkWidget *p_s_vbox = NULL;

    GtkWidget *p_s_menubar = NULL;
    GtkWidget *p_s_filemenu = NULL;
    GtkWidget *p_s_file = NULL;
    GtkWidget *p_s_new = NULL;
    GtkWidget *p_s_open = NULL;
    GtkWidget *p_s_quit = NULL;

    GtkWidget *p_s_sep = NULL;

    GtkAccelGroup *p_s_accel_group = NULL;

    gtk_init(&argc, &argv);

    p_s_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(p_s_window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(p_s_window), 250, 200);
    gtk_window_set_title(GTK_WINDOW(p_s_window), "menu");

    p_s_vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(p_s_window), p_s_vbox);

    p_s_menubar = gtk_menu_bar_new();
    p_s_filemenu = gtk_menu_new();

    p_s_accel_group = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(p_s_window), p_s_accel_group);

    p_s_file = gtk_menu_item_new_with_mnemonic("_File");
    p_s_new = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
    p_s_open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, NULL);
    p_s_sep = gtk_separator_menu_item_new();
    p_s_quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, p_s_accel_group);

    gtk_widget_add_accelerator(p_s_quit, "activate", p_s_accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);



    gtk_menu_shell_append(GTK_MENU_SHELL(p_s_menubar), p_s_file);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(p_s_file), p_s_filemenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(p_s_filemenu), p_s_new);
    gtk_menu_shell_append(GTK_MENU_SHELL(p_s_filemenu), p_s_open);
    gtk_menu_shell_append(GTK_MENU_SHELL(p_s_filemenu), p_s_sep);
    gtk_menu_shell_append(GTK_MENU_SHELL(p_s_filemenu), p_s_quit);

    gtk_box_pack_start(GTK_BOX(p_s_vbox), p_s_menubar, FALSE, FALSE, 3);

    g_signal_connect_swapped(G_OBJECT(p_s_window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(p_s_quit), "activate",
            G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(p_s_window);

    gtk_main();

    return 0;
}
#endif
