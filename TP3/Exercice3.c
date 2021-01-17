#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
*Computes the value of a raised to the power exponent.
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
*Find if theString is a string with only number. 
@param theString is a String variable.
*/
int isnume(char *theString)
{
    return atoi(theString);
}

/*
*Find if theString is a string with only lowercase alphabetical character. 
@param theString is a String variable.
*/
int islowerTest(char *theString)
{
    int i = 0;
    while (theString[i] != '\0')
    {
        if (!(theString[i] >= 'a' && theString[i] <= 'z'))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

/*
char* base10to26(char* theString){
    int i=0;
    int value;
    int string=atoi(theString);
    int rest;
    char* resultat="";
    char charbase26[27]="abcdefghijklmnopqrstuvwyz";
    do{
        string=string/26;
        rest=string%26;

        strcat(resultat,)


    }while()

}*/

/*
*Convert theString which is on base 10 to base 26 (only print). 
@param theString is a String variable.
*/
void base10to26R(int value)
{
    int rest;
    if (value < 26)
    {
        printf("%c", 'a' + value);
        return;
    }
    rest = value % 26;
    value = value / 26;
    base10to26R(value);
    printf("%c", 'a' + rest);
}

/*
*Convert theString which is on base 26 to base 10. 
@param theString is a String variable.
*/
void base26to10(char *theString)
{
    int i = 0;
    int y = 0;
    int value = 0;
    int len = strlen(theString) - 1;
    while (theString[i] != '\0')
    {
        y = theString[i] - 'a';
        value += puissance(26, len) * y;
        len--;
        i++;
    }
    printf("%d", value);
}

/*
*find if theString is on base 10 or 26 and convert it in the other base. 
@param theString is a String variable.
*/
void converbase(char *theString)
{
    if (islowerTest(theString))
    {
        base26to10(theString);
    }
    else if (isnume(theString))
    {
        base10to26R(isnume(theString));
    }
    else
    {
        printf("-ERROR-");
    }
}

int main(int argc, char *argv[])
{

    /*	TEST	*/
    char *chaineTest = "dy";
    char *numTest = "102";
    char *errorTest = "dy102";

    /*	AFFICHAGE TEST	*/
    printf("\n\n\n---------------------------------------- \n");
    printf("------------- TEST EXO3 ---------------- \n");
    printf("---------------------------------------- \n");
    printf("	%s	-----> ", numTest);
    converbase(numTest);
    printf("\n");
    printf("	%s	-----> ", chaineTest);
    converbase(chaineTest);
    printf("\n");
    printf("	%s	-----> ", errorTest);
    converbase(errorTest);
    printf("\n");
    printf("---------------------------------------- \n");
    printf("-------------- FIN TEST ---------------- \n");
    printf("---------------------------------------- \n\n\n");

    return 0;
}