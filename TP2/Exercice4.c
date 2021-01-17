#include <stdio.h>

void print_var(int n)
{
    printf("Value of the variable : %d\n", n);
}

void print_pointer(int *p)
{
    printf("Pointer address : %p and Pointed value : %d\n", p, *p);
}

void set_pointer(int *p, int n)
{
    *p = n;
}

int main(int argc, char *argv[])
{
    int a;
    int *p = &a;
    print_var(a);
    a = 53;
    print_var(a);
    print_pointer(p);
    set_pointer(p, 42);
    print_var(a);

    return 0;
}

/* pour bien comprendre
    ici le but et de montrer comment fonctionne un pointeur.
    et de bien expliquer que un poiteur c'est l'adresse qui amene a un espace memoire.

    ici la valeur de 'a' est à une adresse de la memoire.
    'p' est un pointeur qui ce trouve à la meme adresse de la memoire grace à la ligne 17.
    si on change la valeur que pointe 'p' alors la variable 'a' va elle aussi changer.
*/
