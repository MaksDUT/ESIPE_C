#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "array.h"

/* main to test the compilation of the allocation and free
    functions. 
    */
int main(int argc, char *argv[])
{
    srand(time(NULL));
    int size = 15;

    int *tab = random_array(size, 101);
    int *tab2 = random_array(size, 101);

    printf("\n\n*******************************************************\n");
    printf("\n********************* Test TP5 ************************\n");
    printf("\n*******************************************************\n");

    printf("\narray with value random  size : %d: \n", size);
    printf("tab ->	");
    print_array(tab);
    printf("\n");
    printf("tab2 ->	");
    print_array(tab2);
    printf("\n");

    size = 0;
    tab = random_array(size, 101);
    tab2 = random_array(size, 101);
    printf("\narray with value random  size : %d: \n", size);
    printf("tab ->	");
    print_array(tab);
    printf("\n");
    printf("tab2 ->	");
    print_array(tab2);
    printf("\n");

    size = 5;
    tab = random_array(size, 101);
    tab2 = random_array(size, 101);
    printf("\narray with value random  size : %d: \n", size);
    printf("tab ->	");
    print_array(tab);
    printf("\n");
    printf("tab2 ->	");
    print_array(tab2);
    printf("\n");

    int *tab3 = concat_array(tab, tab2);
    print_array(tab3);

    printf("\n\n*******************************************************\n");
    printf("\n****************** Trie fusion ************************\n");
    printf("\n*******************************************************\n");

    tab2 = merge_sort(tab2);
    printf("\nHere is the sorted array : \n");
    print_array(tab2);
    printf("\n");

    free_integer_array(tab);
    free_integer_array(tab2);
    free_integer_array(tab3);

    printf("\n\n*******************************************************\n");
    printf("\n********************* Test FIN ************************\n");
    printf("\n*******************************************************\n");

    return 0;
}
