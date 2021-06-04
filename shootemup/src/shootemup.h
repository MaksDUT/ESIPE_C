#ifndef __SHOOTEMUP__
#define __SHOOTEMUP__

typedef struct
{
    int x;
    int y;
} Pixel;

typedef struct
{
    int width;
    int height;

} Hitbox;

typedef struct
{
    char *name;
    Hitbox *hit;
    int speed;
    int degat;
    int reload_init;
    int reload;
} Weapon;

typedef struct
{
    int pv;
    Hitbox *hit;
    Pixel *center;
    Weapon *w;
    int speed;
    MLV_Color color;

} Player;

typedef struct
{
    char *name;
    int pv;
    Hitbox *hit;
    Pixel *center;
    Weapon *w;
    int speed;
    MLV_Color color;
} Ennemi;

typedef struct
{
    MLV_Color color;
    int degat;
    Pixel *center;
    Hitbox *hit;
    int speed;
    double rad;
} Missile;

typedef struct
{
    Player *p;
    int vitesse;
    Missile **tabMPlayer;
    Missile **tabMEnnemi;
    Ennemi **tabEnnemi;
    //bonus;
} Data;

/*Creation */

/**
 *  
 * 
 * @param x 
 * @param y 
 * @return Pixel* 
 */

Pixel *creatPixel(int x, int y);
/**
 * 
 * 
 * @param w 
 * @param h 
 * @return Hitbox* 
 */
Hitbox *creatHitbox(int w, int h);
/**
 * 
 * 
 * @param name 
 * @param width 
 * @param lenght 
 * @param speed 
 * @param degat 
 * @param reload 
 * @return Weapon* 
 */
Weapon *creatWeapon(char *name, int width, int lenght, int speed, int degat, int reload);

/**
 * @brief 
 * 
 * @param pv 
 * @param centerX 
 * @param centerY 
 * @param width 
 * @param lenght 
 * @param speed 
 * @param color 
 * @return Player* 
 */
Player *creatPlayer(int pv, int centerX, int centerY, int width, int lenght, int speed, MLV_Color color);
/**
 * @brief 
 * 
 * @param name 
 * @param pv 
 * @param centerX 
 * @param centerY 
 * @param width 
 * @param lenght 
 * @param speed 
 * @param color 
 * @param w 
 * @return Ennemi* 
 */
Ennemi *creatEnnemi(char *name, int pv, int centerX, int centerY, int width, int lenght, int speed, MLV_Color color, Weapon *w);
/**
 * @brief 
 * 
 * @param color 
 * @param degat 
 * @param center 
 * @param width 
 * @param lenght 
 * @param speed 
 * @param rad 
 * @return Missile* 
 */
Missile *creatMissile(MLV_Color color, int degat, Pixel *center, int width, int lenght, int speed, double rad);
/**
 * @brief 
 * 
 * @return Data* 
 */
Data *creatData();


/*Copy*/

/**
 * @brief Copy an object Ennemi
 * 
 * @param e 
 * @return Ennemi* 
 */
Ennemi *copyEnnemi(Ennemi *e);
/**
 * @brief 
 * 
 * @param w 
 * @return Weapon* 
 */
Weapon *copyWeapon(Weapon *w);

/*Free*/
/**
 * @brief free the object Hitbox h
 * 
 * @param h 
 */
void freeHitbox(Hitbox *h);
/**
 * @brief free the object Player p
 * 
 * @param p 
 */
void freePlayer(Player *p);
/**
 * @brief free the object Weapon w
 * 
 * @param w 
 */
void freeWeapon(Weapon *w);
/**
 * @brief free the object Missile m
 * 
 * @param m 
 */
void freeMissile(Missile *m);
/**
 * @brief free the object Data d
 * 
 * @param d 
 */
void freeData(Data *d);
/**
 * @brief free the table of ennemis in the file setting 
 * 
 * @param tabE 
 */
void free_Table_Ennemi_File(Ennemi **tabE);

/**
 * @brief change the position of all the missile on the table tabM
 * 
 * @param tabM 
 * @param width 
 * @param height 
 * @return Missile** 
 */
Missile **changeMissilesPosition(Missile **tabM, int width, int height);

/**
 * @brief check colision between Ennemi and Missile of the player. \n 
 * if they are a colision, the Ennemi will lose pv from the domage of the Missile.
 * 
 * @param data 
 */
void colisionMissPlayerEnnemi(Data *data);
/**
 * @brief check colision between Player and Missile of the Ennemis. \n 
 * If they are a colision, the PLayer will lose pv from the domage of the Missile.
 * If player life < 0 lose return 1  
 * 
 * @param data 
 * @param lose 
 */
void colisionMissEnnemiPlayer(Data *data, int *lose);

/**
 * @brief change the position of the Player
 * 
 * @param p 
 * @param width 
 * @param height 
 * @return Player* 
 */
Player *changePositionPlayer(Player *p, int width, int height);

/**
 * @brief change the position of all the Ennemis int the array
 * 
 * @param tabE 
 * @param width 
 * @param height 
 */
void changeEnnemisPosition(Ennemi ***tabE, int width, int height);

/**
 * @brief add a Missile from the Player into the array of MissilePlayer.
 * 
 * @param tabM 
 * @param p  
 */
void addMissilePlayer(Missile ***tabM, Player *p);
/**
 * @brief add a Missile form an Ennemi into the array of MissileEnnemi.
 * 
 * @param tabM 
 * @param e 
 * @param p 
 */
void addMissileEnnemi(Missile ***tabM, Ennemi *e, Player *p);

/**
 * @brief return if the array of ennemi is empty or not. 
 * 
 * @param tabE 
 * @return int 
 */
int is_Table_Ennemi_Empty(Ennemi **tabE);

/**
 * @brief randomize the fire rate of the Ennemi
 * 
 * @param tabE 
 * @param tabM 
 * @param p 
 * @param time 
 */
void fireEnnemiWithTime(Ennemi ***tabE, Missile ***tabM, Player *p, int time);

/**
 * @brief get an Ennemi from the array by is name
 * 
 * @param name 
 * @param table 
 * @param size_table 
 * @return Ennemi* 
 */
Ennemi *findEnnemiInTableByName(char *name, Ennemi **table, int size_table);

/**
 * @brief add an Ennemi in the array of Ennemi (Ennemi in the current game)
 * 
 * @param e 
 * @param tabE 
 */
void addEnnemiINTable(Ennemi *e, Ennemi ***tabE);

/**
 * @brief check if the hitbox of the missile cross the hitbox of the Ennemi
 * 
 * @param e 
 * @param m 
 * @return int 
 */
int isEnnemiTouch(Ennemi *e, Missile *m);

/**
 * @brief check if the hitbox of the missile cross the hitbox of Player
 * 
 * @param p 
 * @param m 
 * @return int 
 */
int isPlayerTouch(Player *p, Missile *m);

/**
 * @brief reduce the pv of the Player with the value degat
 * 
 * @param p 
 * @param degat 
 * @return int 
 */
int downPlayerLife(Player **p, int degat);

/**
 * @brief reduce the pv of the Ennemi whith the value degat
 * 
 * @param e 
 * @param degat 
 * @return int 
 */
int downEnnemiLife(Ennemi **e, int degat);

/**
 * @brief kill the Ennemi. in fact remove the Ennemi from the array and free it
 * 
 * @param tab 
 * @param index 
 */
void killEnnemi(Ennemi ***tab, int index);

//creer une table d'Ennemi charger depuis un fichier

/**
 * @brief Create a Table Ennemi File object
 * 
 * @param file 
 * @param tabWeapon 
 * @return Ennemi** 
 */
Ennemi **create_Table_Ennemi_File(char *file, Weapon **tabWeapon);
/**
 * @brief Create a Table Weapon File object
 * 
 * @param file 
 * @return Weapon** 
 */
Weapon **create_Table_Weapon_File(char *file);

//Global variable Game
#define RATIO_SCREEN 0.8
//number of wave of Ennemi
#define WAVES 4

//Global variable for DATA structure

//Player INIT
#define Player_RAD -(M_PI / 2)
#define Player_PV 5
#define Player_CENTER_X 800
#define Player_CENTER_Y 200
#define Player_CENTER_WIDTH 75
#define Player_CENTER_LENGHT 20
#define Player_SPEED 15
#define Player_COLOR MLV_COLOR_RED
//Ennemi INIT
#define MAX_CHAR_NAME 25
#define MAX_DIFERENT_Ennemi 10
#define Ennemi_RAD (M_PI / 2)
#define Ennemi_M_SPEED 20

//max size for Missile's table (Player and Ennemi)
#define MAX_SIZE_TAB_Missile_P 80
#define MAX_SIZE_TAB_Missile_E 500
//max size for Ennemi's table
#define MAX_SIZE_TAB_Ennemi 50
#define MAX_SIZE_TAB_Ennemi_FILE 20

#define MAX_SIZE_TAB_WEAPON_FILE 20

#endif