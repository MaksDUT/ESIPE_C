#ifndef __TP10_H__
#define __TP10_H__

typedef struct _cell
{
    char *first_name;
    char *last_name;
    int age;
    struct _cell *next;
} Cell, *List;

Cell *allocate_cell(char *first, char *last, int age);
int age_order(Cell *p1, Cell *p2);
int name_order(Cell *p1, Cell *p2);
void ordered_insertion(List *l, Cell *new, int order_func(Cell *, Cell *));
void print_list(List l);
void free_list(List l);

#endif