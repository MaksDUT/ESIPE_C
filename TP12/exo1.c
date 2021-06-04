#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TP12.h"

#define NB_PACK 4096

/* Exercice 1 */

Node *allocate_Node(char *word)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->word = (char *)malloc(strlen(word) + 1);
    strcpy(n->word, word);
    n->next = NULL;
    return n;
}

void insert_List_First(List *l, char *word)
{
    Node *n = *l;
    Node *new = allocate_Node(word);
    new->next = n;
    *l = new;
}

void free_Node(List l)
{
    while (l)
    {
        free(l->word);
        List tmp = l;
        l = l->next;
        free(tmp);
    }
}
int find_Word_List(List l, char *word)
{
    Node *tmp = l;

    while (tmp != NULL)
    {
        if (strcmp(word, tmp->word) == 0)
        {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

int length_List(List l)
{
    Node *tmp = l;
    int count = 0;
    while (tmp != NULL)
    {
        count++;
        tmp = tmp->next;
    }
    return count;
}

void file_to_list(FILE *f, List *l)
{
    char word[100];
    while (fscanf(f, "%s", word) != EOF)
    {
        if (!find_Word_List(*l, word))
        {
            insert_List_First(l, word);
        }
    }
    fclose(f);
}

/*Exercice 2 */
tableH *create_table(int size)
{
    tableH *table = (tableH *)malloc(sizeof(tableH));
    table->table = (Node **)malloc(size * sizeof(Node *));
    table->size_table = size;
    
    int i;
    for (i = 0; i < table->size_table; i++)
    {
        table->table[i] = NULL;
    }
    return table;
}

unsigned hash(char *word)
{
    int i=0;
    unsigned h = 0;
    while(word[i] != '\0'){
        h +=  (i+1) * word[i];    
        i++;    
    }
    return h;
}

void free_table(tableH *t)
{
    int i;
    for (i = 0; i < t->size_table; i++)
    {
        free_Node(t->table[i]);
    }
    free(t->table);
    free(t);
}

void insert_Hash(tableH *t, char *word)
{
    
    int h = hash(word) % t->size_table;
    if (t->table[h] == NULL)
    {
        insert_List_First(&(t->table[h]), word);
    }
    else
    {
        if (!find_Word_List(t->table[h], word))
        {   
            insert_List_First(&(t->table[h]), word);
        }
    }
}

void file_to_hashT(FILE *f, tableH *t)
{
    char word[100];
    while (fscanf(f, "%s", word) != EOF)
    {
        insert_Hash(t,word);
    }
    fclose(f);
}

int lenght_tableH(tableH *t){
    int i;
    int count = 0;
    for(i=0;i<t->size_table;i++){
        count+= length_List(t->table[i]);
    }
    return count;
}

int main(int argc, char *argv[])
{
    FILE *f = fopen("germinal.txt", "r");

    if (f == NULL)
    {
        printf("error to open the file \n");
        return 1;
    }
    /*
    Node *list = NULL;
    file_to_list(f, &list);
    printf("%d different words found in Germinal \n", length_List(list));
    free_Node(list);
    */

    tableH * tabH = create_table(NB_PACK);
    file_to_hashT(f,tabH);
    printf("%d different words found in Germinal \n", lenght_tableH(tabH));
    free_table(tabH);
    

    return 0;
}
