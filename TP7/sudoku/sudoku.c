#include <stdio.h>

#include "sudoku.h"

void initialize_empty_board(Board grid)
{
    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void print_board(Board grid)
{
    int i, j;
    printf("\n-------------------------------------\n");
    for (i = 0; i < 9; i++)
    {
        printf("|");
        for (j = 0; j < 9; j++)
        {
            if (grid[i][j] == 0)
            {
                printf("   |");
            }
            else
            {
                printf(" %d |", grid[i][j]);
            }
        }
        j = 0;
        printf("\n-------------------------------------\n");
    }
}

int is_line_true(Board grid, int i, int valeur)
{
    int j;
    for (j = 0; j < 9; j++)
    {
        if (grid[i][j] == valeur)
            return 0;
    }
    return 1;
}

int is_row_true(Board grid, int j, int valeur)
{
    int i;
    for (i = 0; i < 9; i++)
    {
        if (grid[i][j] == valeur)
            return 0;
    }
    return 1;
}

int is_square_true(Board grid, int i, int j, int valeur)
{

    int x, y, n1, n2;
    find_square(i, &x, &n1);
    find_square(j, &y, &n2);

    int sauv_x = x;
    int sauv_y = y;
    for (x = sauv_x; x < n1; x++)
    {
        for (y = sauv_y; y < n2; y++)
        {
            if (grid[x][y] == valeur)
            {
                return 0;
            }
        }
    }
    return 1;
}

void find_square(int value, int *result1, int *result2)
{
    if (value >= 0 && value < 3)
    {
        *result1 = 0;
        *result2 = 3;
    }
    else if (value > 2 && value < 6)
    {
        *result1 = 3;
        *result2 = 6;
    }
    else
    {
        *result1 = 6;
        *result2 = 9;
    }
}

int is_value_true(Board grid, int i, int j, int valeur)
{
    if (is_line_true(grid, i, valeur) && is_row_true(grid, j, valeur) && is_square_true(grid, i, j, valeur))
        return 1;
    return 0;
}

int find_zero(Board grid, int *i, int *j)
{
    int x, y;
    for (x = 0; x < 9; x++)
    {
        for (y = 0; y < 9; y++)
        {
            if (grid[x][y] == 0)
            {
                *i = x;
                *j = y;
                return 1;
            }
        }
    }
    return 0;
}

void permutations(Board grid)
{

    int i, j;
    if (!find_zero(grid, &i, &j))
    {
        print_board(grid);
        return;
    }
    /*print_board(grid);*/

    int x;
    for (x = 1; x < 10; x++)
    {

        if (is_value_true(grid, i, j, x))
        {
            /*printf("is true --> %d\n",is_value_true(grid,i,j,x));*/
            grid[i][j] = x;
            permutations(grid);
            grid[i][j] = 0;
        }
    }
    return;
}

int is_end_grid(Board grid)
{
    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (grid[i][j] == 0)
                return 0;
        }
    }
    return 1;
}
