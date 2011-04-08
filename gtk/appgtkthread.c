
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <pthread.h>

char bigbuf[1024];

static gboolean VGAWrefreshTick(GtkWidget *widget)
{
    if (bx_user_quit != FALSE)        // may be in the middle of a "destroy"
        return FALSE;
    GdkDisplay *display = gdk_display_get_default ();
    UpdateStatus();
    if (PO_Tdelay > 0)        // output window is delaying display of a partial line?
    {
        if (--PO_Tdelay == 0)    // on a timeout, add a lf to complete the line
            ParseIDText ("\n");
    }
    XFlush (GDK_DISPLAY_XDISPLAY (display));
    return TRUE;
}

// Need to keep the bochs thread and the gtk_main threads separate -- bochs thread must not
// call GTK functions -- so it needs to set flags to initiate OnBreak, and OutputText updates
static gboolean BochsUpdateTick(GtkWidget *widget)
{
    if (bx_user_quit != FALSE)        // may be in the middle of a "destroy"
        return FALSE;
    if (UpdateOWflag != FALSE)
    {
// replace the entire Output window's text, then scroll the window to the end
        GtkTextBuffer *OBuffer;        // pull model out of the widget
        UpdateOWflag = FALSE;
        OBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(OText));
        gtk_text_buffer_set_text(OBuffer, OutWindow, -1);
        gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(OText), EndMark, (gdouble) 0, TRUE, (gdouble) 1, (gdouble) 1);
    }
    if (HitBrkflag != FALSE)
        OnBreak();
    HitBrkflag = FALSE;
    return TRUE;
}

// multithreading using pure posix threads -- not glib threads
void * EventLp(void *data)
{
    gtk_main();
//    pthread_exit(0);
    return NULL;
}

void MakeGTKthread()
{
    pthread_t hThread;
//    g_thread_init(NULL);    // if I put this in, it gives me an "undefined reference" of all crazy things!
    pthread_create (&hThread, NULL, EventLp, NULL);
}

// The app will call this function at startup
int GUIinit()
{
    int i, argc;
    char *argv[2], **argvp;
    *bigbuf = 0;            // gtk flames out if you pass in a NULL -- sheesh
    argv[0] = bigbuf;    // so I really do have to fake up an "argv" list
    argv[1] = NULL;
    argvp = argv;
    argc = 1;

    // you MUST call gtk_init, even with faked arguments, because it inits GDK and Glib
    if (gtk_init_check(&argc, &argvp) == FALSE)
        printf ("gtk init failed, can not access display?\n");
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Bochs Enhanced Debugger");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    MainVbox = gtk_vbox_new(FALSE, 0);        // vbox that contains EVERYTHING

    gtk_container_add(GTK_CONTAINER(window), MainVbox);

#if 0
    // make/init the menu "containers" (shells) and menu items
    InitMenus();
   
    ... more GTK initialization -- creating widgets and packing them


    AttachSignals();        // this must be called AFTER InitMenus()
#endif
    gtk_widget_show_all(window);

    // create timers
    g_timeout_add(500, (GSourceFunc) VGAWrefreshTick, (gpointer) window);
    g_timeout_add(50, (GSourceFunc) BochsUpdateTick, (gpointer) window);

    MakeGTKthread();
    return 1;
}

int main()
{
    GUIinit();
}
