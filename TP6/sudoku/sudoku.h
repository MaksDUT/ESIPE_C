#ifndef __SUDOKU__
#define __SUDOKU__

typedef int Board[9][9];

void initialize_empty_board(Board grid);
void print_board(Board grid);
int is_line_true(Board grid, int i,int valeur);
int is_row_true(Board grid, int j,int valeur);
int is_square_true(Board grid,int i, int j,int valeur);
void find_square( int value, int* result1,int* result2);
int is_value_true(Board grid, int i, int j, int valeur);
int find_zero(Board grid, int* i, int* j);
void permutations(Board grid);


#endif
