#include <stdio.h>
#include <stdlib.h>

typedef struct _singly_linked_node
{
    void* data;
    struct _singly_linked_node *next;
} node;

node *create_node(void* data, node *next);
node *prepend(node **head, void* data);
typedef void (*callback)(node *data);
void traverse(node *head, callback f);
int count(node *head);
node *append(node **head, void* data);
node *insert_after(node *head, void* data, node *prev);
node *insert_before(node **head, void* data, node *nxt);
node *remove_front(node **head);
node *remove_back(node **head);
node *remove_any(node **head, node *nd);
void dispose(node *head);
node *search(node *head, void* data);