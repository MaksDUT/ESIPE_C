#ifndef __TP12_H__
#define __TP12_H__

typedef struct _node
{
    char *word;
    struct _node *next;
} Node, *List;

typedef struct _table
{
    Node **table;
    int size_table;

} tableH;

/* Node function */
Node *allocate_Node(char *word);
void insert_List_First(List *l, char *word);
void free_Node(List l);
int find_Word_List(List l, char *word);
int length_List(List l);

/*table function */


#endif