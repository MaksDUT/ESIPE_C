#include <MLV/MLV_all.h>
#include <math.h>

void print_grid(int width, int height, float ratio);
int minInt(int a, int b);
void search_case(int x, int y, int width, int height);

int main(int argc, char *argv[])
{
    /*
        Décalaration des variables qui contiendront les positions
        de la souris.
        */
    int x, y;
    int width = MLV_get_desktop_width() * 0.8;
    int height = MLV_get_desktop_height() * 0.8;

    MLV_Keyboard_button touche;
    /*
        Créé et affiche la fenêtre
        */
    MLV_create_window("Test ", "test", width, height);
    /*
        Affiche la consigne
        */
    do
    {
        MLV_draw_text(
            width * 0.05, 10,
            "Click on the window with the mouse to make a circle appear",
            MLV_COLOR_GREEN);
        MLV_draw_text(
            width * 0.05, height * 0.92,
            "to stop the program made the circle then press q or any other key to repeat a new test",
            MLV_COLOR_GREEN);

        print_grid(width, height, 0.8);

        MLV_actualise_window();
        /*
            Attendre que l'utilisateur clique sur le bouton gauche de la souris
            */
        MLV_wait_mouse(&x, &y);
        /*
            Dessine un cercle à la position du curseur de la souris
            */
        search_case(x, y, width, height);

        MLV_draw_circle(x, y, 30, MLV_COLOR_RED);
        MLV_actualise_window();

        MLV_wait_keyboard(&touche, NULL, NULL);

        MLV_draw_filled_rectangle(0, 0, width, height, MLV_COLOR_BLACK);
    } while (touche != MLV_KEYBOARD_q);
    MLV_draw_text(
        width * 0.05, height * 0.92,
        "la fenetre va se fermer dans 5s",
        MLV_COLOR_GREEN);
    MLV_actualise_window();
    MLV_wait_seconds(5);
    /*
        Fermer la fenêtre
        */
    MLV_free_window();
    return 0;
}

void print_grid(int width, int height, float ratio)
{

    int length = minInt(width, height);
    int gridLength = length * ratio;
    /*la partie manquante de width avec le ratio*/
    int value = (length - gridLength) / 2;
    int lengthCase = gridLength / 10;

    MLV_draw_filled_rectangle(value, value, gridLength, gridLength, MLV_COLOR_GRAY10);

    int i;
    for (i = 0; i <= 10; i++)
    {

        MLV_draw_line(value, value + (i * lengthCase), gridLength + value, i * lengthCase + value, MLV_COLOR_WHITE);
        MLV_draw_line(value + i * lengthCase, value, value + i * lengthCase, gridLength + value, MLV_COLOR_WHITE);
    }

    int j;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            char test[80];
            sprintf(test, "(%d,%d)", i, j);
            MLV_draw_text(value + (lengthCase * j) + ((lengthCase - 1) / 2), value + (lengthCase * i) + ((lengthCase - 1) / 2), test, MLV_COLOR_GREEN);
        }
    }
}

int minInt(int a, int b)
{
    int result = (a < b) ? a : b;
    return result;
}

void search_case(int x, int y, int width, int height)
{
    float ratio = 0.8;
    int length = minInt(width, height);
    int gridLength = length * ratio;
    /*la partie manquante de width avec le ratio*/
    int value = (length - gridLength) / 2;

    int startGridx = value;
    int startGridy = value;

    int endGridx = value + gridLength;
    int endGridy = value + gridLength;

    int diviseur;

    if (x >= startGridx && x <= endGridx)
    {
        x = x - value;
        endGridx = endGridx - value;
        diviseur = endGridx / 10;
        x = x / diviseur;

        if (y >= startGridy && y <= endGridy)
        {
            y = y - value;
            endGridy = endGridy - value;
            diviseur = endGridy / 10;
            y = y / diviseur;
        }
        char message[80];
        sprintf(message, "position case : i--> %d | j-->%d", y, x);
        MLV_draw_text(
            width * 0.6, height * 0.3,
            message,
            MLV_COLOR_GREEN);
    }
    else
    {

        char message[80];
        sprintf(message, "erreur");
        MLV_draw_text(
            width * 0.6, height * 0.3,
            message,
            MLV_COLOR_GREEN);
    }
}