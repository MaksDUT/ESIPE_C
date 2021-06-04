#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>

#include <math.h>
#include <time.h>
#include "shootemup.h"
#include "draw.h"
#include "background.h"

void menu_pause(int *quit, double width, double height);
void game();

int main(int argc, char *argv[])
{
    game();
    return 0;
}
void menu_pause(int *quit, double width, double height)
{
    MLV_change_default_font("./../font/PressStart2P.ttf",40);
    MLV_draw_text(
        width * 0.40, height * 0.40,
        "Pause",
        MLV_COLOR_RED);

    MLV_change_default_font("./../font/PressStart2P.ttf", 25);
    MLV_draw_text(
        width * 0.12, height * 0.5,
        "| Q quit the programme | ESC stop the pause",
        MLV_COLOR_RED);

    MLV_update_window();

    MLV_Keyboard_button key_button;
    MLV_Button_state state;

    while (1)
    {
        MLV_wait_event(&key_button, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
        if (key_button == MLV_KEYBOARD_q && state == MLV_PRESSED)
        {
            *quit = 1;
            return;
        }
        if (key_button == MLV_KEYBOARD_ESCAPE && state == MLV_PRESSED)
        {
            return;
        }
    }
}

void game()
{
    /*
        Décalaration des variables qui contiendront les positions
        de la souris.
    */
    
    //double width = MLV_get_desktop_width()*RATIO_SCREEN;
    //double height = MLV_get_desktop_height()*RATIO_SCREEN;
    double width = 1600;
    double height = 900;

    /*Var game */
    int quit = 0;
    int lose = 0;
    int win = 0;
    /*Time / Frame*/
    int frame = 0;

    /*event struc*/
    MLV_Event event = MLV_NONE;
    MLV_Keyboard_button key_button;
    MLV_Button_state state;

    /*
    * Game data Creation  
    */
    Data *data = creatData();

    /*cahnge position player*/
    data->p->center->x=width/2;
    data->p->center->y=height - height/5;

    /*Creation des weapon*/
    Weapon ** tabWeapon =create_Table_Weapon_File("weapon.txt");
    /*Creation des ennemis*/
    Ennemi ** tabEnemies =create_Table_Enemie_File("enemies.txt",tabWeapon);

    /*changment d'Ennemi*/
    int monster = 0;
    /*
    Init background 
    */
    Stars *background = create_stars(width);

    /*
    Créé et affiche la fenêtre
    */
    MLV_create_window("Test ", "test", width, height);
    MLV_change_frame_rate(60);
    
    int waves = 0;
    do
    {
        
        if(frame>300){

            //generateur de niveau 
            if (waves < WAVES)
            {
                if (frame % (60 * 5) == 0)
                {
                    Ennemi *e = tabEnemies[monster];
                    int numbers = width / e->hit->width;
                    int first_position = e->hit->width/2 +20;
                    int j;
                    Ennemi *tmp;
                    for (j = 0; j < numbers; j++)
                    {
                        tmp = copyEnemie(e);
                        tmp->center->x = first_position + (j * (e->hit->width * 2));
                        tmp->center->y = tmp->hit->height / 2;
                        addEnemieINTable(tmp, &data->tabEnemie);
                    }
                    monster = (monster + 1) % 4;
                    waves++;
                }
            }else
            {
                if (table_Enemie_Empty(data->tabEnemie))
                {
                    win = 1;
                }
            }
        }

        //background set
        active_stars(background);
        change_stars(background, height);

        //Capture des événements
        while ((event = MLV_get_event(&key_button, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state)) != MLV_NONE)
        {
            //event = MLV_get_event(&key_button, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
            if (key_button == MLV_KEYBOARD_ESCAPE && state == MLV_PRESSED)
            {
                menu_pause(&quit, width, height);
                //quit = 1;
            }
        }

        if(frame%5==0){

            addMissilePlayer(&(data->tabMPlayer), data->p, PLAYER_M_SPEED);
        }
        fireEnemieWithTime(&(data->tabEnemie), &(data->tabMEnemie),data->p,frame);
        //On fait changer de position cahque element de l'ecran
        /* missiles*/
        changeEnemiesPosition(&data->tabEnemie, width, height);
        data->tabMPlayer = changeMissilesPosition(data->tabMPlayer,width, height);
        data->tabMEnemie = changeMissilesPosition(data->tabMEnemie,width, height);
        /*Joueur*/
        data->p = changePositionPlayer(data->p, width, height);

        //On test les colisions
        colisionMissPlayerEnemie(data);
        colisionMissEnemiePlayer(data, &lose);

        /*Affichage */
        MLV_clear_window(MLV_COLOR_BLACK);
        print_stars(background);
        drawPlayer(data->p);

        //Draw missile player and ennemi
        drawAllMissile(data->tabMPlayer,MAX_SIZE_TAB_MISSILE_P);
        drawAllMissile(data->tabMEnemie,MAX_SIZE_TAB_MISSILE_E);
        
        //draw Ennemie
        drawAllEnnemis(data->tabEnemie);
        /*pv player draw*/
        draw_Player_Life(data->p->pv,width,height);

        //on actualise la fenetre
        MLV_actualise_window();
        MLV_delay_according_to_frame_rate();
        frame++;
    } while (!quit && !lose && !win);




    char textFinal[20];

    if (lose)
    {
        strcpy(textFinal, "Perdu");
    }
    else if (win)
    {
        strcpy(textFinal, "Gagné");
    }
    MLV_change_default_font("./../font/PressStart2P.ttf", 40);
    MLV_draw_text(
        width * 0.42, height * 0.37,
        textFinal,
        MLV_COLOR_RED);

    MLV_change_default_font("./../font/PressStart2P.ttf", 30);
    MLV_draw_text(
        width * 0.30, height * 0.5,
        "Le jeu va se fermer",
        MLV_COLOR_RED);

    MLV_actualise_window();
    MLV_wait_seconds(5);
    /*
        Fermer la fenêtre
    */

    MLV_free_window();
    /* FREE TIME */
    freeData(data);
    free_Table_Enemie_File(tabEnemies);
}
