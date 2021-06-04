#include <stdio.h>
#include <stdlib.h>

#include "array.h"

int *allocate_integer_array(int size)
{
    int *new_tab;

    new_tab = (int *)malloc((size + 1) * sizeof(int));
    if (new_tab == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }
    return new_tab;
}

void free_integer_array(int *tab)
{
    free(tab);
}

int array_size(int *array)
{
    int i = 0;
    while (array[i] != -1)
    {
        i++;
    }
    return i;
}

void print_array(int *array)
{
    int i = 0;
    while (array[i] != -1)
    {
        printf("%d ", array[i]);
        i++;
    }
    return;
}

int are_arrays_equal(int *first, int *second)
{
    if (array_size(first) != array_size(second))
        return 0;
    int i = 0;
    while (first[i] != -1)
    {
        if (first[i] != second[i])
            return 0;
        i++;
    }
    return 1;
}

int *copy_array(int *array)
{

    int size = array_size(array);
    int *copy = allocate_integer_array(size);

    int i = 0;
    while (array[i] != -1)
    {
        copy[i] = array[i];
        i++;
    }
    return copy;
}

int *fill_array(void)
{

    int size = 0;
    printf("Entrez la longeur du tableau :");
    scanf("%d", &size);
    int *tab = allocate_integer_array(size);

    int i;
    int valeur = 0;
    for (i = 0; i <= size; i++)
    {
        printf("entrez une valeur positif : ");
        scanf("%d", &valeur);
        if (valeur == -1)
        {
            break;
        }
        else if (valeur > 0)
        {
            tab[i] = valeur;
        }
    }
    tab[i + 1] = -1;
    return tab;
}

int *random_array(int size, int max_entry)
{

    int *tab = allocate_integer_array(size + 1);
    int i;
    for (i = 0; i < size; i++)
    {
        tab[i] = rand() % max_entry;
    }
    tab[i] = -1;
    return tab;
}

int *concat_array(int *first, int *second)
{

    int size2 = array_size(second);
    int size1 = array_size(first);
    int *tab = allocate_integer_array(size1 + size2);
    int i;

    for (i = 0; i < size1; i++)
    {
        tab[i] = first[i];
    }
    for (i = 0; i < size2; i++)
    {
        tab[size1 + i] = second[i];
    }
    tab[size1 + size2] = -1;
    return tab;
}

int *merge_sorted_arrays(int *first, int *second)
{

    printf("Merge the two following ones :\n");
    print_array(first);
    printf("\n");
    print_array(second);
    printf("\n");

    int size1 = array_size(first);
    int size2 = array_size(second);
    int sizetab = size1 + size2 + 1;
    int *tab = allocate_integer_array(sizetab);

    int cont_first = 0;
    int cont_second = 0;
    int cont_tab;

    for (cont_tab = 0; cont_tab < sizetab; cont_tab++)
    {

        if (cont_first >= size1)
        {
            tab[cont_tab] = second[cont_second];
            cont_second++;
        }
        else if (cont_second >= size2)
        {
            tab[cont_tab] = first[cont_first];
            cont_first++;
        }
        else if (first[cont_first] < second[cont_second])
        {
            tab[cont_tab] = first[cont_first];
            cont_first++;
        }
        else
        {
            tab[cont_tab] = second[cont_second];
            cont_second++;
        }
    }
    tab[cont_tab] = -1;

    print_array(tab);
    printf("\n\n");
    return tab;
}

void split_arrays(int *array, int **first, int **second)
{
    int size = array_size(array);
    int sizetab = size / 2;
    int sizetab2 = sizetab;

    *first = allocate_integer_array(sizetab + 1);

    if (size % 2 == 1)
        sizetab2++;
    *second = allocate_integer_array(sizetab2 + 1);

    int size1 = sizetab;

    int i;
    for (i = 0; i < size1; i++)
    {
        (*first)[i] = array[i];
    }
    (*first)[i] = -1;
    for (i = i; i < size; i++)
    {
        (*second)[i - size1] = array[i];
    }
    (*second)[i - size1] = -1;
}

int *merge_sort(int *array)
{
    int size = array_size(array);
    if (size <= 1)
    {
        return array;
    }
    int *first = NULL, *second = NULL;
    split_arrays(array, &first, &second);
    printf("Split array in two part : \n");
    print_array(array);
    printf("\n");
    print_array(first);
    printf("\n");
    print_array(second);
    printf("\n\n");
    return merge_sorted_arrays(merge_sort(first), merge_sort(second));
}