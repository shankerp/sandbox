#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <JavaScriptCore/JavaScript.h>

static void myclass_init_cb(JSContextRef ctx, JSObjectRef object)
{
printf("Class Initialization\n");
printf("Class Initialization\n");
printf("Class Initialization\n");
printf("Class Initialization\n");
printf("Class Initialization\n");
// ...
}

static void myclass_finalize_cb(JSObjectRef object)
{
printf("Class Finalialization\n");
printf("Class Finalialization\n");
printf("Class Finalialization\n");
printf("Class Finalialization\n");
printf("Class Finalialization\n");
// ...
}

static JSValueRef myclass_mymethod(JSContextRef context,
                       JSObjectRef function,
                       JSObjectRef thisObject,
                       size_t argumentCount,
                       const JSValueRef arguments[],
                       JSValueRef *exception)
{
JSStringRef string = JSStringCreateWithUTF8CString("mystring");
return JSValueMakeNull(context);
return JSValueMakeString(context, string);
}

static const JSStaticFunction class_staticfuncs[] =
{
{ "mymethod", myclass_mymethod, kJSPropertyAttributeReadOnly },
{ NULL, NULL, 0 }
};

static const JSClassDefinition class_def =
{
0,
kJSClassAttributeNone,
"TestClass",
NULL,

NULL,
class_staticfuncs,

myclass_init_cb,
myclass_finalize_cb,

NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL
};

static void addJSClasses(JSGlobalContextRef context)
{
JSClassRef classDef = JSClassCreate(&class_def);
JSObjectRef classObj = JSObjectMake(context, classDef, context);
JSObjectRef globalObj = JSContextGetGlobalObject(context);
JSStringRef str = JSStringCreateWithUTF8CString("myclass");
JSObjectSetProperty(context, globalObj, str, classObj,
                   kJSPropertyAttributeNone, NULL);
}

static void window_object_cleared_cb(WebKitWebView  *web_view,
                                WebKitWebFrame *frame,
                                gpointer        context,
                                gpointer        arg3,
                                gpointer        user_data)

{
JSGlobalContextRef jsContext = webkit_web_frame_get_global_context(frame);
addJSClasses(jsContext);
}

static GtkWidget* main_window;
static WebKitWebView* web_view;

static void destroy_cb(GtkWidget* widget, gpointer data)
{
gtk_main_quit ();
}

static GtkWidget* create_browser()
{
GtkWidget* scrolled_window = gtk_scrolled_window_new (NULL, NULL);
gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

web_view = WEBKIT_WEB_VIEW (webkit_web_view_new ());
gtk_container_add (GTK_CONTAINER (scrolled_window), GTK_WIDGET (web_view));

g_signal_connect (G_OBJECT (web_view), "window-object-cleared", G_CALLBACK(window_object_cleared_cb), web_view);

return scrolled_window;
}

static GtkWidget* create_window()
{
GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);
g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (destroy_cb), NULL);
return window;
}

int main (int argc, char* argv[])
{
gtk_init (&argc, &argv);
if (!g_thread_supported())
   g_thread_init (NULL);

GtkWidget* vbox = gtk_vbox_new(FALSE, 0);
gtk_box_pack_start(GTK_BOX(vbox), create_browser (), TRUE, TRUE, 0);

main_window = create_window();
gtk_container_add(GTK_CONTAINER (main_window), vbox);

gchar* uri = (gchar*) "file:///home/bharath/workspace/sandbox/webkit/simple.html";
webkit_web_view_open(web_view, uri);                      

gtk_widget_grab_focus (GTK_WIDGET (web_view));
gtk_widget_show_all (main_window);
gtk_main ();

return 0;
}
