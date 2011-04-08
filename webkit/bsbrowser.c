#include <gtk/gtk.h>
#include <webkit/webkit.h>

#define BS_TYPE_BROWSER                 (bs_browser_get_type())
#define BS_BROWSER(obj)                 (G_TYPE_CHECK_INSTANCE_CAST((obj), BS_TYPE_BROWSER, BsBrowser))
#define BS_IS_BROWSER(obj)              (G_TYPE_CHECK_INSTANCE_TYPE((obj), BS_TYPE_BROWSER))
#define BS_BROWSER_CLASS(glass)         (G_TYPE_CHECK_CLASS_CAST((glass), BS_TYPE_BROWSER, BsBrowserClass))
#define BS_IS_BROWSER_CLASS(glass)      (G_TYPE_CHECK_CLASS_TYPE((glass), BS_TYPE_BROWSER))
#define BS_BROWSER_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS((obj), BS_TYPE_BROWSER, BsBrowserClass))

struct _BsBrowser 
{
    GtkWindow parent_instance;
}

G_DEFINE_TYPE (BsBrowser, bs_browser, GTK_TYPE_WINDOW)


