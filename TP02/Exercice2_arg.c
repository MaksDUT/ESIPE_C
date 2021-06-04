#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Erreur\n");
        return 1;
    }
    int entier1;
    int entier2;
    int somme;

    entier1 = atoi(argv[1]);
    entier2 = atoi(argv[2]);
    somme = entier1 + entier2;

    printf("\n\n\n---------------------------------------- \n");
    printf("----------- TEST EXO2_arg -------------- \n");
    printf("---------------------------------------- \n");

    printf("résultat de la somme : %d \n\n", somme);

    printf("---------------------------------------- \n");
    printf("-------------- FIN TEST ---------------- \n");
    printf("---------------------------------------- \n\n\n");
    return 0;
}