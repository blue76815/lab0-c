#include "queue.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (head == NULL || list_empty(head))
        return false;

    struct list_head *fast = head->next;
    struct list_head *slow = head->next;
    while (fast != head && fast->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    element_t *ele_node = list_entry(slow, element_t, list);
    list_del(slow);
    free(ele_node->value);
    free(ele_node);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (head == NULL || list_empty(head))
        return false;
    struct list_head *node, *tmp;
    bool last_same_node = false;
    list_for_each_safe(node, tmp, head) {
        element_t *curr_element_t = list_entry(node, element_t, list);
        const element_t *next_element_t =
            list_entry(node->next, element_t, list);
        if (node->next != head &&
            strcmp(curr_element_t->value, next_element_t->value) == 0) {
            last_same_node = true;
            list_del(node);
            free(curr_element_t->value);
            free(curr_element_t);
        } else if (last_same_node == true) {
            last_same_node = false;
            list_del(node);
            free(curr_element_t->value);
            free(curr_element_t);
        }
    }
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (head == NULL || list_empty(head)) {
        return;
    }
    struct list_head *node = head->next, *next_node, *tmp_node;
    while (node != head) {
        next_node = node->next;
        tmp_node = node->next;
        node->next = node->prev;
        node->prev = tmp_node;
        node = next_node;
    }
    tmp_node = head->next;
    head->next = head->prev;
    head->prev = tmp_node;
}

// * @descend: whether or not to sort in descending order
struct list_head *mergeTwoLists(struct list_head *L1,
                                struct list_head *L2,
                                bool descend)
{
    struct list_head *head = NULL;
    struct list_head **ptr = &head;
    for (; L1 && L2; ptr = &(*ptr)->next) {
        const element_t *L1_element_t = list_entry(L1, element_t, list);
        const element_t *L2_element_t = list_entry(L2, element_t, list);
        if ((strcmp(L1_element_t->value, L2_element_t->value) <= 0) !=
            descend) {
            *ptr = L1;
            L1 = L1->next;
        } else {
            *ptr = L2;
            L2 = L2->next;
        }
    }
    *ptr = (struct list_head *) ((uintptr_t) L1 | (uintptr_t) L2);
    return head;
}


/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
static struct list_head *mergesort_list(struct list_head *head, bool descend)
{
    if (!head || !head->next || list_is_singular(head))
        return head;

    struct list_head *slow = head;
    for (const struct list_head *fast = head->next; fast && fast->next;
         fast = fast->next->next)
        slow = slow->next;
    struct list_head *mid = slow->next;
    slow->next = NULL;

    struct list_head *left = mergesort_list(head, descend),
                     *right = mergesort_list(mid, descend);
    return mergeTwoLists(left, right, descend);
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
    if (head == NULL || list_empty(head) || k <= 1) {
        return;
    }
    struct list_head *cur, *safe, *origin_list = head;

    LIST_HEAD(new_cut_list);
    int count = 0;
    list_for_each_safe(cur, safe, head) {
        count++;
        if (count == k) {
            list_cut_position(&new_cut_list, origin_list, cur);
            q_reverse(&new_cut_list);
            list_splice_init(&new_cut_list, origin_list);
            count = 0;
            origin_list = safe->prev;
        }
    }
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend)
{
    if (head == NULL || list_empty(head)) {
        return;
    }
    head->prev->next = NULL;
    head->next = mergesort_list(head->next, descend);
    struct list_head *ptr = head;
    while (ptr->next != NULL) {
        ptr->next->prev = ptr;
        ptr = ptr->next;
    }
    ptr->next = head;
    head->prev = ptr;
}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    if (head == NULL || list_empty(head) || list_is_singular(head)) {
        return 0;
    }
    struct list_head *curr = head->prev;
    struct list_head *next = curr->prev;
    while (next != head) {
        const element_t *curr_entry = list_entry(curr, element_t, list);
        element_t *next_entry = list_entry(next, element_t, list);

        if (strcmp(curr_entry->value, next_entry->value) < 0) {
            list_del(next);
            q_release_element(next_entry);

        } else {
            curr = next;
        }

        next = curr->prev;
    }
    return q_size(head);
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    if (head == NULL || list_empty(head) || list_is_singular(head)) {
        return 0;
    }
    struct list_head *curr = head->prev;
    struct list_head *next = curr->prev;
    while (next != head) {
        const element_t *curr_entry = list_entry(curr, element_t, list);
        element_t *next_entry = list_entry(next, element_t, list);

        if (strcmp(curr_entry->value, next_entry->value) > 0) {
            list_del(next);
            q_release_element(next_entry);

        } else {
            curr = next;
        }

        next = curr->prev;
    }
    return q_size(head);
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
