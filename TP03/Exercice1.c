#include <stdio.h>
/*
*Computes the value of 'a' raised to the power exponent.
@param a is a int.
@param n is a int.
*/
int puissance(int a, int n)
{
    if (n == 0)
        return 1;
    int result = a;
    int i;
    for (i = 1; i < n; i++)
    {
        result = result * a;
    }
    return result;
}
/*
*Computes the value of a raised to the power exponent. 
*The fonction is Recursive.
@param a is a int.
@param n is a int.
*/
int puissanceR(int a, int n)
{
    if (n == 0)
        return 1;
    return (puissance(a, n - 1) * a);
}

int main(int argc, char *argv[])
{
    int a = 2;
    int n = 10;

    printf("\n\n\n---------------------------------------- \n");
    printf("------------- TEST EXO1 ---------------- \n");
    printf("---------------------------------------- \n");

    printf("Fonction puissance(a,n) pour a=%d et n=%d   -> %d\n", a, n, puissance(a, n));
    printf("Fonction puissanceR(a,n) pour a=%d et n=%d   -> %d\n", a, n, puissanceR(a, n));

    printf("---------------------------------------- \n");
    printf("-------------- FIN TEST ---------------- \n");
    printf("---------------------------------------- \n\n\n");

    return 0;
}
