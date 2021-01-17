#include <stdio.h>

void printdouble(int n)
{
    int num = n;
    int ti[num * 2];
    int y = 0;
    for (y = 0; y < num; y++)
    {
        ti[num + y] = y + 1;
        ti[num - y - 1] = y + 1;
    }

    for (y = 0; y < num * 2; y++)
    {
        printf("%d ", ti[y]);
    }
    printf("\n");
    return;
}

void printdoubleRec(int n)
{
    if (n == 0)
        return;
    printf("%d ", n);
    if (n == 1)
    {
        printf("%d ", n);
        return;
    }
    printdoubleRec(n - 1);
    printf("%d ", n);
}

int main(int argc, char *argv[])
{
    int n = 10;

    printf("\n\n\n---------------------------------------- \n");
    printf("------------- TEST EXO3 ---------------- \n");
    printf("---------------------------------------- \n");

    printf("Pour n =%d :\n", n);
    printf("display fonction printdouble() :	");
    printdouble(n);
    printf("display fonction printdoubleRec() :	");
    printdoubleRec(n);

    n = 0;

    printf("\nPour n =%d :\n", n);
    printf("display fonction printdouble() :	");
    printdouble(n);
    printf("display fonction printdoubleRec() :	");
    printdoubleRec(n);

    printf("\nL'affichage ici est normal \"0\" n'est pas compris dans l'affichage\n");

    n = 1;

    printf("\nPour n =%d :\n", n);
    printf("display fonction printdouble() :	");
    printdouble(n);
    printf("display fonction printdoubleRec() :	");
    printdoubleRec(n);

    printf("\n---------------------------------------- \n");
    printf("-------------- FIN TEST ---------------- \n");
    printf("---------------------------------------- \n\n\n");
    return 0;
}