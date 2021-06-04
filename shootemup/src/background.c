#include "background.h"




Stars *create_stars(int width){
    
    Stars *s = malloc(sizeof(Stars));
    int i;
    int ecart = width/MAX_STAR;
    for(i=0;i<MAX_STAR;i++){
        s->x[i]=ecart*i;
        s->y[i]=0;
        s->size[i]= rand() %5;
        s->active[i]=0;
        s->speed[i] = 10 - rand()%5;
    }
    return s;
}

void change_stars(Stars *s,int height){
    int i;
    for(i=0;i<MAX_STAR;i++){
        if(s->active[i]){
            s->y[i]+=s->speed[i];
            if(s->y[i]>height){
                s->y[i]=0;
                s->active[i]=0;
            }
        }
    }
}

void active_stars(Stars *s){
    int i;
    while(1){
        i = rand()%MAX_STAR;
        if(!s->active[i]){
            s->active[i]=1;
            return;
        }
    }
}

void print_stars(Stars *s){
    int i;
    for(i=0;i<MAX_STAR;i++){
        if(s->active[i]==1){
            draw_star(s->x[i],s->y[i],s->size[i]);
        }
    }
}

void draw_star(int x,int y,int taille)
{
    int xr = x - (taille) / 2;
    int yr = y - (taille) / 2;
    MLV_draw_filled_rectangle(xr, yr, taille, taille, MLV_COLOR_WHITE_SMOKE);
}