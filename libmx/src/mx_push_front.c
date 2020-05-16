#include "libmx.h"

void mx_push_front(t_list **list, void *data) {
	t_list *Node = mx_create_node(data);
	if (Node != NULL) {
		Node->next = *list;
		*list = Node;
	}
}

