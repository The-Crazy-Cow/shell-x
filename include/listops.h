// SPDX-License-Identifier: GPL-2.0

#ifndef INCLUDE_LISTOPS_H
#define INCLUDE_LISTOPS_H

#include "errors.h"
#include <stddef.h>
#include <sys/types.h>

/**
 * struct node - Intrusive doubly linked list node
 * @prev: Pointer to previous node (NULL if first)
 * @next: Pointer to next node (NULL if last)
 */
struct node {
    struct node *prev;
    struct node *next;
};

/**
 * struct list - Doubly linked list descriptor
 * @head: Pointer to first node (NULL if empty)
 */
typedef struct list {
    struct node *head;
} list;

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)
#endif

/**
 * container_of - Cast a member pointer back to its containing structure
 * @ptr:    Pointer to the member
 * @type:   Type of the container struct
 * @member: Name of the member within the struct
 */
#ifndef container_of
#define container_of(ptr, type, member)                                        \
    ((type *)((char *)(ptr)-offsetof(type, member)))
#endif

int init_list(list *l, struct node *head);
int list_add_node(list *l, struct node *node);
int list_del_node(list *l, struct node *n);
void *get_node_elem(struct node *n, size_t offset);

/**
 * is_node_have_list - Check if a node is linked into a list
 * @n: Node to check
 *
 * Return: 0 if linked, ER_NOT_BELONGS_TO_LIST otherwise.
 */
static inline int is_node_have_list(struct node *n)
{
    if (!n)
        return ER_NOT_BELONGS_TO_LIST;
    if (!(n->prev || n->next))
        return ER_NOT_BELONGS_TO_LIST;

    return 0;
}

/**
 * list_is_empty - Check if a list is empty
 * @l: List descriptor to check
 *
 * Return: 1 if empty or NULL, 0 otherwise.
 */
static inline int list_is_empty(const list *l)
{
    return !l || l->head == NULL;
}

#endif /* INCLUDE_LISTOPS_H */
