#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;

    list_ele_t *Node;
    list_ele_t *Next_Node;
    Node = q->head;
    while (Node) {
        free(Node->value);
        Next_Node = Node->next;
        free(Node);
        Node = Next_Node;
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL)
        return false;
    /* TODO: What should you do if the q is NULL? */
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->value = (char *) malloc(sizeof(char) * strlen(s) + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }
    memset(newh->value, 0x00, sizeof(char) * strlen(s) + 1);
    memcpy(newh->value, s, sizeof(char) * strlen(s));

    if (q->size == 0) {
        newh->next = NULL;
        q->head = newh;
        q->tail = newh;
    } else {
        newh->next = q->head;
        q->head = newh;
    }
    q->size++;
    return true;
}



/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (q == NULL)
        return false;
    list_ele_t *new_node;
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    new_node = malloc(sizeof(list_ele_t));
    if (!new_node)
        return false;

    new_node->value = malloc(sizeof(char) * strlen(s) + 1);
    if (!new_node->value) {
        free(new_node);
        return false;
    }
    new_node->next = NULL;
    memset(new_node->value, 0x00, sizeof(char) * strlen(s) + 1);
    memcpy(new_node->value, s, sizeof(char) * strlen(s));

    if (q->size == 0) {
        q->head = new_node;
        q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || sp == NULL || q->head == NULL || q->size == 0)
        return false;

    size_t value_size = strlen(q->head->value);
    memset(sp, 0x00, bufsize);
    if (bufsize <= value_size)
        memcpy(sp, q->head->value, bufsize - 1);
    else
        memcpy(sp, q->head->value, value_size);

    list_ele_t *remove_head;
    remove_head = q->head;

    q->size--;
    if (q->size == 0) {
        q->head = NULL;
        q->tail = NULL;
    } else {
        q->head = q->head->next;
    }
    free(remove_head->value);
    free(remove_head);
    return true;
}


/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */

void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head || q->size == 1)
        return;
    list_ele_t *Node = q->head;
    list_ele_t *Old_Node;
    list_ele_t *Next_Node = q->head->next;
    for (int i = 1; i <= (q->size); i++) {
        if (i == 1) {
            Node->next = NULL;
            q->tail = Node;
        } else if (i == q->size) {
            Node->next = Old_Node;
            q->head = Node;
            return;
        } else {
            Node->next = Old_Node;
        }
        Old_Node = Node;
        Node = Next_Node;
        Next_Node = Next_Node->next;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */

void MoveNode(list_ele_t **destRef, list_ele_t **sourceRef)
{
    /* the front source node  */
    list_ele_t *newNode = *sourceRef;
    assert(newNode != NULL);

    /* Advance the source pointer */
    *sourceRef = newNode->next;

    /* Link the old dest off the new node */
    newNode->next = *destRef;

    /* Move dest to point to the new node */
    *destRef = newNode;
}

list_ele_t *sorted_merge(list_ele_t *a, list_ele_t *b)
{
    // a dummy first node to hang the result on
    list_ele_t dummy;
    // tail points to the last result node
    list_ele_t *tail = &dummy;

    dummy.next = NULL;

    while (1) {
        if (a == NULL) {
            tail->next = b;
            break;
        } else if (b == NULL) {
            tail->next = a;
            break;
        }
        if (strcmp(a->value, b->value) < 0) {
            MoveNode(&(tail->next), &a);
        } else {
            MoveNode(&(tail->next), &b);
        }

        tail = tail->next;
    }
    return (dummy.next);
}

void front_back_split(list_ele_t *head,
                      list_ele_t **front_ref,
                      list_ele_t **back_ref)
{
    // if length is less than 2
    if (head == NULL || head->next == NULL) {
        *front_ref = head;
        *back_ref = NULL;
        return;
    }

    list_ele_t *slow = head;
    list_ele_t *fast = head->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front_ref = head;
    *back_ref = slow->next;
    slow->next = NULL;
}
void merge_sort(list_ele_t **head)
{
    if (*head == NULL || (*head)->next == NULL)
        return;

    list_ele_t *a;
    list_ele_t *b;

    front_back_split(*head, &a, &b);

    merge_sort(&a);
    merge_sort(&b);

    *head = sorted_merge(a, b);
}

void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->head == NULL)
        return;

    merge_sort(&q->head);

    list_ele_t *tmp_node = q->head;
    while (tmp_node->next) {
        tmp_node = tmp_node->next;
    }
    q->tail = tmp_node;
}