#include <stdio.h>
#include <stdlib.h>


char** init_array_char(int n,int m){
    int i;
    char** t;
    if((t=(char**)malloc(n*sizeof(char*))) == NULL){
        printf("probleme avec la memoire malloc \n");
    }
    for(i=0;i<n;i++){
        if((t[i]=(char*)malloc(m*sizeof(char))) == NULL){
            printf("probleme avec la memoire malloc \n");
        }
    }
    return t;
}

void free_array_double_char(char** t,int n){
    if(t==NULL) return;
    int i;
    for(i=0;i<n;i++){
        if(t[i]!=NULL) free(t[i]);
    }
    free(t);
    return;
}

void feed_array_char(char** t,int n,int m){
    if(n<0 || m<0) return;
    int i,j,k;
    for(i=0;i<n;i++){
        k=i;
        for(j=0;j<m;j++){
            k=k%26;
            t[i][j]=('a'+k);
            k++;
        }
    }
}

void print_array_char(char** t, int n, int m){
    if(n<0 || m<0) return;
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            printf("%c ",t[i][j]);
        }
        printf("\n");
    }
}


int main(int argc, char const *argv[])
{
    int n,m;
    printf("Donnez deux dimensions entières :");
    scanf("%d %d",&n,&m);
    char** t=init_array_char(n,m);
    feed_array_char(t,n,m);
    print_array_char(t,n,m);

    return 0;
}
