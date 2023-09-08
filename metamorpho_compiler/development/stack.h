#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node
{
    int val;
    node *next;
};

typedef struct
{
    node *top;
    int n;

} stack;

void push(stack *s, int x)
{
    node *newnode = (node *) malloc(sizeof(node));
    newnode->val = x;
    newnode->next = s->top;
    s->top = newnode;
    s->n++;
}

int pop(stack *s)
{
    int val = s->top->val;
    node *next = s->top->next;
    free(s->top);
    s->top = next;
    s->n--;
    return val;
}

int is_not_empty(stack *s)
{
    return s->n;
}

void destroy(stack *s)
{
    while(is_not_empty(s))
    {
        pop(s);
    }
    free(s);
}

int look(stack *s)
{
    return s->top->val;
}
