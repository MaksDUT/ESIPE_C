#include <stdio.h>

/**
 * @brief swap function that work with all object
 * 
 * @param z1 
 * @param z2 
 * @param size 
 */
void swap_mem(void* z1,void* z2,size_t size){
    int i;

    char t;
    char *c1=(char*)z1;
    char *c2=(char*)z2;

    for(i=0;i<size;i++){
        t=c1[i];
        c1[i]=c2[i];
        c2[i]=t;
    }
}

int main(int argc, char const *argv[])
{
    int a = 12;
    int b = 42;
    printf("a -> %d and b -> %d \n",a,b);
    swap_mem(&a,&b,sizeof(int));
    printf("after swap \n");
    
    printf("a -> %d and b -> %d \n",a,b);

    return 0;
}
