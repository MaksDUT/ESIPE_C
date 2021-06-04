#include <stdio.h>

#include "sudoku.h"
#include "in_out.h"

int main(int argc, char *argv[])
{
    Board B;
    if (argc > 1)
    {
        if (fread_board(argv[1], B))
        {
            print_board(B);
            permutations(B);
        }
    }

    /*
  Board test;
  initialize_empty_board(test);
  printf("\n\n");
  print_board(test);
*/
    return 0;
}
