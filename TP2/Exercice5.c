#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    printf("\n\n\n---------------------------------------- \n");
    printf("------------- TEST EXO5 ---------------- \n");
    printf("---------------------------------------- \n");

    FILE *test = fopen("Exercice5.c", "r");
    char ch;
    if (test == NULL)
        exit(1);
    ch = fgetc(test);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(test);
    }
    fclose(test);

    printf("\n---------------------------------------- \n");
    printf("-------------- FIN TEST ---------------- \n");
    printf("---------------------------------------- \n\n\n");
    return 0;
}