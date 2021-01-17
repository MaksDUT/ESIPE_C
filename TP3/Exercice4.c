#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void tabRandom(int tab[], int n);
void affichageTableInt(int list[], int len);
void trieBull(int list[], int len);
int find(int list[], int len, int valeur);
int findR(int list[], int debut, int fin, int valeur);

int main(int argc, char *argv[])
{

    time_t t;
    srand(time(&t));

    int len = 12;
    int list[len];
    tabRandom(list, len);

    printf("\n\n\n---------------------------------------- \n");
    printf("------------- TEST EXO4 ---------------- \n");
    printf("---------------------------------------- \n");

    printf("len = %d \n", len);
    affichageTableInt(list, len);
    trieBull(list, len);

    printf("taille = %d \n", (int)(sizeof(list) / sizeof(int)));
    printf("resultat pour la recherche de 78: %d \n", find(list, len, 78));

    printf("---------------------------------------- \n");
    printf("-------------- FIN TEST ---------------- \n");
    printf("---------------------------------------- \n\n\n");
    return 0;
}
/*
*Fills a table of size n with random values. 
@param tab[] table of int.
@param n the size of the table.
*/
void tabRandom(int tab[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        tab[i] = rand() % 101;
    }
}
/*
*Sort the table. Displays the table at each step of the sorting process.
@param list[] table of int.
@param len the size of the table.
*/
void trieBull(int list[], int len)
{
    int i, j;
    int z = 0;

    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < len - 1 - i; j++)
        {

            if (list[j] > list[j + 1])
            {
                z = list[j];
                list[j] = list[j + 1];
                list[j + 1] = z;
            }
        }
        affichageTableInt(list, len);
        j = 0;
    }
}
/*
*Displays the table.
@param list[] table of int.
@param len the size of the table.
*/
void affichageTableInt(int list[], int len)
{
    int i;
    printf("[");
    for (i = 0; i < len; i++)
    {
        printf("%d, ", list[i]);
    }
    printf("] \n");
}

/*
*Find if the value is in a table sorted.
@return 0 if valeur is not in the table. 1 if not.
@param list[] table of int.
@param len the size of the table.
@param valeur is the value you want to find.
*/
int find(int list[], int len, int valeur)
{
    if (len == 0)
        return 0;
    return findR(list, 0, len, valeur);
}

/*
int findR(int list[],int position,int len,int valeur){
    int test = (position+1)/2;
    if(position<0 || position>len) return 0;
    if(list[position]==valeur) return 1;

    if(list[position]>valeur){
        position=position-test;
    }else{
        position=position+test;
    }
    return findR(list,position, len,valeur);
}
*/

/*
*Find if the value is in the table.
@return 0 if valeur is not in the table. 1 if not.
@param list[] table of int.
@param debut for the start of the search.
@param fin for the end of the search.
@param valeur is the value you want to find.
*/
int findR(int list[], int debut, int fin, int valeur)
{
    int ecart = fin - debut;
    int intermediaire = (ecart / 2) + debut;
    if (ecart <= 1)
        return 0;
    if (list[intermediaire] == valeur)
        return 1;
    if (list[intermediaire] < valeur)
    {
        debut = intermediaire;
    }
    else
    {
        fin = intermediaire;
    }
    return findR(list, debut, fin, valeur);
}
