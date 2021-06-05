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
    MLV_change_default_font("./../font/PressStart2P.ttf", 40);
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
    int frame_rate = 60;

    /*event struc*/
    MLV_Event event = MLV_NONE;
    MLV_Keyboard_button key_button;
    MLV_Button_state state;

    /*
    * Game data Creation  
    */
    Data *data = creatData();

    /*cahnge position Player*/
    data->p->center->x = width / 2;
    data->p->center->y = height - height / 5;

    /*Creation des weapon*/
    Weapon **tabWeapon = create_Table_Weapon_File("weapon.txt");
    /*Creation des ennemis*/
    Ennemi **tabEnnemis = create_Table_Ennemi_File("Ennemis.txt", tabWeapon);
    int numbers_ennemis = get_numbers_ennemi(tabEnnemis);

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
    MLV_change_frame_rate(frame_rate);

    int waves = 0;
    do
    {
        //tempo pour que le joueur ne sois pas surpris 
        if (frame > frame_rate*3)
        {
            //generateur de niveau
            if (waves < WAVES)
            {
                if (frame % (60 * 5) == 0)
                {
                    Ennemi *e = tabEnnemis[monster];
                    int numbers = width / e->hit->width;
                    int first_position = e->hit->width / 2 + 20;
                    int j;
                    Ennemi *tmp;
                    for (j = 0; j < numbers; j++)
                    {
                        tmp = copyEnnemi(e);
                        tmp->center->x = first_position + (j * (e->hit->width * 2));
                        tmp->center->y = tmp->hit->height / 2;
                        addEnnemiINTable(tmp, &data->tabEnnemi);
                    }
                    monster = (monster + 1) % numbers_ennemis;
                    waves++;
                }
            }
            else
            {
                if (is_Table_Ennemi_Empty(data->tabEnnemi))
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

        if (frame % 5 == 0)
        {

            addMissilePlayer(&(data->tabMPlayer), data->p);
        }
        fireEnnemiWithTime(&(data->tabEnnemi), &(data->tabMEnnemi), data->p, frame);
        //On fait changer de position cahque element de l'ecran
        /* Missiles*/
        changeEnnemisPosition(&data->tabEnnemi, width, height);
        data->tabMPlayer = changeMissilesPosition(data->tabMPlayer, width, height);
        data->tabMEnnemi = changeMissilesPosition(data->tabMEnnemi, width, height);
        /*Joueur*/
        data->p = changePositionPlayer(data->p, width, height);

        //On test les colisions
        colisionMissPlayerEnnemi(data);

        colisionMissEnnemiPlayer(data, &lose);

        /*Affichage */
        MLV_clear_window(MLV_COLOR_BLACK);
        print_stars(background);
        drawPlayer(data->p);

        //Draw Missile Player and ennemi
        drawAllMissile(data->tabMPlayer, MAX_SIZE_TAB_Missile_P);
        drawAllMissile(data->tabMEnnemi, MAX_SIZE_TAB_Missile_E);

        //draw Ennemie
        drawAllEnnemis(data->tabEnnemi);
        /*pv Player draw*/
        draw_Player_Life(data->p->pv, width, height);

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
    free_Table_Ennemi_File(tabEnnemis);
    free_Table_Weapon_File(tabWeapon);
}
