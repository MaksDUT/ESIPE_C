#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <MLV/MLV_all.h>
#include "shootemup.h"

Pixel *creatPixel(int x, int y)
{
    Pixel *p = (Pixel *)malloc(sizeof(Pixel));
    p->x = x;
    p->y = y;
    return p;
}

Hitbox *creatHitbox(int w, int h)
{
    Hitbox *hit = (Hitbox *)malloc(sizeof(Hitbox));
    hit->width = w;
    hit->height = h;
    return hit;
}

Weapon *creatWeapon(char *name, int width, int lenght, int speed, int degat, int reload)
{
    Weapon *w = malloc(sizeof(Weapon));
    w->name = malloc(strlen(name));
    strcpy(w->name, name);
    w->hit = creatHitbox(width, lenght);
    w->speed = speed;
    w->reload_init = reload;
    w->reload = reload;

    w->degat = degat;
    return w;
}
Player *creatPlayer(int pv, int centerX, int centerY, int width, int lenght, int speed, MLV_Color color)
{
    Player *p = (Player *)malloc(sizeof(Player));
    p->center = creatPixel(centerX, centerY);
    p->hit = creatHitbox(width, lenght);
    p->pv = pv;
    p->w = creatWeapon("basic", 20, 20, 15, 1, 300);
    p->speed = speed;
    p->color = color;

    return p;
}

Ennemi *creatEnnemi(char *name, int pv, int centerX, int centerY, int width, int lenght, int speed, MLV_Color color, Weapon *w)
{
    Ennemi *e = (Ennemi *)malloc(sizeof(Ennemi));
    e->name = (char *)malloc((MAX_CHAR_NAME + 1) * sizeof(name));
    e->center = creatPixel(centerX, centerY);
    e->hit = creatHitbox(width, lenght);
    strcpy(e->name, name);
    e->pv = pv;
    e->w = copyWeapon(w);
    e->speed = speed;
    e->color = color;
    return e;
}

Missile *creatMissile(MLV_Color color, int degat, Pixel *center, int width, int lenght, int speed, double rad)
{
    Missile *m = (Missile *)malloc(sizeof(Missile));
    m->center = creatPixel(center->x, center->y);
    m->color = color;
    m->degat = degat;
    m->rad = rad;
    m->speed = speed;
    m->hit = creatHitbox(width, lenght);
    return m;
}

Data *creatData()
{
    Data *d = (Data *)malloc(sizeof(Data));
    d->vitesse = 15;
    d->p = creatPlayer(Player_PV, Player_CENTER_X, Player_CENTER_Y, Player_CENTER_WIDTH, Player_CENTER_LENGHT, Player_SPEED, Player_COLOR);
    d->tabMPlayer = (Missile **)malloc(MAX_SIZE_TAB_Missile_P * sizeof(Missile *));
    d->tabMEnnemi = (Missile **)malloc(MAX_SIZE_TAB_Missile_E * sizeof(Missile *));
    d->tabEnnemi = (Ennemi **)malloc(MAX_SIZE_TAB_Ennemi * sizeof(Ennemi *));

    int i;
    for (i = 0; i < MAX_SIZE_TAB_Missile_P; i++)
    {
        d->tabMPlayer[i] = NULL;
    }
    for (i = 0; i < MAX_SIZE_TAB_Missile_E; i++)
    {
        d->tabMEnnemi[i] = NULL;
    }
    for (i = 0; i < MAX_SIZE_TAB_Ennemi; i++)
    {
        d->tabEnnemi[i] = NULL;
    }

    return d;
}



/*Copy */

Ennemi *copyEnnemi(Ennemi *e)
{
    if (e != NULL)
    {
        return creatEnnemi(e->name, e->pv, e->center->x, e->center->y, e->hit->width, e->hit->height, e->speed, e->color, copyWeapon(e->w));
    }
    return NULL;
}

Weapon *copyWeapon(Weapon *w)
{
    if (w != NULL)
    {
        return creatWeapon(w->name, w->hit->width, w->hit->height, w->speed, w->degat, w->reload);
    }
    return NULL;
}

/*free structure*/

void freeHitbox(Hitbox *h)
{
    free(h);
}

void freePlayer(Player *p)
{
    free(p->center);
    freeHitbox(p->hit);
    freeWeapon(p->w);
    free(p);
}

void freeEnnemi(Ennemi *e)
{
    free(e->name);
    free(e->center);
    freeHitbox(e->hit);
    freeWeapon(e->w);
    free(e);
}

void freeWeapon(Weapon *w)
{
    free(w->name);
    freeHitbox(w->hit);
    free(w);
}

void freeMissile(Missile *m)
{
    free(m->center);
    freeHitbox(m->hit);
    free(m);
}

void freeData(Data *d)
{

    int i;
    for (i = 0; i < MAX_SIZE_TAB_Missile_P; i++)
    {
        if (d->tabMPlayer[i] != NULL)
        {
            freeMissile(d->tabMPlayer[i]);
        }
    }
    for (i = 0; i < MAX_SIZE_TAB_Missile_E; i++)
    {
        if (d->tabMEnnemi[i] != NULL)
        {
            freeMissile(d->tabMEnnemi[i]);
        }
    }
    for (i = 0; i < MAX_SIZE_TAB_Ennemi; i++)
    {
        if (d->tabEnnemi[i] != NULL)
        {
            freeEnnemi(d->tabEnnemi[i]);
        }
    }
    free(d->tabEnnemi);
    free(d->tabMEnnemi);
    free(d->tabMPlayer);
    freePlayer(d->p);

    free(d);
}

void free_Table_Ennemi_File(Ennemi **tabE)
{
    int i;
    for (i = 0; i < MAX_SIZE_TAB_Ennemi_FILE; i++)
    {
        if (tabE[i] != NULL)
        {
            freeEnnemi(tabE[i]);
        }
    }
    free(tabE);
}

void free_Table_Weapon_File(Weapon **tabW)
{
    int i;
    for (i = 0; i < MAX_SIZE_TAB_WEAPON_FILE; i++)
    {
        if (tabW[i] != NULL)
        {
            freeWeapon(tabW[i]);
        }
    }
    free(tabW);
}

//changer la position des Missiles du joueur ou Ennemi
Missile **changeMissilesPosition(Missile **tabM, int width, int height)
{
    int i;
    Missile *m;
    for (i = 0; i < MAX_SIZE_TAB_Missile_P; i++)
    {
        m = tabM[i];
        if (m != NULL)
        {
            m->center->x += cos(m->rad) * m->speed;
            m->center->y += sin(m->rad) * m->speed;
            /*  
                si jamais le changement de position rend le mission en dehors de la zone de la fenetre,
                alors on free la memoire du Missile et on rend sa valeur a NULL dans le tableau.
            */
            if ((m->center->x < 0 || m->center->x > width) || (m->center->y < 0 || m->center->y > height))
            {
                freeMissile(m);
                tabM[i] = NULL;
            }
        }
    }
    return tabM;
}

void colisionMissPlayerEnnemi(Data *data)
{
    int i, k;
    for (i = 0; i < MAX_SIZE_TAB_Ennemi; i++)
    {
        for (k = 0; k < MAX_SIZE_TAB_Missile_P; k++)
        {
            if (data->tabEnnemi[i] != NULL && data->tabMPlayer[k] != NULL)
            {
                if (isEnnemiTouch(data->tabEnnemi[i], data->tabMPlayer[k]))
                {
                    if (downEnnemiLife(&(data->tabEnnemi[i]), data->tabMPlayer[k]->degat))
                    {
                        killEnnemi(&(data->tabEnnemi), i);
                    }
                    freeMissile(data->tabMPlayer[k]);
                    data->tabMPlayer[k] = NULL;
                }
            }
        }
    }
}

void colisionMissEnnemiPlayer(Data *data, int *lose)
{
    int k;
    for (k = 0; k < MAX_SIZE_TAB_Missile_E; k++)
    {
        if (data->tabMEnnemi[k] != NULL)
        {
            if (isPlayerTouch(data->p, data->tabMEnnemi[k]))
            {
                if (downPlayerLife(&(data->p), data->tabMEnnemi[k]->degat))
                {
                    *lose = 1;
                }
                freeMissile(data->tabMEnnemi[k]);
                data->tabMEnnemi[k] = NULL;
            }
        }
    }
}

void changeEnnemisPosition(Ennemi ***tabE, int width, int height)
{
    int i;
    Ennemi *e;
    for (i = 0; i < MAX_SIZE_TAB_Ennemi; i++)
    {
        e = (*tabE)[i];
        if (e != NULL)
        {
            e->center->x += cos(Ennemi_RAD) * e->speed;
            e->center->y += sin(Ennemi_RAD) * e->speed;
            /*  
                si jamais le changement de position rend le mission en dehors de la zone de la fenetre,
                alors on free la memoire du Missile et on rend sa valeur a NULL dans le tableau.
            */
            if ((e->center->x < 0 || e->center->x > width) || (e->center->y < 0 || e->center->y > height))
            {
                freeEnnemi(e);
                (*tabE)[i] = NULL;
            }
        }
    }
}

Player *changePositionPlayer(Player *p, int width, int height)
{

    int vitesse = p->speed;

    int x = p->center->x;
    int y = p->center->y;

    if (MLV_get_keyboard_state(MLV_KEYBOARD_LSHIFT) == MLV_PRESSED)
    {
        vitesse = vitesse + (vitesse * 0.5);
    }

    if (MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED)
    {
        y += vitesse;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED)
    {
        y -= vitesse;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED)
    {
        x -= vitesse;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED)
    {
        x += vitesse;
    }

    if ((x - (p->hit->width / 2)) > 0 && (x + (p->hit->width / 2)) < width)
    {
        p->center->x = x;
    }

    if (y > 0 && y < height)
    {
        p->center->y = y;
    }

    return p;
}

/* ajout dans les tableaux (Missile, Ennemi etc..)*/

void addMissilePlayer(Missile ***tabM, Player *p)
{

    int i;
    for (i = 0; i < MAX_SIZE_TAB_Missile_P; i++)
    {
        if ((*tabM)[i] == NULL)
        {
            Missile *m = creatMissile(MLV_COLOR_SKY_BLUE, p->w->degat, p->center, p->w->hit->width, p->w->hit->height, p->w->speed, Player_RAD);
            (*tabM)[i] = m;
            return;
        }
    }
}

/* ajout dans les tableaux (Missile, Ennemi etc..)*/

void addMissileEnnemi(Missile ***tabM, Ennemi *e, Player *p)
{

    double sous1 = p->center->x - e->center->x;
    double sous2 = p->center->y - e->center->y;

    /*Missile sur la traj du joueur*/
    double angle = atan((sous2) / (sous1));
    if (sous1 < 0)
    {
        angle = angle + M_PI;
    }

    int i;
    for (i = 0; i < MAX_SIZE_TAB_Missile_P; i++)
    {
        if ((*tabM)[i] == NULL)
        {
            Missile *m = creatMissile(MLV_COLOR_RED, e->w->degat, e->center, e->w->hit->width, e->w->hit->height, e->w->speed, angle);
            (*tabM)[i] = m;
            return;
        }
    }
}

int is_Table_Ennemi_Empty(Ennemi **tabE)
{
    int i;
    Ennemi *e;
    for (i = 0; i < MAX_SIZE_TAB_Ennemi; i++)
    {
        e = tabE[i];
        if (e != NULL)
        {
            return 0;
        }
    }
    return 1;
}

void fireEnnemiWithTime(Ennemi ***tabE, Missile ***tabM, Player *p, int time)
{
    int i;
    Ennemi *e;
    for (i = 0; i < MAX_SIZE_TAB_Ennemi; i++)
    {
        e = (*tabE)[i];
        if (e != NULL)
        {
            if (time % e->w->reload == 0)
            {
                e->w->reload = rand() % e->w->reload_init + (e->w->reload_init - e->w->reload_init / 2);
                addMissileEnnemi(tabM, e, p);
            }
        }
    }
}

Ennemi *findEnnemiInTableByName(char *name, Ennemi **table, int size_table)
{
    Ennemi *e;
    int i;
    for (i = 0; i < size_table; i++)
    {
        e = table[i];
        if (e != NULL)
        {
            if (strcmp(e->name, name) == 0)
            {
                return e;
            }
        }
    }
    return NULL;
}

Weapon *findWeaponInTableByName(char *name, Weapon **table, int size_table)
{
    Weapon *w;
    int i;
    for (i = 0; i < size_table; i++)
    {
        w = table[i];
        if (w != NULL)
        {
            if (strcmp(w->name, name) == 0)
            {
                return w;
            }
        }
    }
    return NULL;
}

void addEnnemiINTable(Ennemi *e, Ennemi ***tabE)
{

    int i;
    Ennemi *EnnemiTable;
    for (i = 0; i < MAX_SIZE_TAB_Ennemi; i++)
    {
        EnnemiTable = (*tabE)[i];
        if (EnnemiTable == NULL)
        {
            //e = creatEnnemi("tutu", 2, (50 + i * 50) % 1920, 50, 25, 25, 15, MLV_COLOR_BROWN4);
            (*tabE)[i] = e;
            return;
        }
    }
}

int isEnnemiTouch(Ennemi *e, Missile *m)
{

    int xe1 = e->center->x - (e->hit->width) / 2;
    int ye1 = e->center->y - (e->hit->height) / 2;
    int xe2 = e->center->x + (e->hit->width) / 2;
    int ye2 = e->center->y + (e->hit->height) / 2;

    int xm1 = m->center->x - (m->hit->width) / 2;
    int ym1 = m->center->y - (m->hit->height) / 2;
    int xm2 = m->center->x + (m->hit->width) / 2;
    int ym2 = m->center->y + (m->hit->height) / 2;

    if ((xm1 >= xe2) || (xm2 <= xe1) || (ym1 >= ye2) || (ym2 <= ye1))
    {
        return 0;
    }
    return 1;
}

int isPlayerTouch(Player *p, Missile *m)
{

    int xe1 = p->center->x - (p->hit->width) / 2;
    int ye1 = p->center->y - (p->hit->height) / 2;
    int xe2 = p->center->x + (p->hit->width) / 2;
    int ye2 = p->center->y + (p->hit->height) / 2;

    int xm1 = m->center->x - (m->hit->width) / 2;
    int ym1 = m->center->y - (m->hit->height) / 2;
    int xm2 = m->center->x + (m->hit->width) / 2;
    int ym2 = m->center->y + (m->hit->height) / 2;

    if ((xm1 >= xe2) || (xm2 <= xe1) || (ym1 >= ye2) || (ym2 <= ye1))
    {
        return 0;
    }
    return 1;
}
/* enleve le nombre de degat au pv du joueur
    renvoie 0 si le joueur est toujours en vie
    1 sinon.
 */
int downPlayerLife(Player **p, int degat)
{
    (*p)->pv -= degat;
    if ((*p)->pv <= 0)
    {
        return 1;
    }
    return 0;
}

/* enleve le nombre de degat au pv de l'Ennemi
    renvoie 0 si le joueur est toujours en vie
    1 sinon.
 */
int downEnnemiLife(Ennemi **e, int degat)
{
    (*e)->pv -= degat;
    if ((*e)->pv <= 0)
    {
        return 1;
    }
    return 0;
}

void killEnnemi(Ennemi ***tab, int index)
{
    if ((*tab)[index]->pv <= 0)
    {
        freeEnnemi((*tab)[index]);
        (*tab)[index] = NULL;
    }
}

Ennemi **create_Table_Ennemi_File(char *fileString, Weapon **tabWeapon)
{
    int i;
    Ennemi **tabEnnemis = (Ennemi **)malloc(MAX_SIZE_TAB_Ennemi_FILE * sizeof(Ennemi *));
    for (i = 0; i < MAX_SIZE_TAB_Ennemi_FILE; i++)
    {
        tabEnnemis[i] = NULL;
    }
    
    int pv, center_x, center_y, width, lenght, speed;
    char *name = (char *)malloc((MAX_CHAR_NAME + 1) * sizeof(name));
    MLV_Color color;
    char weapon[25];
    int index = 0;

    FILE *file = fopen(fileString, "r");
    if (file == NULL)
    {
        printf("Error File %s not found \n", fileString);
        exit(-1);
    }
    char l[500];
    char scolor[60];
    int ret;
    while (fgets(l, sizeof(l), file) != NULL)
    {
        if (l[0] != '#')
        {
            ret = sscanf(l, "%s %d %d %d %d %d %d %s %s", name, &pv, &center_x, &center_y, &width, &lenght, &speed, scolor, weapon);
            if (ret != -1)
            {
                /*
                printf("name: %s, pv: %d, center_x: %d, center_y: %d, width: %d, lenght: %d, speed: %d, color: %s \n \n", name, pv, center_x, center_y, width, lenght, speed, scolor);
                */
                color = MLV_convert_string_to_color(scolor);
                Weapon *w = findWeaponInTableByName(weapon, tabWeapon, MAX_SIZE_TAB_WEAPON_FILE);
                tabEnnemis[index] = creatEnnemi(name, pv, center_x, center_y, width, lenght, speed, color, w);
                index++;
            }
        }
    }
    fclose(file);

    return tabEnnemis;
}

Weapon **create_Table_Weapon_File(char *fileString)
{
    int i;
    Weapon **tabWeapon = malloc(MAX_SIZE_TAB_WEAPON_FILE * sizeof(Weapon *));
    for (i = 0; i < MAX_SIZE_TAB_WEAPON_FILE; i++)
    {
        tabWeapon[i] = NULL;
    }
        int width, lenght, speed, degat, reload;
    char *name = (char *)malloc((MAX_CHAR_NAME + 1) * sizeof(name));
    //MLV_Color color;

    int index = 0;

    FILE *file = fopen(fileString, "r");
    if (file == NULL)
    {
        printf("Error File %s not found \n", fileString);
        exit(-1);
    }
    char l[500];
    int ret;
    while (fgets(l, sizeof(l), file) != NULL)
    {
        if (l[0] != '#')
        {
            ret = sscanf(l, "%s %d %d %d %d %d", name, &width, &lenght, &speed, &degat, &reload);
            if (ret != -1)
            {
                /*
                printf("name: %s, pv: %d, center_x: %d, center_y: %d, width: %d, lenght: %d, speed: %d, color: %s \n \n", name, pv, center_x, center_y, width, lenght, speed, scolor);
                */
                tabWeapon[index] = creatWeapon(name, width, lenght, speed, degat, reload);
                index++;
            }
        }
    }
    fclose(file);

    return tabWeapon;
}

int get_numbers_ennemi(Ennemi **tabEnnemis){
    int i;
    int count =0;
    for(i=0;i<MAX_SIZE_TAB_Ennemi_FILE;i++){
        if(tabEnnemis[i]!=NULL){
            count++;
        }
    }
    return count;
}