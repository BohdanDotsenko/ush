#include "libmx.h"

#include "libmx.h"
void mx_pop_front(t_list **list) {
	if (list && *list) {
		t_list *node = *list;
		*list = node->next;
		node->data = NULL;
		node->next = NULL;
		free(node);
	}
}
