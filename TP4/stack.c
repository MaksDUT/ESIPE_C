#include <stdio.h>
#include "stack.h"

static Stack stack;

int main(int argc, char *argv[])
{
    stack_init();
    int i;

    printf("value if empty :%d \n", stack_is_empty());
    for (i=0; i < 5; i++)
    {
        stack_push(145 + i);
        stack_display();
    }
    printf("value of the top :%d \n", stack_top());
    printf("value of the pop:%d \n", stack_pop());
    stack_display();
    printf("value if empty :%d \n", stack_is_empty());
    return 0;
}

void stack_init(void)
{
    stack.size = 0;
    stack.values[MAX_SIZE];
}

int stack_size(void)
{
    return stack.size;
}

int stack_is_empty(void)
{
    return stack.size ? 0 : 1;
}

int stack_top(void)
{
    return stack.values[stack.size];
}
int stack_pop(void)
{
    stack.size--;
    return stack.values[stack.size + 1];
}

void stack_push(int n)
{
    if (!(stack.size >= MAX_SIZE))
    {
        stack.size++;
        stack.values[stack.size] = n;
    }
}

void stack_display(void)
{
    int i;
    printf("---pile--- \n");
    for (i = stack.size; i > 0; i--)
    {
        printf("(%d) --> %d \n", i, stack.values[i]);
    }
    printf("---------- \n");
}

int stack_get_element(int index)
{
    if (index > MAX_SIZE)
        return EOF;
    return stack.values[index];
}
