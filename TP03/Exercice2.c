#include <stdio.h>

/*
print the number of characters, words, and line write in the default input until a signal EOF.
*/
void wc()
{
    int countC = 0, countW = 0, countL = 0;
    char c;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t' || c == ' ')
        {
            countW += 1;
        }
        if (c == '\n')
        {
            countL += 1;
            countW += 1;
        }
        countC += 1;
    }
    printf("\n %d / %d / %d \n", countC, countW, countL);
}
int main(int arc, char *arv[])
{

    printf("\n\n\n---------------------------------------- \n");
    printf("------------- TEST EXO2 ---------------- \n");
    printf("---------------------------------------- \n\n");

    printf("enter text as you want. \nIf you want to stop : (Ctrl + d) \n");

    wc();
    printf("---------------------------------------- \n");
    printf("-------------- FIN TEST ---------------- \n");
    printf("---------------------------------------- \n\n\n");
    return 0;
}
