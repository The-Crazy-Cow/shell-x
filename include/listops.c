// SPDX-License-Identifier: GPL-2.0

/**
 * @file listops.c
 * @author jd (jdj17180@gmail.com)
 * @brief  handle list instrusive operations like in linux kernel
 * @version 0.1
 * @date 2026-08-27
 * 
 * @copyright GNU General Public License v2.0
 * 
 */
#include "listops.h"
#include "errors.h"
#include <errno.h>
#include <stdio.h>

/**
 * init_list - Initialize a doubly linked list
 * @l:    List descriptor to initialize
 * @head: Initial head node (or NULL for empty list)
 *
 * Return: 0 on success, >0 on failure.
 */
int init_list(list *l, struct node *head)
{
    if (!l)
        return -1;

    l->head = head;
    if (head) {
        head->prev = NULL;
        head->next = NULL;
    }

    return 0;
}

/**
 * list_add_node - Append a node to the end of the list
 * @l:    Target list
 * @node: Node to append
 *
 * Return: 0 on success, >0 on failure.
 */
int list_add_node(list *l, struct node *node)
{
    struct node *n;

    if (!l || !node)
        return -1;

    node->next = NULL;

    if (!l->head) {
        node->prev = NULL;
        l->head = node;
        return 0;
    }

    n = l->head;
    while (n->next) {
        n = n->next;
    }

    n->next = node;
    node->prev = n;

    return 0;
}

/**
 * list_del_node - Detach a node from its list
 * @l: Target list descriptor (optional, can be NULL)
 * @n: Node to remove
 *
 * Return: 0 on success, >0 on failure.
 */
int list_del_node(list *l, struct node *n)
{
    if (!n)
        return -1;

    if (n->prev)
        n->prev->next = n->next;
    else if (l && l->head == n)
        l->head = n->next;

    if (n->next)
        n->next->prev = n->prev;

    n->prev = NULL;
    n->next = NULL;

    return 0;
}

/**
 * get_node_elem - Retrieve container structure pointer from node offset
 * @n:      Pointer to embedded node
 * @offset: Byte offset of node within container struct
 *
 * Return: Pointer to container structure, or NULL if @n is NULL.
 *
 * @brief: need to cast it in element type on return
 */
void *get_node_elem(struct node *n, size_t offset)
{
    if (!n)
        return NULL;

    return (void *)((char *)n - offset);
}
