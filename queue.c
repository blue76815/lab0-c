#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (head == NULL)
        return NULL;
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (head == NULL)
        return;

    element_t *node = NULL, *tmp_node = NULL;
    list_for_each_entry_safe(node, tmp_node, head, list) {
        list_del(&node->list);
        q_release_element(node);
    }
    free(head);
}


/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (s == NULL || head == NULL)
        return false;
    element_t *node = malloc(sizeof(element_t));
    if (node == NULL)
        return false;

    node->value = (char *) malloc(sizeof(char) * strlen(s) + 1);
    if (node->value == NULL) {
        q_release_element(node);
        return false;
    }
    memset(node->value, '\0', sizeof(char) * strlen(s) + 1);
    memcpy(node->value, s, sizeof(char) * strlen(s));
    list_add(&node->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (head == NULL || s == NULL)
        return false;

    element_t *node = malloc(sizeof(element_t));

    if (node == NULL)
        return false;


    node->value = (char *) malloc(sizeof(char) * strlen(s) + 1);
    if (node->value == NULL) {
        q_release_element(node);
        return false;
    }
    memset(node->value, '\0', sizeof(char) * strlen(s) + 1);
    memcpy(node->value, s, sizeof(char) * strlen(s));
    list_add_tail(&node->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (head == NULL || list_empty(head))
        return NULL;

    element_t *node = list_first_entry(head, element_t, list);

    list_del_init(&(node->list));

    if (sp) {
        size_t length = strlen(node->value) + 1;
        length = length > bufsize ? bufsize : length;
        memset(sp, '\0', length);
        memcpy(sp, node->value, length - 1);
    }
    return node;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (head == NULL || list_empty(head))
        return NULL;

    element_t *node = list_last_entry(head, element_t, list);

    list_del_init(&(node->list));

    if (sp) {
        size_t length = strlen(node->value) + 1;
        length = length > bufsize ? bufsize : length;
        memset(sp, '\0', length);
        memcpy(sp, node->value, length - 1);
    }

    return node;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (head == NULL || list_empty(head))
        return 0;

    int size = 0;
    struct list_head *node = NULL;

    list_for_each(node, head) {
        size++;
    }
    return size;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
