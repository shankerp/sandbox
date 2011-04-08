/* To compile: gcc -o grab_test grab_test.c `pkg-config --libs --cflags gtk+-2.0` */

#include <gtk/gtk.h>

/* grab top corner of screen directly to a pixmap */
GdkPixmap *
grab_pixmap()
{
  GdkDrawable *src;
  GdkPixmap *dest;
  GdkGC *gc;

  dest = gdk_pixmap_new(NULL, 100, 100, 24);
  src = gdk_window_lookup(gdk_x11_get_default_root_xwindow());

  gc = gdk_gc_new(dest);
  gdk_draw_drawable(dest, gc, src,
    0, 0, 0, 0, 100, 100);

  g_object_unref(G_OBJECT(gc));
  return dest;
}

/* grab top corner of screen to a pixmap via an intermediate pixbuf */
GdkPixmap *
grab_pixmap2()
{
  GdkDrawable *src;
  GdkPixmap *dest;
  GdkColormap *cmap;
  GdkPixbuf *pbuf;
  GdkGC *gc;

  dest = gdk_pixmap_new(NULL, 100, 100, 24);
  src = gdk_window_lookup(gdk_x11_get_default_root_xwindow());

  cmap = gdk_window_get_colormap(src);
  pbuf = gdk_pixbuf_get_from_drawable(NULL, src, cmap, 0, 0, 0, 0, 100, 100);

  gc = gdk_gc_new(dest);
  gdk_draw_pixbuf(dest, gc, pbuf,
    0, 0, 0, 0, 100, 100, 0, 0, 0);

  g_object_unref(G_OBJECT(gc));
  g_object_unref(G_OBJECT(pbuf));
  return dest;
}

int
main(int argc, char **argv)
{
  GtkWidget *window = NULL;
  GtkWidget *image = NULL, *box = NULL;
  GdkPixmap *pixmap = NULL, *mask = NULL;
  GdkPixbuf *pixbuf = NULL;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_app_paintable(window, TRUE);

  box = gtk_hbox_new(1, 5);
  gtk_container_add(GTK_CONTAINER(window), box);

  /* left image is direct to pixmap (and doesn't work) */
  image = gtk_image_new();
  gtk_container_add(GTK_CONTAINER(box), image);
  pixmap = grab_pixmap();
  gtk_image_set_from_pixmap(GTK_IMAGE(image), pixmap, mask);
  g_object_unref(G_OBJECT(pixmap));

  /* right image uses intermediate pixbuf (and works) */
  image = gtk_image_new();
  gtk_container_add(GTK_CONTAINER(box), image);
  pixmap = grab_pixmap2();
  gtk_image_set_from_pixmap(GTK_IMAGE(image), pixmap, mask);
  g_object_unref(G_OBJECT(pixmap));

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);
  gtk_main();
}

