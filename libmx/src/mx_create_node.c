#include "libmx.h"

t_list *mx_create_node(void *data) {

	t_list *Node = (t_list*) malloc(sizeof(t_list));
	Node->data = data;
	Node->next = NULL;
	return Node;	
}
