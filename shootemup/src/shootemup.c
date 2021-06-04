#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <MLV/MLV_all.h>
#include "shootemup.h"

pixel *creatPixel(int x, int y)
{
    pixel *p = (pixel *)malloc(sizeof(pixel));
    p->x = x;
    p->y = y;
    return p;
}

hitbox *creatHitbox(int w, int h)
{
    hitbox *hit = (hitbox *)malloc(sizeof(hitbox));
    hit->width = w;
    hit->height = h;
    return hit;
}

Weapon *creatWeapon(char * name,int width,int lenght,int speed,int degat, int reload){
    Weapon *w= malloc(sizeof(Weapon));
    w->name = malloc(strlen(name));
    strcpy(w->name,name);
    w->hit = creatHitbox(width,lenght);
    w->speed = speed;
    w->reload_init = reload;
    w->reload=reload;

    w->degat = degat;
    return w;
} 
player *creatPlayer(int pv, int centerX, int centerY, int width, int lenght, int speed, MLV_Color color)
{
    player *p = (player *)malloc(sizeof(player));
    p->center = creatPixel(centerX, centerY);
    p->hit = creatHitbox(width, lenght);
    p->pv = pv;
    p->w = creatWeapon("basic",20,20,15,1,300);
    p->speed = speed;
    p->color = color;

    return p;
}


Ennemi *creatEnemie(char *name, int pv, int centerX, int centerY, int width, int lenght, int speed, MLV_Color color,Weapon *w)
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

missile *creatMissile(MLV_Color color, int degat, pixel *center, int width, int lenght, int speed, double rad)
{
    missile *m = (missile *)malloc(sizeof(missile));
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
    d->p = creatPlayer(PLAYER_PV, PLAYER_CENTER_X, PLAYER_CENTER_Y, PLAYER_CENTER_WIDTH, PLAYER_CENTER_LENGHT, PLAYER_SPEED, PLAYER_COLOR);
    d->tabMPlayer = (missile **)malloc(MAX_SIZE_TAB_MISSILE_P * sizeof(missile *));
    d->tabMEnemie = (missile **)malloc(MAX_SIZE_TAB_MISSILE_E * sizeof(missile *));
    d->tabEnemie = (Ennemi **)malloc(MAX_SIZE_TAB_ENEMIE * sizeof(Ennemi *));

    int i;
    for (i = 0; i < MAX_SIZE_TAB_MISSILE_P; i++)
    {
        d->tabMPlayer[i] = NULL;
    }
    for (i = 0; i < MAX_SIZE_TAB_MISSILE_E; i++)
    {
        d->tabMEnemie[i] = NULL;
    }
    for (i = 0; i < MAX_SIZE_TAB_ENEMIE; i++)
    {
        d->tabEnemie[i] = NULL;
    }

    return d;
}

Ennemi **create_Table_Enemie_File(char *file, Weapon **tabWeapon)
{
    int i;
    Ennemi **tabEnemies = (Ennemi **)malloc(MAX_SIZE_TAB_ENEMIE_FILE * sizeof(Ennemi *));
    for (i = 0; i < MAX_SIZE_TAB_ENEMIE_FILE; i++)
    {
        tabEnemies[i] = NULL;
    }
    CreatTableOfEnemies(file, &tabEnemies,tabWeapon);
    return tabEnemies;
}

Weapon **create_Table_Weapon_File(char *file)
{
    int i;
    Weapon **tabWeapon = malloc(MAX_SIZE_TAB_WEAPON_FILE * sizeof(Weapon *));
    for (i = 0; i < MAX_SIZE_TAB_WEAPON_FILE; i++)
    {
        tabWeapon[i] = NULL;
    }
    CreatTableOfWeapon(file, &tabWeapon);
    return tabWeapon;
}

/*Copy */

Ennemi *copyEnemie(Ennemi *e)
{
    if (e != NULL)
    {
        return creatEnemie(e->name, e->pv, e->center->x, e->center->y, e->hit->width, e->hit->height, e->speed, e->color,copyWeapon(e->w));
    }
    return NULL;
}

Weapon *copyWeapon(Weapon *w){
    if(w!=NULL){
        return creatWeapon(w->name,w->hit->width,w->hit->height,w->speed,w->degat,w->reload);
    }
    return NULL;
}

/*free structure*/

void freeHitbox(hitbox *h)
{
    free(h);
}

void freePlayer(player *p)
{
    free(p->center);
    freeHitbox(p->hit);
    freeWeapon(p->w);
    free(p);
}

void freeEnemie(Ennemi *e)
{
    free(e->name);
    free(e->center);
    freeHitbox(e->hit);
    freeWeapon(e->w);
    free(e);
}

void freeWeapon(Weapon *w){
    free(w->name);
    freeHitbox(w->hit);
    free(w);
}

void freeMissile(missile *m)
{
    free(m->center);
    freeHitbox(m->hit);
    free(m);
}

void freeData(Data *d)
{

    int i;
    for (i = 0; i < MAX_SIZE_TAB_MISSILE_P; i++)
    {
        if (d->tabMPlayer[i] != NULL)
        {
            freeMissile(d->tabMPlayer[i]);
        }
    }
    for (i = 0; i < MAX_SIZE_TAB_MISSILE_E; i++)
    {
        if (d->tabMEnemie[i] != NULL)
        {
            freeMissile(d->tabMEnemie[i]);
        }
    }
    for (i = 0; i < MAX_SIZE_TAB_ENEMIE; i++)
    {
        if (d->tabEnemie[i] != NULL)
        {
            freeEnemie(d->tabEnemie[i]);
        }
    }
    free(d->tabEnemie);
    free(d->tabMEnemie);
    free(d->tabMPlayer);
    freePlayer(d->p);

    free(d);
}

void free_Table_Enemie_File(Ennemi **tabE)
{
    int i;
    for (i = 0; i < MAX_SIZE_TAB_ENEMIE_FILE; i++)
    {
        if (tabE[i] != NULL)
        {
            freeEnemie(tabE[i]);
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

//changer la position des missiles du joueur ou Ennemi 
missile **changeMissilesPosition(missile **tabM,int width, int height)
{
    int i;
    missile *m;
    for (i = 0; i < MAX_SIZE_TAB_MISSILE_P; i++)
    {
        m = tabM[i];
        if (m != NULL)
        {
            m->center->x += cos(m->rad) * m->speed;
            m->center->y += sin(m->rad) * m->speed;
            /*  
                si jamais le changement de position rend le mission en dehors de la zone de la fenetre,
                alors on free la memoire du missile et on rend sa valeur a NULL dans le tableau.
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

void colisionMissPlayerEnemie(Data *data)
{
    int i, k;
    for (i = 0; i < MAX_SIZE_TAB_ENEMIE; i++)
    {
        for (k = 0; k < MAX_SIZE_TAB_MISSILE_P; k++)
        {
            if (data->tabEnemie[i] != NULL && data->tabMPlayer[k] != NULL)
            {
                if (isEnemieTouch(data->tabEnemie[i], data->tabMPlayer[k]))
                {
                    if (downEnemieLife(&(data->tabEnemie[i]), data->tabMPlayer[k]->degat))
                    {
                        killEnemie(&(data->tabEnemie), i);
                    }
                    freeMissile(data->tabMPlayer[k]);
                    data->tabMPlayer[k] = NULL;
                }
            }
        }
    }
}

void colisionMissEnemiePlayer(Data *data, int *lose)
{
    int k;
    for (k = 0; k < MAX_SIZE_TAB_MISSILE_E; k++)
    {
        if (data->tabMEnemie[k] != NULL)
        {
            if (isPlayerTouch(data->p, data->tabMEnemie[k]))
            {
                if (downPlayerLife(&(data->p), data->tabMEnemie[k]->degat))
                {
                    *lose = 1;
                }
                freeMissile(data->tabMEnemie[k]);
                data->tabMEnemie[k] = NULL;
            }
        }
    }
}

void changeEnemiesPosition(Ennemi ***tabE, int width, int height)
{
    int i;
    Ennemi *e;
    for (i = 0; i < MAX_SIZE_TAB_ENEMIE; i++)
    {
        e = (*tabE)[i];
        if (e != NULL)
        {
            e->center->x += cos(ENEMIE_RAD) * e->speed;
            e->center->y += sin(ENEMIE_RAD) * e->speed;
            /*  
                si jamais le changement de position rend le mission en dehors de la zone de la fenetre,
                alors on free la memoire du missile et on rend sa valeur a NULL dans le tableau.
            */
            if ((e->center->x < 0 || e->center->x > width) || (e->center->y < 0 || e->center->y > height))
            {
                freeEnemie(e);
                (*tabE)[i] = NULL;
            }
        }
    }
}

player *changePositionPlayer(player *p, int width, int height)
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

/* ajout dans les tableaux (missile, Ennemi etc..)*/

void addMissilePlayer(missile ***tabM, player *p, int speed)
{


    int i;
    for (i = 0; i < MAX_SIZE_TAB_MISSILE_P; i++)
    {
        if ((*tabM)[i] == NULL)
        {
            missile *m = creatMissile(MLV_COLOR_SKY_BLUE, p->w->degat, p->center,p->w->hit->width,p->w->hit->height, p->w->speed, PLAYER_RAD);
            (*tabM)[i] = m;
            return;
        }
    }
}

/* ajout dans les tableaux (missile, Ennemi etc..)*/

void addMissileEnemie(missile ***tabM, Ennemi *e, player *p, int speed)
{

    double sous1 = p->center->x - e->center->x;
    double sous2 = p->center->y - e->center->y;

    /*missile sur la traj du joueur*/
    double angle = atan((sous2) / (sous1));
    if (sous1 < 0)
    {
        angle = angle + M_PI;
    }

    int i;
    for (i = 0; i < MAX_SIZE_TAB_MISSILE_P; i++)
    {
        if ((*tabM)[i] == NULL)
        {
            missile *m = creatMissile(MLV_COLOR_RED, e->w->degat, e->center, e->w->hit->width,e->w->hit->height, e->w->speed, angle);
            (*tabM)[i] = m;
            return;
        }
    }
}

int table_Enemie_Empty(Ennemi **tabE)
{
    int i;
    Ennemi *e;
    for (i = 0; i < MAX_SIZE_TAB_ENEMIE; i++)
    {
        e = tabE[i];
        if (e != NULL)
        {
            return 0;
        }
    }
    return 1;
}

void fireEnemieWithTime(Ennemi ***tabE, missile ***tabM,player *p,int time)
{
    int i;
    Ennemi *e;
    for (i = 0; i < MAX_SIZE_TAB_ENEMIE; i++)
    {
        e = (*tabE)[i];
        if (e != NULL)
        {
            if (time % e->w->reload == 0)
            {
                e->w->reload = rand() % e->w->reload_init + (e->w->reload_init - e->w->reload_init / 2);
                addMissileEnemie(tabM, e, p,e->w->speed);
            }
        }
    }
}

Ennemi *findEnemieInTableByName(char *name, Ennemi **table, int size_table)
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

void addEnemieINTable(Ennemi *e, Ennemi ***tabE)
{

    int i;
    Ennemi *enemieTable;
    for (i = 0; i < MAX_SIZE_TAB_ENEMIE; i++)
    {
        enemieTable = (*tabE)[i];
        if (enemieTable == NULL)
        {
            //e = creatEnemie("tutu", 2, (50 + i * 50) % 1920, 50, 25, 25, 15, MLV_COLOR_BROWN4);
            (*tabE)[i] = e;
            return;
        }
    }
}

int isEnemieTouch(Ennemi *e, missile *m)
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

int isPlayerTouch(player *p, missile *m)
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
int downPlayerLife(player **p, int degat)
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
int downEnemieLife(Ennemi **e, int degat)
{
    (*e)->pv -= degat;
    if ((*e)->pv <= 0)
    {
        return 1;
    }
    return 0;
}

void killEnemie(Ennemi ***tab, int index)
{
    if ((*tab)[index]->pv <= 0)
    {
        freeEnemie((*tab)[index]);
        (*tab)[index] = NULL;
    }
}

//on assume que tabEnemies est vide car il s'agit de l'initialisation
int CreatTableOfEnemies(char *fileString, Ennemi ***tabEnemies, Weapon **tabWeapon)
{
    int pv, center_x, center_y, width, lenght, speed;
    char *name = (char *)malloc((MAX_CHAR_NAME + 1) * sizeof(name));
    MLV_Color color;
    char weapon[25];
    int index = 0;

    FILE *file = fopen(fileString, "r");
    if (file == NULL)
    {
        printf("Error File %s not found \n", fileString);
        return -1;
    }
    char l[500];
    char scolor[60];
    int ret;
    while (fgets(l, sizeof(l), file) != NULL)
    {
        if (l[0] != '#')
        {
            ret = sscanf(l, "%s %d %d %d %d %d %d %s %s", name, &pv, &center_x, &center_y, &width, &lenght, &speed, scolor,weapon);
            if (ret != -1)
            {
                /*
                printf("name: %s, pv: %d, center_x: %d, center_y: %d, width: %d, lenght: %d, speed: %d, color: %s \n \n", name, pv, center_x, center_y, width, lenght, speed, scolor);
                */
                color = MLV_convert_string_to_color(scolor);
                Weapon * w = findWeaponInTableByName(weapon,tabWeapon,MAX_SIZE_TAB_WEAPON_FILE);
                (*tabEnemies)[index] = creatEnemie(name, pv, center_x, center_y, width, lenght, speed, color,w);
                index++;
            }
        }
    }
    fclose(file);
    return 0;
}


//on assume que tabEnemies est vide car il s'agit de l'initialisation
int CreatTableOfWeapon(char *fileString, Weapon ***tabWeapon)
{
    int width, lenght, speed,degat,reload;
    char *name = (char *)malloc((MAX_CHAR_NAME + 1) * sizeof(name));
    //MLV_Color color;

    int index = 0;

    FILE *file = fopen(fileString, "r");
    if (file == NULL)
    {
        printf("Error File %s not found \n", fileString);
        return -1;
    }
    char l[500];
    int ret;
    while (fgets(l, sizeof(l), file) != NULL)
    {
        if (l[0] != '#')
        {
            ret = sscanf(l, "%s %d %d %d %d %d", name, &width, &lenght, &speed,&degat,&reload);
            if (ret != -1)
            {
                /*
                printf("name: %s, pv: %d, center_x: %d, center_y: %d, width: %d, lenght: %d, speed: %d, color: %s \n \n", name, pv, center_x, center_y, width, lenght, speed, scolor);
                */
                (*tabWeapon)[index] = creatWeapon(name, width, lenght, speed,degat,reload);
                index++;
            }
        }
    }
    fclose(file);
    return 0;
}
