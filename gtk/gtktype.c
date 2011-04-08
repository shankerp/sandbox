G_DEFINE_TYPE(WebKitWebView, webkit_web_view, GTK_TYPE_CONTAINER)
#define G_DEFINE_TYPE(TN, t_n, T_P)             G_DEFINE_TYPE_EXTENDED (TN, t_n, T_P, 0, {})
#define G_DEFINE_TYPE_EXTENDED(TN, t_n, T_P, _f_, _C_)      _G_DEFINE_TYPE_EXTENDED_BEGIN (TN, t_n, T_P, _f_) {_C_;} _G_DEFINE_TYPE_EXTENDED_END()

G_DEFINE_TYPE_EXTENDED (WebKitWebView,
                        webkit_web_view,
                        GTK_TYPE_CONTAINER,
                        0,
                        {});

static void     webkit_web_view_init       (WebKitWebView      *self);
static void     webkit_web_view_class_init (WebKitWebViewClass *klass);
static gpointer webkit_web_view_parent_class = NULL;
static void     webkit_web_view_class_intern_init (gpointer klass)
{
  webkit_web_view_parent_class = g_type_class_peek_parent (klass);
  webkit_web_view_class_init ((WebKitWebViewClass*) klass);
}

GType
webkit_web_view_get_type (void)
{
  static volatile gsize g_define_type_id__volatile = 0;
  if (g_once_init_enter (&g_define_type_id__volatile))
    {
      GType g_define_type_id =
        g_type_register_static_simple (GTK_TYPE_CONTAINER,
                                       g_intern_static_string ("WebKitWebView"),
                                       sizeof (WebKitWebViewClass),
                                       (GClassInitFunc) webkit_web_view_class_intern_init,
                                       sizeof (WebKitWebView),
                                       (GInstanceInitFunc) webkit_web_view_init,
                                       (GTypeFlags) 0);
      {
          {
          }
      }
      g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
    }
  return g_define_type_id__volatile;
}
