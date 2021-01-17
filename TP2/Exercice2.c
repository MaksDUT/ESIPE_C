#include <stdio.h>

int main(int argc, char *argv[])
{
    int entier1;
    int entier2;
    int somme;

    printf("\n\n\n---------------------------------------- \n");
    printf("------------- TEST EXO2 ---------------- \n");
    printf("---------------------------------------- \n");

    printf("\nentrez deux entiers :");
    scanf("%d %d", &entier1, &entier2);
    somme = entier1 + entier2;
    printf("résultat de la somme : %d \n\n", somme);

    printf("---------------------------------------- \n");
    printf("-------------- FIN TEST ---------------- \n");
    printf("---------------------------------------- \n\n\n");

    return 0;
}