#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TP12.h"

#define NB_PACK 4096

/* Exercice 1 */

/**
 * @brief create a Node
 * 
 * @param word 
 * @return Node* 
 */
Node *allocate_Node(char *word)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->word = (char *)malloc(strlen(word) + 1);
    strcpy(n->word, word);
    n->next = NULL;
    return n;
}

/**
 * @brief insert a word into the list
 * 
 * @param list 
 * @param word 
 */
void insert_List_First(List *list, char *word)
{
    Node *n = *list;
    Node *new = allocate_Node(word);
    new->next = n;
    *list = new;
}

/**
 * @brief free a node
 * 
 * @param list 
 */
void free_Node(List list)
{
    while (list)
    {
        free(list->word);
        List tmp = list;
        list = list->next;
        free(tmp);
    }
}

/**
 * @brief return true (1) if the word is in the list
 * 
 * @param list 
 * @param word 
 * @return int 
 */
int find_Word_List(List list, char *word)
{
    Node *tmp = list;

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

/**
 * @brief return the size of the list (number of word)
 * 
 * @param list 
 * @return int 
 */
int length_List(List list)
{
    Node *tmp = list;
    int count = 0;
    while (tmp != NULL)
    {
        count++;
        tmp = tmp->next;
    }
    return count;
}

/**
 * @brief read a file and put into the list all the word
 * 
 * @param f 
 * @param list 
 */
void file_to_list(FILE *f, List *list)
{
    char word[100];
    while (fscanf(f, "%s", word) != EOF)
    {
        if (!find_Word_List(*list, word))
        {
            insert_List_First(list, word);
        }
    }
    fclose(f);
}

/*Exercice 2 */

/**
 * @brief Create a hash table
 * 
 * @param size 
 * @return tableH* 
 */
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

/**
 * @brief hash function
 * 
 * @param word 
 * @return unsigned 
 */
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

/**
 * @brief free the hash table
 * 
 * @param table 
 */
void free_table(tableH *table)
{
    int i;
    for (i = 0; i < table->size_table; i++)
    {
        free_Node(table->table[i]);
    }
    free(table->table);
    free(table);
}

/**
 * @brief insert a word in the hash table
 * 
 * @param table 
 * @param word 
 */
void insert_Hash(tableH *table, char *word)
{
    
    int h = hash(word) % table->size_table;
    if (table->table[h] == NULL)
    {
        insert_List_First(&(table->table[h]), word);
    }
    else
    {
        if (!find_Word_List(table->table[h], word))
        {   
            insert_List_First(&(table->table[h]), word);
        }
    }
}

/**
 * @brief read a file and put into the hash table all the word
 * 
 * @param f 
 * @param table 
 */
void file_to_hashT(FILE *f, tableH *table)
{
    char word[100];
    while (fscanf(f, "%s", word) != EOF)
    {
        insert_Hash(table,word);
    }
    fclose(f);
}

/**
 * @brief return the number of word  in the hash table
 * 
 * @param table 
 * @return int 
 */
int lenght_tableH(tableH *table){
    int i;
    int count = 0;
    for(i=0;i<table->size_table;i++){
        count+= length_List(table->table[i]);
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
    /*Exo1*/
    printf("Exo1 with list: \n");
    Node *list = NULL;
    file_to_list(f, &list);
    printf("%d different words found in Germinal \n", length_List(list));
    free_Node(list);
    
    f = fopen("germinal.txt", "r");

    /*Exo2*/
    printf("Exo2 with hash table: \n");
    tableH * tabH = create_table(NB_PACK);
    file_to_hashT(f,tabH);
    printf("%d different words found in Germinal \n", lenght_tableH(tabH));
    free_table(tabH);
    

    return 0;
}
