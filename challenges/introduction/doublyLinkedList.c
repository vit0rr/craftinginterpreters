// To get some practice with pointers, define a doubly linked list of heap-allocated strings.
// Write functions to insert, find, and delete items from it. Test them.
// Ref.: https://en.wikipedia.org/wiki/Doubly_linked_list#Inserting_a_node
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char *value;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct List
{
    Node *head;
    Node *tail;
} List;

// Allocates a new node with the given value and returns a pointer to it
Node *create_node(char *value)
{
    Node *node = malloc(sizeof(Node));
    node->value = malloc(strlen(value) + 1);
    strcpy(node->value, value);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Inserts a new node with the given value at the front of the list
void insert_front(List *list, char *value)
{
    Node *node = create_node(value);
    if (list->head == NULL)
    {
        // The list is empty
        list->head = node;
        list->tail = node;
    }
    else
    {
        // The list is not empty
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
}

// Inserts a new node with the given value at the back of the list
void insert_back(List *list, char *value)
{
    Node *node = create_node(value);
    if (list->tail == NULL)
    {
        // The list is empty
        list->head = node;
        list->tail = node;
    }
    else
    {
        // The list is not empty
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
}

// Searches for the first node with the given value and returns a pointer to it, or NULL if not found
Node *find(List *list, char *value)
{
    Node *current = list->head;
    while (current != NULL && strcmp(current->value, value) != 0)
    {
        current = current->next;
    }
    return current;
}

// Deletes the first node with the given value
void delete(List *list, char *value)
{
    Node *node = find(list, value);
    if (node == NULL)
        return; // Node not found
    if (node->prev != NULL)
        node->prev->next = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    if (node == list->head)
        list->head = node->next;
    if (node == list->tail)
        list->tail = node->prev;
    free(node->value);
    free(node);
}

// Frees all memory used by the list
void destroy(List *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        Node *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    free(list);
}

// Prints the list
void print_list(List *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        printf("%s ", current->value);
        current = current->next;
    }
    printf(" (head: %s, tail: %s) %s\n", list->head->value, list->tail->value);
}

int main()
{
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;

    insert_front(list, "first");
    insert_front(list, "second");
    insert_back(list, "third");
    insert_back(list, "fourth");
    print_list(list); // second first third fourth (head: second, tail: fourth)

    delete (list, "second");
    delete (list, "fourth");
    print_list(list); // first third (head: first, tail: third)

    Node *node = find(list, "first");
    printf("Found: %s\n", node->value); // Found: first

    destroy(list);
    return 0;
}