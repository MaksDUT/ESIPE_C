#ifndef __SHOOTEMUP__
#define __SHOOTEMUP__
/*
enum weapon
{
    cannon = 300,
    basic = 150,
    laser = 1
};
*/

typedef struct
{
    int x;
    int y;
} pixel;

typedef struct
{
    int width;
    int height;

} hitbox;

typedef struct
{
    char *name;
    hitbox *hit;
    int speed;
    int degat;
    int reload_init;
    int reload;
} Weapon;

typedef struct
{
    int pv;
    hitbox *hit;
    pixel *center;
    Weapon *w;
    int speed;
    MLV_Color color;

} player;

typedef struct
{
    char *name;
    int pv;
    hitbox *hit;
    pixel *center;
    Weapon *w;
    int speed;
    MLV_Color color;
} Ennemi;

typedef struct
{
    MLV_Color color;
    int degat;
    pixel *center;
    hitbox *hit;
    int speed;
    double rad;
} missile;

typedef struct
{
    player *p;
    int vitesse;
    missile **tabMPlayer;
    missile **tabMEnemie;
    Ennemi **tabEnemie;
    //bonus;
} Data;

/*Creation */
pixel *creatPixel(int x, int y);
hitbox *creatHitbox(int w, int h);
Weapon *creatWeapon(char *name, int width, int lenght, int speed, int degat, int reload);

player *creatPlayer(int pv, int centerX, int centerY, int width, int lenght, int speed, MLV_Color color);
Ennemi *creatEnemie(char *name, int pv, int centerX, int centerY, int width, int lenght, int speed, MLV_Color color, Weapon *w);
missile *creatMissile(MLV_Color color, int degat, pixel *center, int width, int lenght, int speed, double rad);
Data *creatData();

Ennemi **create_Table_Enemie_File(char *file, Weapon **tabWeapon);
Weapon **create_Table_Weapon_File(char *file);

/*Copy*/
Ennemi *copyEnemie(Ennemi *e);
Weapon *copyWeapon(Weapon *w);

/*Free*/
void freeHitbox(hitbox *h);
void freePlayer(player *p);
void freeWeapon(Weapon *w);
void freeMissile(missile *m);
void freeData(Data *d);
void free_Table_Enemie_File(Ennemi **tabE);

missile **changeMissilesPosition(missile **tabM, int width, int height);

void colisionMissPlayerEnemie(Data *data);
void colisionMissEnemiePlayer(Data *data, int *lose);

player *changePositionPlayer(player *p, int width, int height);
void changeEnemiesPosition(Ennemi ***tabE, int width, int height);

void addMissilePlayer(missile ***tabM, player *p, int speed);
void addMissileEnemie(missile ***tabM, Ennemi *e, player *p, int speed);

int table_Enemie_Empty(Ennemi **tabE);

void fireEnemieWithTime(Ennemi ***tabE, missile ***tabM, player *p, int time);

Ennemi *findEnemieInTableByName(char *name, Ennemi **table, int size_table);
void addEnemieINTable(Ennemi *e, Ennemi ***tabE);

int isEnemieTouch(Ennemi *e, missile *m);
int isPlayerTouch(player *p, missile *m);

int downPlayerLife(player **p, int degat);
int downEnemieLife(Ennemi **e, int degat);

void killEnemie(Ennemi ***tab, int index);

//creer une table d'Ennemi charger depuis un fichier
int CreatTableOfEnemies(char *fileString, Ennemi ***tabEnemies, Weapon **tabWeapon);
int CreatTableOfWeapon(char *fileString, Weapon ***tabWeapon);

//Global variable Game
#define RATIO_SCREEN 0.8
//number of wave of Ennemi
#define WAVES 4

//Global variable for DATA structure

//Player INIT
#define PLAYER_RAD -(M_PI / 2)
#define PLAYER_PV 5
#define PLAYER_CENTER_X 800
#define PLAYER_CENTER_Y 200
#define PLAYER_CENTER_WIDTH 75
#define PLAYER_CENTER_LENGHT 20
#define PLAYER_SPEED 15
#define PLAYER_COLOR MLV_COLOR_RED
#define PLAYER_M_SPEED 15
//Ennemi INIT
#define MAX_CHAR_NAME 25
#define MAX_DIFERENT_ENEMIE 10
#define ENEMIE_RAD (M_PI / 2)
#define ENEMIE_M_SPEED 20

//max size for missile's table (Player and Ennemi)
#define MAX_SIZE_TAB_MISSILE_P 80
#define MAX_SIZE_TAB_MISSILE_E 500
//max size for Ennemi's table
#define MAX_SIZE_TAB_ENEMIE 50
#define MAX_SIZE_TAB_ENEMIE_FILE 20

#define MAX_SIZE_TAB_WEAPON_FILE 20

#endif