#include <webkit/webkit.h>

#define PAGE "<html><body><p><a href=\"google.com\">Google</a></p><p><a href=\"webkit.org\">WebKit</a></p></body></html>"

static gboolean
bounce_back(WebKitDOMCSSStyleDeclaration *style)
{
    webkit_dom_css_style_declaration_set_property(style, "-webkit-transition", "top 1s ease-in", "", NULL);
    webkit_dom_css_style_declaration_set_property(style, "top", "0px", "", NULL);

    return FALSE;
}

static void
mark_links(GtkButton *button, WebKitWebView *view)
{
    WebKitDOMDocument* document = webkit_web_view_get_dom_document(view);
    WebKitDOMHTMLCollection *collection = webkit_dom_document_get_links(document);
    gulong length = webkit_dom_html_collection_get_length(collection);
    guint i;

    for (i = 0; i < length; i++) {
        WebKitDOMNode *node = webkit_dom_html_collection_item(collection, i);
        WebKitDOMElement* element = (WebKitDOMElement*)node;
        WebKitDOMCSSStyleDeclaration *style = webkit_dom_element_get_style(element);
        webkit_dom_css_style_declaration_set_property(style, "-webkit-transition", "top 1s ease-in", "", NULL);
        webkit_dom_css_style_declaration_set_property(style, "top", "25px", "", NULL);
        webkit_dom_css_style_declaration_set_property(style, "position", "relative", "", NULL);
        g_timeout_add(1000, (GSourceFunc)bounce_back, style);
    }
}

int main(int argc, char** argv)
{
    GtkWidget *window, *box, *button, *scrolled, *view;

    gtk_init(&argc, &argv);

    g_thread_init (NULL);
    gtk_init (&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    box = gtk_vbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    view = webkit_web_view_new();
    gtk_container_add(GTK_CONTAINER(scrolled), view);
    gtk_box_pack_start(GTK_BOX(box), scrolled, TRUE, TRUE, 0);

    button = gtk_button_new_with_label("Dance links!");
    g_signal_connect(button, "clicked", G_CALLBACK(mark_links), view);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);

    if (argc == 1)
        webkit_web_view_load_string(WEBKIT_WEB_VIEW(view), PAGE, NULL, NULL, NULL);
    else
        webkit_web_view_load_uri(WEBKIT_WEB_VIEW(view), argv[1]);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
