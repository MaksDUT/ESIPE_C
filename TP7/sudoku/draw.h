#ifndef __DRAW__
#define __DRAW__

#include "sudoku.h"

#define BACKGROUND_C_GRID MLV_rgba(81, 46, 95, 255)


typedef struct
{
    int i;
    int j;
} Couple;

void print_grid(Board grid, int width, int height, float ratio, Couple tab[], int count);
int minInt(int a, int b);
void search_case_grid(int x_pixel, int y_pixel, int width, int height, float ratio, int *i, int *j);
void print_grid_value(int width, int height, float ratio);
int search_case_value(int x_pixel, int y_pixel, int width, int height);
int isACaseTrue(int i, int j);
int find_first_couple(Board grid, Couple **tab);
int is_couple(Couple tab[], int i, int j, int count);

#endif