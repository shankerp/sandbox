#include <gtk/gtk.h>

#if 0
int main( int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *fixed;

  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *button3;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "GtkFixed");
  gtk_window_set_default_size(GTK_WINDOW(window), 290, 200);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), fixed);

  button1 = gtk_button_new_with_label("Button");
  gtk_fixed_put(GTK_FIXED(fixed), button1, 150, 50);
  gtk_widget_set_size_request(button1, 80, 35);

  button2 = gtk_button_new_with_label("Button");
  gtk_fixed_put(GTK_FIXED(fixed), button2, 15, 15);
  gtk_widget_set_size_request(button2, 80, 35);

  button3 = gtk_button_new_with_label("Button");
  gtk_fixed_put(GTK_FIXED(fixed), button3, 100, 100);
  gtk_widget_set_size_request(button3, 80, 35);

  g_signal_connect_swapped(G_OBJECT(window), "destroy", 
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
#endif

int main(int argc, char *argv[])
{
    GtkWidget *p_s_window = NULL;
    GtkWidget *p_s_fixed = NULL;

    GtkWidget *p_s_button1 = NULL;
    GtkWidget *p_s_button2 = NULL;
    GtkWidget *p_s_button3 = NULL;

    gtk_init(&argc, &argv);

    p_s_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_s_window), "GtkFixed");
    gtk_window_set_default_size(GTK_WINDOW(p_s_window), 290, 200);
    gtk_window_set_position(GTK_WINDOW(p_s_window), GTK_WIN_POS_CENTER);

    p_s_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(p_s_window), p_s_fixed);

    p_s_button1 = gtk_button_new_with_label("Button");
    p_s_button2 = gtk_button_new_with_label("Button");
    p_s_button3 = gtk_button_new_with_label("Button");

    gtk_fixed_put(GTK_FIXED(p_s_fixed), p_s_button1, 150, 50);
    gtk_fixed_put(GTK_FIXED(p_s_fixed), p_s_button2, 15, 15);
    gtk_fixed_put(GTK_FIXED(p_s_fixed), p_s_button3, 100, 100);

    gtk_widget_set_size_request(p_s_button1, 190, 35);
    gtk_widget_set_size_request(p_s_button2, 190, 35);
    gtk_widget_set_size_request(p_s_button3, 190, 35);

    g_signal_connect(G_OBJECT(p_s_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(p_s_window);

    gtk_main();

    return 0;
}
