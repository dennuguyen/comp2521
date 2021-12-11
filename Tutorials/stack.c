/**
 * Stack implementation using linked lists.
 * 
 * Recursion is used where iteration is possible.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _Stack
{
    int data;
    struct _Stack *next;
} Stack;

Stack *init()
{
    return NULL;
}

void destroy(Stack **s)
{
    if (*s == NULL)
        return;
    destroy(&((*s)->next));
    free(*s);
    *s = NULL;
}

void push(Stack **s, int data)
{
    Stack *head = malloc(sizeof(Stack)); // Allocate heap memory.

    if (head == NULL)
    {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(1);
    }

    head->data = data; // Set data.
    head->next = *s;   // Point head to current pointer.
    *s = head;         // Update current pointer to head.
}

void pop(Stack **s)
{
    if (*s != NULL)
    {
        Stack *temp = *s; // Create temporary pointer to head.
        *s = temp->next;  // Reassign head pointer.
        free(temp);       // Deallocate memory.
    }
}

int empty(Stack *s)
{
    return s == NULL;
}

void peek(Stack *s)
{
    !empty(s) ? printf("%d\n", s->data) : fprintf(stderr, "Error: Stack is empty.\n");
}

int len(Stack **s)
{
    if (*s == NULL)
        return 0;
    return 1 + len(&((*s)->next));
}

void print(Stack **s)
{
    if (*s == NULL)
        return;
    print(&((*s)->next));
    printf("%d ", (*s)->data);
}

int main(void)
{
    // Stack *s = &(Stack){.data = 1, .next = NULL}; // Compound literal

    Stack *s = init();
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    pop(&s);
    peek(s);

    return 0;
}
