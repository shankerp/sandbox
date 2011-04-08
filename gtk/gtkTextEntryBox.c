#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

// Example GTK program to create and modify a text entry box.
// BSD license.

// Compile: g++ -g -o gtkTextEntryBox gtkTextEntryBox.c `pkg-config --cflags --libs gtk+-2.0` `gnome-config --cflags --libs gnome gnomeui`

static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
   return FALSE;
}

static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

int main( int   argc, char *argv[] )
{
    GtkWidget *window_Widget;
    GtkWidget *vBox_Widget;
    GtkWidget *boxLabel_Widget;
    GtkWidget *text_entry_Widget;
    GtkWidget *textLabel_Widget;
    char       textLabel[64];

    GdkColor colorBlack;
    GdkColor colorGreen;

    // black
    colorBlack.red=0;
    colorBlack.green=0;
    colorBlack.blue=0;

    // Green
    colorGreen.red=0;
    colorGreen.green=65535;
    colorGreen.blue=0;

    gtk_init (&argc, &argv);
    window_Widget = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window_Widget), "Text Entry Box Example");

    g_signal_connect (G_OBJECT (window_Widget), "delete_event",
                      G_CALLBACK (delete_event), NULL);

    g_signal_connect (G_OBJECT (window_Widget), "destroy",
                      G_CALLBACK (destroy), NULL);

    gtk_container_set_border_width (GTK_CONTAINER (window_Widget), 10);

    vBox_Widget = gtk_vbox_new (FALSE, 0);

    char *textLabel0="Display Label";
    sprintf(textLabel, "<small>%s</small>",textLabel0);

    textLabel_Widget = gtk_label_new (textLabel);
    gtk_label_set_markup(GTK_LABEL (textLabel_Widget),textLabel);
    gtk_label_set_justify(GTK_LABEL (textLabel_Widget),GTK_JUSTIFY_LEFT);
    gtk_misc_set_alignment (GTK_MISC (textLabel_Widget), 0, 0.5);
    gtk_widget_show (textLabel_Widget);
    gtk_box_pack_start( GTK_BOX (vBox_Widget),
                        textLabel_Widget,
                        TRUE,
                        TRUE,
                        0);

    // --------------------------------------------------------------------
    // Create text entry widget and modify.
    // --------------------------------------------------------------------

    text_entry_Widget = gtk_entry_new();

    gtk_widget_modify_text(text_entry_Widget, GTK_STATE_NORMAL, &colorGreen);
    gtk_widget_modify_base(text_entry_Widget, GTK_STATE_NORMAL, &colorBlack);

    GtkStyle *style = gtk_widget_get_style(text_entry_Widget);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(text_entry_Widget, style->font_desc);

    int        text_width = 20;           // Width of field in characters
    gtk_entry_set_width_chars(GTK_ENTRY(text_entry_Widget), text_width);

    gtk_editable_set_editable(GTK_EDITABLE(text_entry_Widget), FALSE);
    GTK_WIDGET_UNSET_FLAGS(text_entry_Widget, GTK_CAN_FOCUS);

    char *txtBuffer = "Display Text";
    gtk_entry_set_text(GTK_ENTRY(text_entry_Widget), txtBuffer);

    // --------------------------------------------------------------------

    gtk_box_pack_start (GTK_BOX (vBox_Widget), text_entry_Widget, TRUE, TRUE, 0);
    gtk_widget_show (text_entry_Widget);

    gtk_container_add (GTK_CONTAINER (window_Widget), vBox_Widget);

    gtk_widget_show (vBox_Widget);
    gtk_widget_show (window_Widget);

    gtk_main ();

    return 0;
}
