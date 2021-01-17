#include <stdio.h>
#include <MLV/MLV_all.h>

#include "sudoku.h"
#include "in_out.h"
#include "draw.h"

#define RATIO_GRID 0.8
#define RATIO_WINDOW 1
#define BACKGROUND_C_WINDOW MLV_rgba(28, 40, 51, 255)
/*#define BACKGROUND_C_GRID MLV_rgba(81, 46, 95, 255)*/
#define FONT_DEFAULT "font/Nunito.ttf"
#define FONT_WIN "font/Nunito.ttf"

int main(int argc, char *argv[])
{
    Board B;
    Couple *table_couple;
    table_couple = malloc(sizeof(Couple) * 81);
    int count;
    int x_pixel, y_pixel, i, j, value;
    int width = MLV_get_desktop_width() * RATIO_WINDOW;
    int height = MLV_get_desktop_height() * RATIO_WINDOW;
    /*variable text*/
    char *fileGrid = "";
    char text_grid[80] = "Sudoku : ";
    char text_error_value[80];

    if (argc < 2)
    {
        printf("ERROR : to start the program you have to put in argument a \"grid.txt\" which is in the data folder. \
    \n the argument \"Test\" allows to start the program with the first grid (grid1.txt). \n");
        return 0;
    }
    if (!strcmp(argv[1], "test"))
    {
        fileGrid = "data/grid1.txt";
    }
    else
    {
        fileGrid = argv[1];
    }

    /* initialize the grid*/
    if (!fread_board(fileGrid, B))
    {
        printf("ERROR :The file does not exist. You can find the available files in the data folder. furthermore you can start the program with 'test' in argument to start sudoku with the first grid. \n");
        return 0;
    }
    /*a table which groups together the cells already filled in the file in argument*/
    count = find_first_couple(B, &table_couple);

    sprintf(text_grid, fileGrid);
    sprintf(text_grid, " Sudoku :  %s", fileGrid);

    /* initialize the window*/
    MLV_create_window("Sudoku", "it's me", width, height);

    MLV_draw_filled_rectangle(0, 0, width, height, BACKGROUND_C_WINDOW);
    MLV_change_default_font(FONT_DEFAULT, 20);

    /*initialize the grid draw*/
    print_grid(B, width, height, RATIO_GRID, table_couple, count);

    MLV_draw_text(
        width * 0.05, 10,
        text_grid,
        MLV_COLOR_GREEN);

    MLV_actualise_window();

    /*Main game loop*/
    MLV_Event event = MLV_NONE;
    MLV_Keyboard_button key_button;
    MLV_Mouse_button mouse_button;
    MLV_Button_state mouse_state;

    while (!(event == MLV_KEY && key_button == MLV_KEYBOARD_ESCAPE) && !is_end_grid(B))
    {
        event = MLV_wait_event(
            &key_button,
            NULL,
            NULL,
            NULL,
            NULL,
            &x_pixel,
            &y_pixel,
            &mouse_button,
            &mouse_state);
        /*the user left clicks */
        if (event == MLV_MOUSE_BUTTON && mouse_button == MLV_BUTTON_LEFT)
        {
            /*If the click is in the grid find the coordinates of the cell (i,j) if not return -1,-1 in i,j*/
            search_case_grid(x_pixel, y_pixel, width, height, RATIO_GRID, &i, &j);

            if (isACaseTrue(i, j) == 1)
            {
                /*find if the case can be change*/
                if (!is_couple(table_couple, i, j, count))
                {
                    print_grid_value(width, height, 0.33);
                    MLV_draw_circle(x_pixel, y_pixel, 30, MLV_COLOR_RED);
                    MLV_actualise_window();

                    int right = 0;
                    do
                    {
                        MLV_wait_mouse(&x_pixel, &y_pixel);
                        value = search_case_value(x_pixel, y_pixel, width, height);
                        if (value == -1)
                        {
                            right = 1;
                        }
                        else if (value == 0)
                        {
                            B[i][j] = 0;
                            right = 1;
                        }
                        else
                        {
                            if (is_value_true(B, i, j, value))
                            {
                                B[i][j] = value;
                                right = 1;
                            }
                            else
                            {
                                sprintf(text_error_value, " ERROR : \nThe number %d is already in the line, row or square.", value);
                                MLV_draw_text_box(
                                    width * 0.6, height * 0.1, width * 0.35, height * 0.35,
                                    text_error_value, 3,
                                    MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_BLACK,
                                    MLV_TEXT_CENTER, MLV_TEXT_CENTER, MLV_TEXT_CENTER);
                                MLV_actualise_window();
                            }
                        }
                    } while (!right);
                }
            }
            MLV_draw_filled_rectangle(0, 0, width, height, BACKGROUND_C_WINDOW);
            print_grid(B, width, height, RATIO_GRID, table_couple, count);

            MLV_draw_text(
                width * 0.05, 10,
                text_grid,
                MLV_COLOR_GREEN);

            MLV_actualise_window();
        }
    }
    /* do{
      MLV_draw_text(
              width*0.05, 10,
              "Cliquez sur la fenêtre à l'aide de la souris pour faire apparaître un cercle",
              MLV_COLOR_GREEN
      );

      MLV_draw_text(
          width*0.05, height*0.92,
          "pour arreter le programme faite le rond puis apuiller sur q ou n'importe quelle autre touche pour refaire un test",
          MLV_COLOR_GREEN
      );



      print_grid(B,width,height,0.8,table_couple,count);

      MLV_actualise_window();

      MLV_wait_mouse(&x_pixel, &y_pixel);

      search_case_grid(x_pixel,y_pixel,width,height,&i,&j);

      if(isACaseTrue(i,j)==1){
        if(B[i][j]==0 || !is_couple(table_couple,i,j,count)){
          print_grid_value(width,height,0.33);
          MLV_draw_circle( x_pixel, y_pixel, 30, MLV_COLOR_RED );
          MLV_actualise_window();

          int right = 0;
          do{
            MLV_wait_mouse(&x_pixel, &y_pixel);
            value=search_case_value(x_pixel,y_pixel,width,height);
            if(value!=-1){
              if(is_value_true(B,i,j,value)==1){
                B[i][j]=value;
                right=1;
              }
            }else{
              right=1;
            }
          }while(right ==0);
        }
      }



      MLV_actualise_window();


      MLV_wait_keyboard( &touche, NULL, NULL );
      MLV_draw_filled_rectangle(0,0,width,height,MLV_COLOR_BLACK);
      
  

  }while(!is_end_grid(B)); 
*/
    MLV_draw_filled_rectangle(0, 0, width, height, BACKGROUND_C_WINDOW);

    MLV_change_default_font(FONT_DEFAULT, 64);

    float position_y_message = 0.4;

    if (is_end_grid(B))
    {
        MLV_change_default_font(FONT_WIN, 64);
        position_y_message = 0.6;

        MLV_draw_text(
            width * 0.3, height * 0.3,
            "YOU WIN !!!! ",
            MLV_COLOR_GREEN);
        MLV_actualise_window();
    }

    MLV_draw_text(
        width * 0.2, height * position_y_message,
        "the window will close in 10s",
        MLV_COLOR_GREEN);
    MLV_actualise_window();
    MLV_wait_seconds(10);

    /* free the window and the table */
    MLV_free_window();
    free(table_couple);

    return 0;
}
