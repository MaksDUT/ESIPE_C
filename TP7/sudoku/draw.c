/*  For test
#include <stdio.h>  
*/ 
#include <MLV/MLV_all.h>

#include "draw.h"


/*Draw the grid with the value*/
void print_grid(Board grid, int width, int height, float ratio, Couple tab[], int count)
{

    int length = minInt(width, height);
    int gridLength = (int)(length * ratio);
    /*la partie manquante de width avec le ratio*/
    int value = (int)((length - gridLength) / 2);
    int lengthCase = (int)(gridLength / 9);

    MLV_draw_filled_rectangle(value, value, lengthCase * 9, lengthCase * 9, BACKGROUND_C_GRID);

    int i;
    int linebiger = 0;
    MLV_Color color;
    color = MLV_COLOR_WHITE;

    for (i = 0; i <= 9; i++)
    {
        linebiger = linebiger % 3;

        if (linebiger == 0)
        {
            MLV_draw_line(value, value + (i * lengthCase) - 1, (lengthCase * 9) + value, i * lengthCase + value - 1, color);
            MLV_draw_line(value, value + (i * lengthCase) + 1, (lengthCase * 9) + value, i * lengthCase + value + 1, color);
            MLV_draw_line(value + i * lengthCase - 1, value, value + i * lengthCase - 1, (lengthCase * 9) + value, color);
            MLV_draw_line(value + i * lengthCase + 1, value, value + i * lengthCase + 1, (lengthCase * 9) + value, color);
        }

        MLV_draw_line(value, value + (i * lengthCase), (lengthCase * 9) + value, i * lengthCase + value, color);
        MLV_draw_line(value + i * lengthCase, value, value + i * lengthCase, (lengthCase * 9) + value, color);
        linebiger++;
    }

    int j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            char test[80];
            if (grid[i][j] == 0)
            {
                sprintf(test, " ");
            }
            else
            {
                sprintf(test, "%d", grid[i][j]);
            }
            if (is_couple(tab, i, j, count))
            {
                MLV_draw_text(value + (lengthCase * j) + ((lengthCase - 1) / 2), value + (lengthCase * i) + ((lengthCase - 1) / 3), test, MLV_COLOR_GRAY);
            }
            else
            {
                MLV_draw_text(value + (lengthCase * j) + ((lengthCase - 1) / 2), value + (lengthCase * i) + ((lengthCase - 1) / 3), test, MLV_COLOR_GREEN);
            }
        }
    }
}
/*draw the numeric keypad */
void print_grid_value(int width, int height, float ratio)
{

    int length = minInt(width, height);
    int gridLength = (int)(length * ratio);
    /*la partie manquante de width avec le ratio*/
    int value = (int)(gridLength / 2);
    int lengthCase = (int)(gridLength / 3);

    int startx = width - gridLength - value;
    int starty = height - gridLength - value;

    MLV_draw_filled_rectangle(startx, starty, gridLength, gridLength, BACKGROUND_C_GRID);

    int i;
    for (i = 0; i <= 3; i++)
    {
        MLV_draw_line(startx, starty + (i * lengthCase), startx + gridLength, i * lengthCase + starty, MLV_COLOR_WHITE);
        MLV_draw_line(startx + i * lengthCase, starty, startx + i * lengthCase, starty + gridLength, MLV_COLOR_WHITE);
    }
    int j;
    int compteur = 1;
    /*draw the text value in eache case*/
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            char test[12];
            sprintf(test, "%d", compteur);
            compteur++;
            MLV_draw_text(startx + (lengthCase * j) + ((lengthCase - 1) / 2), starty + (lengthCase * i) + ((lengthCase - 1) / 3), test, MLV_COLOR_WHITE);
        }
    }

    /*case 0*/
    char test[80];
    sprintf(test, "Suppr");
    /*draw the outline of the case 0*/
    MLV_draw_filled_rectangle(startx - 1, height - value + 5, minInt(width, height) * 0.333, minInt(width, height) * 0.1, MLV_COLOR_WHITE);
    /*draw the case 0*/
    MLV_draw_filled_rectangle(startx, height - value + 6, -2 + minInt(width, height) * 0.333, -2 + minInt(width, height) * 0.1, BACKGROUND_C_GRID);
    /*draw the text value of the case 0*/
    MLV_draw_text(startx + (-2 + minInt(width, height) * 0.333) / 2.3, height - value + 6 + (-2 + minInt(width, height) * 0.1) / 3, test, MLV_COLOR_WHITE);
}

int minInt(int a, int b)
{
    int result = (a < b) ? a : b;
    return result;
}
/*If the click is in the grid find the coordinates of the cell (i,j) if not return -1,-1 in i,j*/
void search_case_grid(int x_pixel, int y_pixel, int width, int height, float ratio, int *i, int *j)
{
    int length = minInt(width, height);
    int gridLength = (int)(length * ratio);
    /*la partie manquante de width avec le ratio*/
    int value = (int)((length - gridLength) / 2);
    int lengthCase = (int)(gridLength / 9);

    int startGridx = value;
    int startGridy = value;

    int endGridy = value + (lengthCase * 9);
    int endGridx = value + (lengthCase * 9);

    int diviseur;

    if (x_pixel >= startGridx && x_pixel <= endGridx)
    {
        x_pixel = x_pixel - value;
        endGridx = endGridx - value;
        diviseur = endGridx / 9;
        x_pixel = x_pixel / diviseur;

        if (y_pixel >= startGridy && y_pixel <= endGridy)
        {
            y_pixel = y_pixel - value;
            endGridy = endGridy - value;
            diviseur = endGridy / 9;
            y_pixel = y_pixel / diviseur;
            *i = y_pixel;
            *j = x_pixel;
        }
    }
    else
    {
        *i = -1;
        *j = -1;
    }
}
/*If the click is in the numeric keypad, return the value */
int search_case_value(int x_pixel, int y_pixel, int width, int height)
{

    float ratio = 0.33;
    int length = minInt(width, height);
    int gridLength = length * ratio;
    /*la partie manquante de width avec le ratio*/

    int value = gridLength / 2;
    int startGridx = width - gridLength - value;
    int startGridy = height - gridLength - value;

    int endGridx = startGridx + gridLength;
    int endGridy = startGridy + gridLength;

    int diviseur;

    if (x_pixel >= startGridx && x_pixel <= endGridx)
    {
        x_pixel = x_pixel - startGridx;
        endGridx = gridLength;
        diviseur = endGridx / 3;
        x_pixel = x_pixel / diviseur;

        if (y_pixel >= startGridy && y_pixel <= endGridy)
        {
            y_pixel = y_pixel - startGridy;
            endGridy = gridLength;
            diviseur = endGridy / 3;
            y_pixel = y_pixel / diviseur;

            int result = 3 * y_pixel + x_pixel + 1;
            return result;
        }
        else if (y_pixel >= endGridy + 5 && y_pixel <= endGridy + 5 + (length * 0.1))
        {
            return 0;
        }
    }
    return -1;
}

int isACaseTrue(int i, int j)
{
    if (i == -1 || j == -1)
        return 0;
    return 1;
}
/*find the case that already int the grid file*/
int find_first_couple(Board grid, Couple **tab)
{
    int i, j, count;
    count = 0;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (grid[i][j] != 0)
            {
                Couple c;
                c.i = i;
                c.j = j;
                (*tab)[count] = c;
                count++;
            }
        }
    }
    return count;
}
/*return true if the case(i,j) is in the table tab.*/
int is_couple(Couple tab[], int i, int j, int count)
{
    int x_pixel;
    Couple c;
    for (x_pixel = 0; x_pixel < count; x_pixel++)
    {
        c = tab[x_pixel];
        if (c.i == i && c.j == j)
            return 1;
    }
    return 0;
}
