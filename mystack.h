#include <stdio.h>

struct stack
{
    double arr[50];
    int index;
};

struct stack_ch
{
    char arr[50];
    int index;
};

void push_val(double, struct stack *);
double pop_val(struct stack *);
void push_char(char, struct stack_ch *);
char pop_char(struct stack_ch *);
void view_val(struct stack *);
void view_char(struct stack_ch *);

void push_val(double n, struct stack *s)
{
    if (s->index == 49)
    {
        printf("\nint stack is full");
        return;
    }
    s->arr[++s->index] = n;
}

double pop_val(struct stack *s)
{
    double ret = -1;
    if (s->index == -1)
    {
        printf("\nstack is empty");
        return ret;
    }
    ret = s->arr[s->index--];
    return ret;
}

void view_val(struct stack *s)
{
    int i = 0;
    if (s->index == -1)
    {
        printf("stack is empty");
        return;
    }
    for (i = s->index; i >= 0; i--)
    {
        printf("\n%d\t%lf", i, s->arr[i]);
    }
}

void push_char(char n, struct stack_ch *c)
{
    if (c->index == 49)
    {
        printf("\nchar stack is full");
        return;
    }
    c->arr[++c->index] = n;
}

char pop_char(struct stack_ch *c)
{
    char ret = -1;
    if (c->index == -1)
    {
        printf("\nchar stack is empty");
        return ret;
    }
    ret = c->arr[c->index--];
    return ret;
}

void view_char(struct stack_ch *c)
{
    int i = 0;
    if (c->index == -1)
    {
        printf("stack is empty");
        return;
    }
    for (i = c->index; i >= 0; i--)
    {
        printf("\n%d\t%c", i, c->arr[i]);
    }
}