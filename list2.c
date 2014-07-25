#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct node{
	int num;
	struct list_head list;
};
static inline struct node*
init_node(struct node *nodep)
{
	int counter = 0;
again:
	if (counter < 5 && (nodep = malloc(sizeof(*nodep))) == NULL)
	{
		counter++;
		goto again;
	}
	
	return nodep;
}
static inline int 
assign_node(struct node *nodep, int num)
{
	if (nodep != NULL)
	{
		nodep->num = num;
		return 0;
	}
	else
	{
		return 1;
	}
	return 0;
}
static inline void
destroy_node(struct node *nodep)
{
	list_del(&nodep->list);	
	free(nodep);
	return;
}

int main(int argc, char *argv[])
{
	int counter = 0;
#if 0
	struct list_head head = LIST_HEAD_INIT(head);
#else
	struct list_head head;
	INIT_LIST_HEAD(&head);
#endif
	struct node *nodep = NULL;
	nodep = init_node(nodep);
	assign_node(nodep, ++counter);
	list_add(&nodep->list, &head);
	int i;
	for (i = 0; i < 10; i++)
	{
		nodep = init_node(nodep);
		assign_node(nodep, ++counter);
		list_add(&nodep->list, &head);
	}
	struct list_head *list;
	list_for_each(list, &head) {
		nodep = list_entry(list, struct node, list);
		fprintf(stdout, "nodep->num :%d\n", nodep->num);
	}
	fprintf(stdout, "======\n");
#if 1
	struct list_head *backup;
	list_for_each_safe(list, backup, &head) {
#else
	list_for_each(list, &head) {
#endif
		nodep = list_entry(list, struct node, list);
		if (nodep->num == 5)
			destroy_node(nodep);
		if (nodep->num == 6)
			list_move(&nodep->list, &head);
	}

	list_for_each(list, &head) {
		nodep = list_entry(list, struct node, list);
		fprintf(stdout, "nodep->num :%d\n", nodep->num);
	}
	fprintf(stdout, "======\n");
	

	if (!list_empty(&head))
	{
#if 1
		struct list_head *backup;
		list_for_each_safe(list, backup, &head) {
#else
		list_for_each(list, &head) {
#endif
			nodep = list_entry(list, struct node, list);
				destroy_node(nodep);
		}
	}

	return 0;
}
