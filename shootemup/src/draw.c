#include <MLV/MLV_all.h>
#include "draw.h"

void drawPlayer(Player *p)
{
    int x = p->center->x - (p->hit->width) / 2;
    int y = p->center->y - (p->hit->height) / 2;
    MLV_draw_filled_rectangle(x, y, p->hit->width, p->hit->height, p->color);
}

void drawAllMissile(Missile **tabM, int size)
{
    int i;
    Missile *m;
    for (i = 0; i < size; i++)
    {
        m = tabM[i];
        if (m != NULL)
        {
            drawMissile(m);
        }
    }
}
void drawAllMissileEnnemi(Missile **tabM)
{
    int i;
    Missile *m;
    for (i = 0; i < MAX_SIZE_TAB_Missile_E; i++)
    {
        m = tabM[i];
        if (m != NULL)
        {
            drawMissile(m);
        }
    }
}

void drawMissile(Missile *m)
{
    int x = m->center->x - (m->hit->width) / 2;
    int y = m->center->y - (m->hit->height) / 2;
    MLV_draw_filled_rectangle(x, y, m->hit->width, m->hit->height, m->color);
}

void drawAllEnnemis(Ennemi **tabE){
    int i;
    Ennemi *e;
    for(i = 0; i<MAX_SIZE_TAB_Ennemi;i++){
        e = tabE[i];
        if(e!=NULL){
            drawEnnemi(e);
        }
    }
}

void drawEnnemi(Ennemi *e)
{
    int x = e->center->x - (e->hit->width) / 2;
    int y = e->center->y - (e->hit->height) / 2;
    MLV_draw_filled_rectangle(x, y, e->hit->width, e->hit->height, e->color);
}

void draw_Player_Life(int pv_Player, int width, int height){

    int h = height/40; 
    int w = width/10;
    
    int x = 50;
    int y = height-(h*2);
    
    int pv_act = w/Player_PV; 

    MLV_draw_filled_rectangle(x, y, w,h, MLV_COLOR_WHITE_SMOKE);
    MLV_draw_filled_rectangle(x, y, pv_act*pv_Player,h, MLV_COLOR_GREEN);
}