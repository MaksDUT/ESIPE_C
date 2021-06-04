#ifndef __DRAW__
#define __DRAW__

#include "shootemup.h"

void drawPlayer(player *p);
void drawEnnemi(Ennemi *e);
void drawAllMissile(missile **tabM, int size);

void drawAllMissileEnemie(missile **tabM);
void drawMissile(missile *m);
void drawAllEnnemis(Ennemi **tabE);

void draw_Player_Life(int pv_player, int width, int height);


#endif