#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Cell *allocate_cell(char *first, char *last, int age)
{
    Cell *cel = (Cell *)malloc(sizeof(Cell));
    cel->first_name = (char *)malloc(strlen(first) + 1);
    cel->last_name = (char *)malloc(strlen(last) + 1);
    cel->age = age;
    strcpy(cel->first_name, first);
    strcpy(cel->last_name, last);
    cel->next = NULL;
    return cel;
}

int age_order(Cell *p1, Cell *p2)
{
    int val = p1->age - p2->age;
    if (val == 0)
    {
        return strcmp(p1->last_name, p2->last_name);
    }
    return val;
}

int name_order(Cell *p1, Cell *p2)
{
    int val = strcmp(p1->last_name, p2->last_name);
    if (val == 0)
    {
        return p1->age - p2->age;
    }
    return val;
}

void ordered_insertion(List *l, Cell *new, int order_func(Cell *, Cell *))
{
    Cell *cel = *l;
    Cell *tmp = NULL;

    while (cel != NULL && order_func(cel, new) < 0)
    {
        tmp = cel;
        cel = cel->next;
    }

    new->next = cel;

    if (tmp != NULL)
    {
        tmp->next = new;
    }
    else
    {
        *l = new;
    }
}

void print_list(List l)
{
    Cell *tmp = l;
    printf("[ ");
    while (tmp != NULL)
    {
        printf("name %s %s ,age : %d | ", tmp->first_name, tmp->last_name, tmp->age);
        tmp = tmp->next;
    }
    printf(" ]\n");
}

void free_list(List l)
{
    while (l)
    {
        free(l->first_name);
        free(l->last_name);
        List tmp = l;
        l = l->next;
        free(tmp);
    }
}

int main(int argc, char const *argv[])
{
    FILE *f = fopen("list_nom.txt", "r");
    if (f == NULL)
    {
        printf("error to open the file \n");
    }

    char first[100];
    char last[100];
    int age = -1;

    Cell *lage = NULL;
    Cell *lalpha = NULL;
    Cell *new = NULL;
    Cell *new2 = NULL;
    while (fscanf(f, "%s %s %d", first, last, &age) != EOF)
    {
        new = allocate_cell(first, last, age);
        new2 = allocate_cell(first, last, age);
        ordered_insertion(&lage, new, age_order);
        /*printf("name %s %s ,age : %d \n", lage->first_name, lage->last_name, lage->age);*/
        /*
        print_list(lage);
        printf("test \n");
        printf("name %s %s ,age : %d \n", lalpha->first_name, lalpha->last_name, lalpha->age);
        */
        ordered_insertion(&lalpha, new2, name_order);
    }
    fclose(f);
    printf("titi \n");
    /*print */
    print_list(lage);
    printf("############################################\n");
    print_list(lalpha);

    /*free list */
    free_list((lage));
    free_list((lalpha));
    return 0;
}
