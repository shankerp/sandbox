#include <glib.h>

enum Capital {
    Richmond,
    Richmond2,
    Austin,
    Austin2,
    Columbus
};

void value_destroyed(gpointer data) {
    printf("Got a value destroy call for %d\n", GPOINTER_TO_INT(data));
}

int main(int argc, char** argv) {
    GHashTable* hash = g_hash_table_new_full(g_str_hash, g_str_equal,
            NULL,
            (GDestroyNotify)value_destroyed);
    GHashTable *hash1 = hash;
    hash = g_hash_table_new_full(g_str_hash, g_str_equal,
            NULL,
            (GDestroyNotify)value_destroyed);
    g_hash_table_insert(hash1, g_strdup("Virginia"), g_strdup("Richmond"));
    g_hash_table_insert(hash1, g_strdup("Texas"), g_strdup("Austin"));
    g_hash_table_insert(hash1, g_strdup("Ohio"), g_strdup("Columbus"));
    printf("The capital of Texas is ");
    gchar *ptr = g_strdup("Texas");
    int i = 0;
    while(1) {
        //switch(GPOINTER_TO_INT(g_hash_table_lookup(hash1, ptr))) {
        //    case Richmond:
        //        printf("Richmond\n");
        //        break;
        //    case Austin:
        //        printf("Austin\n");
        //        break;
        //    case Columbus:
        //        printf("Columbus\n");
        //        break;
        //    default:
        //        printf("default\n");
        //        break;
        //}
        g_print("%s\n", (g_hash_table_lookup(hash1, ptr)));
        if(i == 100)
            break;
        i++;
    }
    g_hash_table_destroy(hash1);
    g_hash_table_destroy(hash);
    return 0;
}
