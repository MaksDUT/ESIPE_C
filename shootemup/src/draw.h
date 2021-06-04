#ifndef __DRAW__
#define __DRAW__

#include "shootemup.h"

/**
 * @brief draw Player
 * 
 * @param p 
 */
void drawPlayer(Player *p);
/**
 * @brief draw one Ennemi
 * 
 * @param e 
 */
void drawEnnemi(Ennemi *e);

/**
 * @brief draw all the Missile from array
 * 
 * @param tabM 
 * @param size 
 */
void drawAllMissile(Missile **tabM, int size);

/**
 * @brief draw one Missile
 * 
 * @param m 
 */
void drawMissile(Missile *m);
/**
 * @brief draw All Ennemis 
 * 
 * @param tabE 
 */
void drawAllEnnemis(Ennemi **tabE);
/**
 * @brief draw Player life
 * 
 * @param pv_Player 
 * @param width 
 * @param height 
 */
void draw_Player_Life(int pv_Player, int width, int height);


#endif