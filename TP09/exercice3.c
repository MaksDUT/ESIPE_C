#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief intialize the array
 * 
 * @param n 
 * @param argv 
 * @return char** 
 */
char** init_array_char(int n,char *argv[]){
    int i;
    char** t;
    if((t=(char**)malloc(n*sizeof(char*))) == NULL){
        printf("probleme avec la memoire malloc \n");
    }
    for(i=0;i<n;i++){
        if((t[i]=(char*)malloc((strlen(argv[i])+1))) == NULL){
            printf("probleme avec la memoire malloc \n");
        }
    }
    return t;
}

/**
 * @brief free the array
 * 
 * @param t 
 * @param n 
 */
void free_array_double_char(char** t,int n){
    if(t==NULL) return;
    int i;
    for(i=0;i<n;i++){
        if(t[i]!=NULL) free(t[i]);
    }
    free(t);
    return;
}
/**
 * @brief filled the array with the program's arguments 
 * 
 * @param t 
 * @param n 
 * @param argv 
 */
void feed_array_char(char** t,int n,char *argv[]){
    if(n<0) return;
    int i,j;
    j=0;
    for(i=0;i<n;i++){
        while(argv[i][j]!='\0'){
            t[i][j]=argv[i][j];
            j++;
        }
        t[i][j]='\0';
        j=0;
    }
}

/**
 * @brief print the array
 * 
 * @param t 
 * @param n 
 */
void print_array_char(char** t, int n){
    if(n<0) return;
    int i,j;
    j=0;
    for(i=0;i<n;i++){
        printf("arg[%d] --> ",i);
        while(t[i][j]!='\0'){
            printf("%c",t[i][j]);
            j++;
        }
        j=0;
        printf("\n");
    }
}


int main(int argc, char *argv[])
{

    char** t=init_array_char(argc,argv);
    feed_array_char(t,argc,argv);
    print_array_char(t,argc);
    free_array_double_char(t,argc);
    return 0;
}
