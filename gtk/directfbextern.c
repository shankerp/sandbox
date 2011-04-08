#include <directfb/directfb.h>
#include <gtk/gtk.h>
#include <math.h>

extern IDirectFBWindow *gdk_directfb_window_lookup(GdkWindow *window );

int main(int argc, char **argv)
{
    GtkWidget *win;
    GtkWidget *image;
    cairo_t *cr;
    GdkColormap *cmap;
    GdkPixmap *pmap;
    GdkPixbuf *pbuf;
    IDirectFBWindow *window;

    gint w, h;

    /* you can set w and h to whatever you want */
    w = 200;
    h = 200;

    gtk_init(&argc, &argv);

    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(win, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    /* get a default GdkColormap */
    cmap = gdk_colormap_get_system();
    /* create a new GdkPixmap for drawing */
    pmap = gdk_pixmap_new(NULL, w, h, gdk_colormap_get_visual(cmap)->depth);
    /* create a cairo context from the pixmap */
    cr = gdk_cairo_create(GDK_DRAWABLE(pmap));

    /* fill the background red */
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_rectangle(cr, 0, 0, w, h);
    cairo_fill(cr);

    /* create a white circle in the center */
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_arc(cr, w/2, h/2, MIN(w/4, h/4), 0, 2*M_PI);
    cairo_fill(cr);

    /* free the cairo context */
    cairo_destroy(cr);

    /* create a new GdkPixbuf from the pixmap */
    pbuf = gdk_pixbuf_get_from_drawable(NULL, pmap, cmap, 0, 0, 0, 0, w, h);
    /* create a new GtkImage from the pixbuf */
    image = gtk_image_new_from_pixbuf(pbuf);
    gtk_container_add(GTK_CONTAINER(win), image);
    gtk_widget_show(image);

    gtk_widget_show(win);

    window = gdk_directfb_window_lookup(pmap);
    gtk_main();

    return 0;
}
