#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_info_zone(void *adr){
    size_t *info_adr = (size_t *)adr;
    printf("Zone a l'adresse : %p\n",adr); 
    printf("%lu \n",info_adr[0]); 
    printf("%lu \n",info_adr[-1]); 
    printf("%lu \n",info_adr[-2]); 
    printf("%lu - %lu  = %lu \n",info_adr[0],info_adr[-1],info_adr[0]+info_adr[-1]); 
}

int main(int argc, char *argv[])
{
    char * toto = (char *)malloc((strlen("tototo")+1)*sizeof(char));
    toto = strcpy(toto,"toto");
    print_info_zone(&toto);
    free(toto);
    print_info_zone(&toto);
    return 0;
}
