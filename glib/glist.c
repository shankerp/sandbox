#include <glib.h>

int main()
{
/* Notice that these are initialized to the empty list. */
GSList *list = NULL, *number_list = NULL;

g_print("Number of elements %d\n", g_slist_length(list));
/* This is a list of strings. */
//list = g_slist_append (list, "first");
list = g_slist_insert(list, g_strdup("first"), g_slist_length(list));
list = g_slist_insert(list, g_strdup("first"), g_slist_length(list));
g_print("Number of elements %d\n", g_slist_length(list));
/* This is a list of strings. */
list = g_slist_append (list, g_strdup("second"));
g_print("Number of elements %d\n", g_slist_length(list));
/* This is a list of strings. */

g_print("%s ", g_slist_nth_data(list, 0));
g_print("%s \n", g_slist_nth_data(list, 1));
g_print("%s \n", g_slist_nth_data(list, 2));
g_print("%s \n", g_slist_nth_data(list, 2));
g_print("%s \n", g_slist_nth_data(list, g_slist_length(list) - 1));
int s32_length = g_slist_length(list);
while (s32_length) {
    g_free(g_slist_nth_data(list, s32_length - 1));
    g_print("The length now is %d\n", g_slist_length(list));
    list = g_slist_remove(list, g_slist_nth_data(list, s32_length - 1));
    g_print("The length now is %d\n", g_slist_length(list));
    s32_length--;
}

g_slist_free(list);
g_slist_free(list);
g_slist_free(list);
g_print("Multiple frees works!!\n");
g_slist_free(list);
g_slist_free(list);
/* This is a list of integers. */
number_list = g_slist_append (number_list, GINT_TO_POINTER (27));
number_list = g_slist_append (number_list, GINT_TO_POINTER (14));


}
