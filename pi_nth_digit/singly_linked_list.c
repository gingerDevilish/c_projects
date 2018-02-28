#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "singly_linked_list.h"

node *create_node(void *data, node *next)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("Node creation error\n");
        exit(0);
    }
    new_node->data = data;
    new_node->next = next;

    return new_node;
}

node *prepend(node **head, void *data)
{
    if (head == NULL)
    {
        return NULL;
    }
    node *new_node = create_node(data, *head);
    *head = new_node;
    return new_node;
}

typedef void (*callback)(node *data);

void traverse(node *head, callback f)
{
    node *cursor = head;
    while (cursor != NULL)
    {
        f(cursor);
        cursor = cursor->next;
    }
}

int count(node *head)
{
    node *cursor = head;
    int c = 0;
    while (cursor != NULL)
    {
        c++;
        cursor = cursor->next;
    }
    return c;
}

node *append(node **head, void *data)
{
    if (head == NULL)
    {
        return NULL;
    }
    node *new_node = create_node(data, (node*)NULL);
    node *cursor = *head;
    if (cursor != 0)
    {
        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }
        cursor->next = new_node;
    }
    else
    {
        *head = new_node;
    }
    return new_node;
}

node *insert_after(node *head, void *data, node *prev)
{
    node *cursor = head;
    while ((cursor != prev) && (cursor != NULL))
    {
        cursor = cursor->next;
    }
    if (cursor != NULL)
    {
        node *new_node = create_node(data, cursor->next);
        cursor->next = new_node;
        return new_node;
    }
    else
    {
        return NULL;
    }
}

node *insert_before(node **head, void *data, node *nxt)
{
    if (head == NULL)
    {
        return NULL;
    }
    if ((*head) == NULL)
    {
        return prepend(head, data);
    }
    if (nxt == NULL)
    {
        return append(head, data);
    }
    node *cursor = *head;
    while (cursor != NULL)
    {
        if (cursor->next == nxt)
        {
            break;
        }
        cursor = cursor->next;
    }
    if (cursor != NULL)
    {
        node *new_node = create_node(data, cursor->next);
        cursor->next = new_node;
        return new_node;
    }
    else
    {
        return NULL;
    }
}

node *remove_front(node **head)
{
    if (head == NULL)
    {
        return NULL;
    }
    if (*head == NULL)
    {
        return NULL;
    }
    node *front = *head;
    *head = (*head)->next;
    front->next = NULL;
    return front;
}

node *remove_back(node **head)
{
    if (head == NULL)
    {
        return NULL;
    }
    if (*head == NULL)
    {
        return NULL;
    }
    node *cursor = *head;
    node *back = NULL;
    while (cursor->next != NULL)
    {
        back = cursor;
        cursor = cursor->next;
    }
    if (back != NULL)
    {
        back->next = NULL;
    }
    if (cursor == *head)
    {
        *head = NULL;
    }
    return cursor;
}

node *remove_any(node **head, node *nd)
{
    if (head == NULL)
    {
        return NULL;
    }
    if (nd == *head)
    {
        return remove_front(head);
    }
    if (nd->next == NULL)
    {
        return remove_back(head);
    }
    node *cursor = *head;
    while (cursor != NULL)
    {
        if (cursor->next == nd)
        {
            break;
        }
        cursor = cursor->next;
    }
    if (cursor != NULL)
    {
        node *tmp = cursor->next;
        cursor->next = tmp->next;
        tmp->next = NULL;
        return tmp;
    }
    return NULL;
}

void dispose(node *head)
{
    node *cursor, *tmp;
    if (head != NULL)
    {
        cursor = head->next;
        head->next = NULL;
        while (cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
        free(head);
    }
}

node *search(node *head, void *data)
{
    node *cursor = head;
    while (cursor != NULL)
    {
        if (cursor->data == data)
        {
            return cursor;
        }
        cursor = cursor->next;
    }
    return NULL;
}