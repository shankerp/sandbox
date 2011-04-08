/* Test me with:
*   gcc -o combo combo.c $(pkg-config --cflags --libs gtk+-2.0) && ./combo
*/

#include <gtk/gtk.h>

/* This function gets called when currently selected item changes */
static void
cb_changed( GtkComboBox *combo,
            gpointer     data )
{
    /* Obtain currently selected string from combo box */
    gchar *string = gtk_combo_box_get_active_text( combo );

    /* Print it to the console - if nothing is selected, print NULL */
    g_print( "Selected (simple): >> %s <<\n", ( string ? string : "NULL" ) );

    /* Free string */
    g_free( string );
}

/* This function deletes currently selected item from combo box */
static void
cb_delete( GtkButton   *button,
           GtkComboBox *combo )
{
    gint index;

    /* Get currently selected item's index */
    index = gtk_combo_box_get_active( combo );

    /* Remove this item from combo */
    gtk_combo_box_remove_text( combo, index );
}

int
main( int    argc,
      char **argv )
{
    /*Common variables */
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *frame;
    GtkWidget *combo;
    GtkWidget *button;

    /* Initialization */
    gtk_init( &argc, &argv );

    /* Create main window */
    window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
    g_signal_connect( G_OBJECT( window ), "destroy",
                      G_CALLBACK( gtk_main_quit ), NULL );
    gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );

    /* Create vbox */
    vbox = gtk_vbox_new( FALSE, 6 );
    gtk_container_add( GTK_CONTAINER( window ), vbox );

    /* Create frame */
    frame = gtk_frame_new( "Text API" );
    gtk_box_pack_start( GTK_BOX( vbox ), frame, FALSE, FALSE, 0 );

    /* Create combo box using text API and add some data to it */
    combo = gtk_combo_box_new_text();
    gtk_container_add( GTK_CONTAINER( frame ), combo );
    gtk_combo_box_append_text( GTK_COMBO_BOX( combo ), "Hello World once" );
    gtk_combo_box_prepend_text( GTK_COMBO_BOX( combo ), "Hello World twice" );
    gtk_combo_box_insert_text( GTK_COMBO_BOX( combo ), 1, "Hello World last time" );

    /* Connect signal to tour handler function */
    g_signal_connect( G_OBJECT( combo ), "changed",
                      G_CALLBACK( cb_changed ), NULL );


    /* Add button that, when clicked, deletes currently selected entry */
    button = gtk_button_new_with_mnemonic( "_Delete selected item" );
    gtk_box_pack_start( GTK_BOX( vbox ), button, FALSE, FALSE, 0 );
    g_signal_connect( G_OBJECT( button ), "clicked",
                      G_CALLBACK( cb_delete ), GTK_COMBO_BOX( combo ) );

    /* Show our application and start main loop */
    gtk_widget_show_all( window );
    gtk_main();

    return( 0 );
}
