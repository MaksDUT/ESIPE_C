#ifndef __BACKGROUND__
#define __BACKGROUND__

#include <stdlib.h>
#include <MLV/MLV_all.h>

#define MAX_STAR 300

typedef struct _stars
{
    int x[MAX_STAR];
    int y[MAX_STAR];
    int size[MAX_STAR];
    int speed[MAX_STAR];
    int active[MAX_STAR];
    /*int r[MAX_STAR];
    int g[MAX_STAR];
    int b[MAX_STAR];*/
} Stars;

Stars *create_stars(int width);
void change_stars(Stars *s, int height);
void active_stars(Stars *s);
void print_stars(Stars *s);
void draw_star(int x, int y, int taille);

#endif