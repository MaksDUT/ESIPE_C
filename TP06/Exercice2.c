#include <stdio.h>
#include <stdlib.h>

#define N 3

void initialize_tab(int (*tab)[], int size);
void permutations(int buffer[], int current, int max);
void print_tab(int tab[]);

/* Display indentation following the depth of recursion */
void make_space(int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("  ");
}

/* Recursive function displaying the height of the execution stack */
int stack_adr(int n, int *height, int *start_adr)
{
    int p = n;
    if (n >= 0)
    {
        make_space(n);
        printf("Recursive climbing call : %d\n", p);
        make_space(n);
        printf("Adr pointer : %p and Adr local variable : %p\n", height, &p);
        make_space(n);
        printf("Stack jump : %ld\n", height - &p);
        make_space(n);
        printf("Stack total height : %ld\n\n", start_adr - &p);
        stack_adr(n - 1, &p, start_adr);
        make_space(n);
        printf("Recursive descending call : %d\n", p);
        make_space(n);
        printf("Stack total height : %ld\n\n", start_adr - &p);
    }
    else
    {
        printf("LAST RECURSION\n\n");
    }
    return p;
}

int main(int argc, char *argv[])
{
    /*int i;
    if (argc != 2)
    {
        fprintf(stderr, "Nope, I need one positive integer in argument to work properly.\n");
    }

    stack_adr(atoi(argv[1]), &i, &i);
    */
    int tab[N];
    initialize_tab(&tab, N);
    print_tab(tab);
    permutations(tab, 1, N);
    return 0;
}

void permutations(int buffer[], int current, int max)
{

    if (current > max)
    {
        print_tab(buffer);
        return;
    }

    int i;
    for (i=0; i < N; i++)
    {
        if (buffer[i] == 0)
        {
            buffer[i] = current;
            permutations(buffer, current + 1, max);
            buffer[i] = 0;
        }
    }
}

void initialize_tab(int (*tab)[], int size)
{
    int i;
    for (i=0; i < size; i++)
    {
        (*tab)[i] = 0;
    }
    return ;
}

void print_tab(int tab[])
{
    int i;
    printf("[%d", tab[0]);
    for (i=1; i < N; i++)
    {
        printf(",%d", tab[i]);
    }
    printf("]\n");
}
