#include "libmx.h"

t_list *mx_sort_list(t_list *list, bool (*cmp)(void *a, void *b)) {
	t_list *c_list = NULL, *tmp = list, *store = list;
	void *swap_data;

	while (list) {
		c_list = store;
		while (c_list) {
			if (c_list->next && cmp(c_list->data, c_list->next->data)) {
				swap_data = c_list->data;
				c_list->data = c_list->next->data;
				c_list->next->data = swap_data;		
			}	
			c_list = c_list->next;
		}
		list = list->next;
	}
	return tmp;
}

