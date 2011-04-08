#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

static GtkWidget *web_view;
struct my_msgbuf
{
    long mtype;
    char mtext[200];
};
static void customloaderthread(void)
{
    struct my_msgbuf buf;
    int msqid;
    key_t key;
    GdkEvent    s_event;
    if ((key = ftok("/media/work/Dropbox/workspace/sandbox/isense", 'B')) == -1)
    {
        /* same key as kirk.c */
        perror("ftok");
        exit(1);
    }
    if ((msqid = msgget(key, 0644)) == -1)
    {
        /* connect to the queue */
        perror("msgget");
        exit(1);
    }
    printf("spock: ready to receive messages, captain.\n");

    while(1) {
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 2, IPC_NOWAIT) == -1)
        {
            if (errno == ENOMSG)
            {
                usleep(10*1000);
                continue;
            }
            printf("%d\n", errno);
            perror("msgrcv");
            /* exit(1);*/
        }
        printf("Out of msgrcv\n");
        printf("spock: \"%s\"\n", buf.mtext);
        webkit_web_view_load_uri (WEBKIT_WEB_VIEW (web_view), buf.mtext);
    }
}

int main (int argc, char *argv[])
{
    pthread_t thread;
    gtk_init(&argc, &argv);
    if (!g_thread_supported ())
        g_thread_init (NULL);  
    /* Create the widgets */
    GtkWidget *main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    web_view = webkit_web_view_new ();

    /* Place the WebKitWebView in the GtkScrolledWindow */
    gtk_container_add (GTK_CONTAINER (scrolled_window), web_view);
    gtk_container_add (GTK_CONTAINER (main_window), scrolled_window);

    /* Open a webpage */
    webkit_web_view_load_uri (WEBKIT_WEB_VIEW (web_view), "http://www.gnome.org");

    pthread_create(&thread, NULL, (void *(*)(void *))(customloaderthread), NULL );
    /* Show the result */
    gtk_window_set_default_size (GTK_WINDOW (main_window), 800, 600);
    gtk_widget_show_all (main_window);

    gtk_main();
}
