#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct node{
    int                 num;
    struct list_head    list;
};

static inline struct node
*init_node(struct node *nodep)
{
    nodep = malloc(sizeof(*nodep));
    if (nodep != NULL)
        INIT_LIST_HEAD(&nodep->list);

    return nodep;
}
static inline void
destroy_node(struct node *nodep)
{
    free(nodep);
    nodep = NULL;
    return;
}
static inline int
assign_node(struct node *nodep, int num)
{
    if (nodep != NULL) {
        nodep->num = num;
        return 0;
    }
    else {
        return 1;
    }
}

int
main(int argc, char *argv[])
{
#include <mcheck.h>
    mtrace();
    int counter = 0;
    struct list_head node;
    INIT_LIST_HEAD(&node);
    
    struct node *nodep = NULL;
    nodep = init_node(nodep);
#define debug   0
#if DEBUG
    fprintf(stdout, "nodep :%p,%p\n", nodep, NULL);
    if (nodep != NULL)
        fprintf(stdout, "nodep->next:%p\nnodep->prev:%p\nnode->list:%p\n",
                nodep->list.next, nodep->list.prev, &nodep->list);
#endif

    
    assign_node(nodep, ++counter);
#if DEBUG
    fprintf(stdout, "node checke empty result:%d\n",
            list_empty(&node));
#endif
    list_add(&nodep->list, &node);
#if DEBUG
    fprintf(stdout, "node checke empty result:%d\n",
            list_empty(&node));
#endif
    struct list_head    *pos    = NULL;
    struct node         *entry  = NULL;
#if DEBUG
    list_for_each(pos, &node) {
        entry = list_entry(pos, struct node, list);
        fprintf(stdout, "node->num:%d\n", entry->num);
    }
#endif
    int i;
    for (i = 0; i < 10; i++) {
        if ((nodep = init_node(nodep)) != NULL) {
            assign_node(nodep, ++counter);
            list_add(&nodep->list, &node);
        }
    }
#if DEBUG 
    list_for_each(pos, &node) {
        entry = list_entry(pos, struct node, list);
        fprintf(stdout, "node->num:%d\n", entry->num);
    }
#endif    
    struct list_head   *backup;
#if 1
    list_for_each(pos, &node) {
#else
    list_for_each_safe(pos, backup, &node) {
#endif
        entry = list_entry(pos, struct node, list);
        if (entry->num == 5) {
                list_del(pos);
                destroy_node(entry);
        }
#if 0
        if (entry->num == 6) {
            list_move(pos, &node);
            break;
        }
#endif
    }
#if DEBUG
    fprintf(stdout, "check list head result :%d\n",
            list_empty(&node));
    list_for_each(pos, &node) {
        entry = list_entry(pos, struct node, list);
        fprintf(stdout, "node->num:%d\n", entry->num);
    }
#endif    
    if (!list_empty(&node))
    {
        list_for_each_safe(pos, backup, &node) {
            list_del(pos);
            entry = list_entry(pos, struct node, list);
            destroy_node(entry);
        }
    }
    return 0;
}

/* vim:set shiftwidth=4 tabstop=4 softtabstop=4: */
