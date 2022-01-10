#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "top_10.h"
#include "save, load.h"

#define  reset "\x1b[0m"


#define  black "\x1b[30m"
#define  red "\x1b[31m"
#define  green "\x1b[32m"
#define  yellow "\x1b[33m"
#define  blue "\x1b[34m"
#define  magenta "\x1b[35m"
#define  cyan "\x1b[36m"
#define  white "\x1b[37m"

#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define Background_Light_Red BACKGROUND_INTENSITY | BACKGROUND_RED
#define Background_Light_Blue BACKGROUND_GREEN | BACKGROUND_BLUE



void print_board(int scores[], int moves[], int maxmoves, int time_spent){

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // Gets the standard output handle

    SetConsoleTextAttribute(hOut, 9); // color is bright blue
    printf("    Player 1's score: %d                     ", scores[0]);
    SetConsoleTextAttribute(hOut, 12); // color is bright red
    printf("    Player 2's score: %d\n", scores[1]);

    SetConsoleTextAttribute(hOut, 9);  // color is bright blue
    printf("    Player 1's moves: %d                     ", moves[0]);
    SetConsoleTextAttribute(hOut, 12);  // color is bright red
    printf("    Player 2's moves: %d\n\n", moves[1]);

    SetConsoleTextAttribute(hOut, 11);  // color is bright yellow
    printf("    Time Passed: %d : %d : %d\t\t\t", time_spent/3600, (time_spent%3600)/60, (time_spent%3600)%60);
    printf("Remaining moves: %d\n\n", maxmoves - moves[0] - moves[1]);

    SetConsoleTextAttribute(hOut, 14);
    printf("    Enter (a) to SAVE in file 1,  (b) to SAVE in file 2 OR (c) to SAVE in file 3\n");
    printf("    Enter (u) to UNDO,  (r) to REDO  OR (e) to Exit Game and Return to Main Menu.\n    And remember, you need to UNDO First to REDO Back :)");

    SetConsoleTextAttribute(hOut, FOREGROUND_WHITE); // resets the color

    printf("                     \n\n");
}


// function returns struct
 players getplayerinfo(){

  players player;

  printf("Player Name: ");
  fgets(player.name, 30, stdin);
  while(player.name[0] < 'A' || player.name[0] > 'z'){
    if(player.name[0] != '\n')printf(reset red "   Enter Valid Name" reset);
    //fgets(player.name, 30, stdin);
    fgets(player.name, 30, stdin);
  }

  return player;
}



struct point{
    int row;
    int col;
};

struct line{
    struct point point1;
    struct point point2;
};


// function returns struct
struct line getLine(){

  struct line lineG;
  char in1[30], in2[30], in3[30], in4[30];

  enter_again:
  printf(green "  ROW: ");
  fgets(in1, 30, stdin);

  printf("  ROW: ");
  fgets(in2, 30, stdin);

  printf("  COL: ");
  fgets(in3, 30, stdin);

  printf("  COL: ");
  fgets(in4, 30, stdin);

  if(in1[1] != '\n' || in2[1] != '\n' || in3[1] != '\n' || in4[1] != '\n'){printf(red "    Enter Valid Input\n" reset);goto enter_again;}

  switch(in1[0]){
   case '1':lineG.point1.row = 1;break;case '2':lineG.point1.row = 2;break;case '3':lineG.point1.row = 3;break;
   case '4':lineG.point1.row = 4;break;case '5':lineG.point1.row = 5;break;case '6':lineG.point1.row = 6;break;
   case '7':lineG.point1.row = 7;break;case '8':lineG.point1.row = 8;break;case '9':lineG.point1.row = 9;break;

   case 'e':lineG.point1.row = 0;break;case 'E':lineG.point1.row = 0;break;

   case 'u':lineG.point1.row = -1;break;case 'r':lineG.point1.row = -2;break;
   case 'U':lineG.point1.row = -1;break;case 'R':lineG.point1.row = -2;break;
    case 'a':lineG.point1.row = -5;break;case 'b':lineG.point1.row = -6;break;case 'c':lineG.point1.row = -7;break;
    case 'A':lineG.point1.row = -5;break;case 'B':lineG.point1.row = -6;break;case 'C':lineG.point1.row = -7;break;

   default : printf(red "    Enter Valid Input\n" reset);goto enter_again;break;
  }

  switch(in3[0]){
   case '1':lineG.point1.col = 1;break;case '2':lineG.point1.col = 2;break;case '3':lineG.point1.col = 3;break;
   case '4':lineG.point1.col = 4;break;case '5':lineG.point1.col = 5;break;case '6':lineG.point1.col = 6;break;
   case '7':lineG.point1.col = 7;break;case '8':lineG.point1.col = 8;break;case '9':lineG.point1.col = 9;break;

   case 'e':lineG.point1.col = 0;break;case 'E':lineG.point1.col = 0;break;

   case 'u':lineG.point1.col = -1;break;case 'r':lineG.point1.col = -2;break;
   case 'U':lineG.point1.col = -1;break;case 'R':lineG.point1.col = -2;break;
    case 'a':lineG.point1.col = -5;break;case 'b':lineG.point1.col = -6;break;case 'c':lineG.point1.col = -7;break;
    case 'A':lineG.point1.col = -5;break;case 'B':lineG.point1.col = -6;break;case 'C':lineG.point1.col = -7;break;

   default : printf(red "    Enter Valid Input\n" reset);goto enter_again;break;
  }

  switch(in2[0]){
   case '1':lineG.point2.row = 1;break;case '2':lineG.point2.row = 2;break;case '3':lineG.point2.row = 3;break;
   case '4':lineG.point2.row = 4;break;case '5':lineG.point2.row = 5;break;case '6':lineG.point2.row = 6;break;
   case '7':lineG.point2.row = 7;break;case '8':lineG.point2.row = 8;break;case '9':lineG.point2.row = 9;break;

   case 'e':lineG.point2.row = 0;break;case 'E':lineG.point2.row = 0;break;

   case 'u':lineG.point2.row = -1;break;case 'r':lineG.point2.row = -2;break;
   case 'U':lineG.point2.row = -1;break;case 'R':lineG.point2.row = -2;break;
    case 'a':lineG.point2.row = -5;break;case 'b':lineG.point2.row = -6;break;case 'c':lineG.point2.row = -7;break;
    case 'A':lineG.point2.row = -5;break;case 'B':lineG.point2.row = -6;break;case 'C':lineG.point2.row = -7;break;

   default : printf(red "    Enter Valid Input\n" reset);goto enter_again;break;
  }

  switch(in4[0]){
   case '1':lineG.point2.col = 1;break;case '2':lineG.point2.col = 2;break;case '3':lineG.point2.col = 3;break;
   case '4':lineG.point2.col = 4;break;case '5':lineG.point2.col = 5;break;case '6':lineG.point2.col = 6;break;
   case '7':lineG.point2.col = 7;break;case '8':lineG.point2.col = 8;break;case '9':lineG.point2.col = 9;break;

   case 'e':lineG.point2.col = 0;break;case 'E':lineG.point2.col = 0;break;

   case 'u':lineG.point2.col = -1;break;case 'r':lineG.point2.col = -2;break;
   case 'U':lineG.point2.col = -1;break;case 'R':lineG.point2.col = -2;break;
    case 'a':lineG.point2.col = -5;break;case 'b':lineG.point2.col = -6;break;case 'c':lineG.point2.col = -7;break;
    case 'A':lineG.point2.col = -5;break;case 'B':lineG.point2.col = -6;break;case 'C':lineG.point2.col = -7;break;

   default : printf(red "    Enter Valid Input\n" reset);goto enter_again;break;
  }


  return lineG;
}


int game(char x) {

  system("");//for enabling colors

  int n, m;

    switch(x){

      case 'b':n = 2; m = 2;break;  // Beginners get 2 X 2 grid
      case 'B':n = 2; m = 2;break;  // Beginners get 2 X 2 grid

      case 'e':n = 5; m = 5;break;  // Experts get 5 X 5 grid
      case 'E':n = 5; m = 5;break;  // Experts get 5 X 5 grid

      case 'c':
        printf( cyan "\n\n  Grid is n X m boxes\n");
        printf("  n: " reset);scanf("%d", &n);
        while(n > 8 || n < 1){printf(red "  Invalid Number, Enter number from 1 to 8\n  " reset);scanf("%d", &n);}
        printf(cyan "  m: "reset);scanf("%d", &m);
        while(m > 8 || m < 1){printf(red "  Invalid Number, Enter number from 1 to 8\n  " reset);scanf("%d", &m);}
        system("cls");break;

      case 'l':loadNM(1, &n, &m);break; // in case of loading an old game
      case 's':loadNM(2, &n, &m);break; // in case of loading an old game
      case 'p':loadNM(3, &n, &m);break; // in case of loading an old game

  }


    int grid[2*n+1][2*m+1];
    int colorsgrid[2*n+1][2*m+1];


  // guarantee that all grid elements are empty
    for(int i = 0; i < 2*n+1; i++){

        for(int j = 0; j < 2*m+1; j++){

            grid[i][j] = 32;
            colorsgrid[i][j] = FOREGROUND_WHITE ;

        }
    }


    // making the grid
    for(int i =0;i < 2*n+1; i++){

        if(i%2 == 0){
            for(int j = 0; j < 2*m+1; j+=2){
                grid[i][j] = 254;
            }
            for(int j = 1; j < 2*m+1; j+=2){
                grid[i][j] = 32;
            }
        }

        else {
          for(int j = 0; j < 2*m+1; j+=2){
                grid[i][j] = 32;
            }
        }

    }





  //whenever maxmoves is reached game is over
  int maxmoves =  m*(n+1) + n*(m+1);

  players playersInfo[2];

  int scores[2] = {0, 0}, boxClosed = 0;
  int moves[2] = {}, totalmoves = moves[0] + moves[1];
  int colors[2] = {9, 12}; // bright blue & bright red
  int backcolors[2] = {Background_Light_Blue, Background_Light_Red}; // background colors in case player scored a box
  int currentplaying = 0;
  int row1 = 0, row2 = 0, col1 = 0, col2 = 0;
  int chosenrows[maxmoves], chosencols[maxmoves];
  int redorows[maxmoves], redocols[maxmoves], redocounter = 0;
  int valid_choice = 0, withinlimits = 1, lineAvlbe = 1;

  static int time_spent;

  //static players top10[10];



  //----------------------Taking players Information----------------------------

  // ---------------- load -------------------

  if(x == 'l' || x =='s' || x == 'p'){

    switch(x){

        case 'l':load(1, &time_spent, playersInfo, &maxmoves, scores, moves, &currentplaying, chosenrows,
                    chosencols, redocols, redorows, &redocounter, &n, &m, grid, colorsgrid);break; // in case of loading an old game
        case 's':load(2, &time_spent, playersInfo, &maxmoves, scores, moves, &currentplaying, chosenrows,
                    chosencols, redocols, redorows, &redocounter, &n, &m, grid, colorsgrid);break; // in case of loading an old game
        case 'p':load(3, &time_spent, playersInfo, &maxmoves, scores, moves, &currentplaying, chosenrows,
                    chosencols, redocols, redorows, &redocounter, &n, &m, grid, colorsgrid);break; // in case of loading an old game
    }


  } else{

        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        printf("\n\n\t\t\t");
        SetConsoleTextAttribute(hOut, backcolors[0]);
        printf(" First ");
        playersInfo[0] = getplayerinfo();

        printf("\n\n\t\t\t");
        SetConsoleTextAttribute(hOut, backcolors[1]);
        printf(" Second ");
        playersInfo[1] = getplayerinfo();
        SetConsoleTextAttribute(hOut, FOREGROUND_WHITE); // resets the color

        system("cls");


  }



  // -------------------------------------------------------------- starting the game ----------------------------------------------------


//--------------------------printing grid for the first time------------------

              // columns rank before the grid
              printf("\n\n                                 ");
              for(int j = 0; j < m+1; j++){printf(yellow "%d.    " reset, j+1);}
              printf("\n\n");


              for(int i = 0;i < 2*n+1; i++){
                if(!(i%2))
                printf(yellow "                          %d.    " reset, i/2+1);  // rows rank left to the grid

                else
                printf("                                ");
                for(int j = 0; j < 2*m+1; j++){
                    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // Gets the standard output handle
                    SetConsoleTextAttribute(hOut, colorsgrid[i][j]); //The font is set to it's assigned color in my array colorsgrid

                    printf(" %c ", grid[i][j]);
                    SetConsoleTextAttribute(hOut, FOREGROUND_WHITE);
                }

                printf("\n");

              }

  printf("\n\n");
  print_board(scores, moves, maxmoves, time_spent);



//------------------------------------------------ Game Loop --------------------------------------------


  while(maxmoves - moves[0] - moves[1]){

    no_moves_to_undo:
    no_moves_to_redo:

    valid_choice = 0;boxClosed = 0;
    totalmoves = moves[0] + moves[1];

    clock_t begin = 0, end = 0;

    begin = clock();

    printf(green "   Turn OF: " reset);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, colors[currentplaying%2]);
    printf(" %s", playersInfo[currentplaying%2].name);
    SetConsoleTextAttribute(hOut, FOREGROUND_WHITE);

    struct line lineD;
    lineD = getLine();

    row1 = lineD.point1.row;
    row2 = lineD.point2.row;

    col1 = lineD.point1.col;
    col2 = lineD.point2.col;

    int row = 0, col = 0; // only for painting the chosen line

//---------------------------------------------- Save ---------------------------------------------------------

    if (row1 == -5 || row2 == -5 || col1 == -5 || col2 == -5){save(1, time_spent, playersInfo, scores, moves, maxmoves, chosenrows,
                                                            chosencols, redorows, redocols, redocounter, currentplaying, n, m, grid, colorsgrid);goto undo;}

    else if(row1 == -6 || row2 == -6 || col1 == -6 || col2 == -6){save(2, time_spent, playersInfo, scores, moves, maxmoves, chosenrows,
                                                            chosencols, redorows, redocols, redocounter, currentplaying, n, m, grid, colorsgrid);goto undo;}

    else if(row1 == -7 || row2 == -7 || col1 == -7 || col2 == -7){save(3, time_spent, playersInfo, scores, moves, maxmoves, chosenrows,
                                                            chosencols, redorows, redocols, redocounter, currentplaying, n, m, grid, colorsgrid);goto undo;}

//------------------------------------------break from game and return to menu ------------------------------

    if (row1 == 0 || row2 == 0 || col1 == 0 || col2 == 0){
            printf("\t\t\tBack to Main Menu in 5");Sleep(1000);
            SetConsoleTextAttribute(hOut, 6);
            printf("\n\t\t\t\t4");Sleep(1000);
            SetConsoleTextAttribute(hOut, 14);
            printf("\n\t\t\t\t3");Sleep(1000);
            SetConsoleTextAttribute(hOut, 12);
            printf("\n\t\t\t\t2");Sleep(1000);
            SetConsoleTextAttribute(hOut, 4);
            printf("\n\t\t\t\t1");Sleep(1000);
            return 0;
    }


//----------------------------------- UNDO Function ----------------------------------------------

    if(row1 == -1 || row2 == -1 || col1 == -1 || col2 == -1){

        if(!totalmoves){
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // Gets the standard output handle
            SetConsoleTextAttribute(hOut, 4); // color is bright blue
            printf("  No Previous Moves to UNDO :)\n");goto no_moves_to_undo;
            SetConsoleTextAttribute(hOut, FOREGROUND_WHITE); // color is bright blue
        }

        else{
            row = chosenrows[totalmoves-1];
            col = chosencols[totalmoves-1];

            chosenrows[totalmoves-1] = 0;
            chosencols[totalmoves-1] = 0;

            redorows[redocounter] = row;
            redocols[redocounter] = col;
            redocounter++;

            //resetting the point
            grid[row][col] = ' ';
            colorsgrid[row][col] = FOREGROUND_WHITE ;

            // ---------resetting any closed box ------------
            int undoclosedbox = 0;
            // if it's vertical line
            if(row%2){
                    if(grid[row][col+1] == 65 || grid[row][col+1] == 66){undoclosedbox = 1;scores[currentplaying%2]--;
                    grid[row][col+1] = ' ';
                    colorsgrid[row][col+1] = FOREGROUND_WHITE ;}

                    if(grid[row][col-1] == 65 || grid[row][col-1] == 66){undoclosedbox = 1;scores[currentplaying%2]--;
                    grid[row][col-1] = ' ';
                    colorsgrid[row][col-1] = FOREGROUND_WHITE ;}
            }

            // if it's horizontal line
            else{
                if(grid[row+1][col] == 65 || grid[row+1][col] == 66){undoclosedbox = 1;scores[currentplaying%2]--;
                grid[row+1][col] = ' ';
                colorsgrid[row+1][col] = FOREGROUND_WHITE ;}

                if(grid[row-1][col] == 65 || grid[row-1][col] == 66){undoclosedbox = 1;scores[currentplaying%2]--;
                grid[row-1][col] = ' ';
                colorsgrid[row-1][col] = FOREGROUND_WHITE ;}
            }

            if(undoclosedbox){currentplaying++;undoclosedbox = 0;}

            currentplaying++;
            moves[currentplaying%2]--;

            goto undo;
        }
    }


//----------------------------------- REDO Function ----------------------------------------------
    if(row1 == -2 || row2 == -2 || col1 == -2 || col2 == -2){

        if(!redocounter){
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // Gets the standard output handle
            SetConsoleTextAttribute(hOut, 4); // color is bright blue
            printf("  No Further Moves to REDO :)\n");goto no_moves_to_redo;
            SetConsoleTextAttribute(hOut, FOREGROUND_WHITE); // color is bright blue
        }

        else{

            row = redorows[redocounter-1];
            col = redocols[redocounter-1];
            if(redocounter)redocounter--;

            chosenrows[totalmoves] = row;
            chosencols[totalmoves] = col;

            if(row%2){
                grid[row][col] = 186;
                colorsgrid[row][col] = colors[currentplaying%2];
            }

            else{
                grid[row][col] = 205;
                colorsgrid[row][col] = colors[currentplaying%2];
            }

            goto redo;

        }


    }

//----------------------------------End of UNDO & REDO ----------------------------------



    // resetting the redo array in case they enter a move
    for(int i = 0; i < maxmoves; i++){redorows[i] = 0;redocols[i] = 0;redocounter = 0;}


    // changing the right point on grid
    // if it's horizontal line
    if(col1 < col2){row = 2*row1-2, col = 2*col1-1;}
    else if(col1 > col2){row = 2*row1-2, col = 2*col2-1;}

    // if it's vertical line
    if(row1 < row2){row = 2*row1-1, col = 2*col1-2;}
    else if(row1 > row2){row = 2*row2-1, col = 2*col1-2;}


    int rowdiff = abs(row1 - row2);
    int coldiff = abs(col1 - col2);

    // check if the line is within limits of my grid
    if( (row1 > n+1) || (row2 > n+1) || (col1 > m+1) || (col2 > m+1) )withinlimits = 0; // if beyond limits number
    if( (row1 < 1) || (row2 < 1) || (col1 < 1) || (col2 < 1) )withinlimits = 0; // if -ve number


    if((rowdiff==1 && !coldiff && withinlimits) || (coldiff==1 && !rowdiff && withinlimits)){

        //----need to make sure these points have NOT been chosen before---------------
        // is line chosen ?
        for(int i = 0; i < totalmoves; i++){
           if(chosenrows[i] == row && chosencols[i] == col){lineAvlbe = 0;break;}
        }

        if(!lineAvlbe){
            printf(red "  Line Already Chosen, looks like you are not paying attention to the board :(\n" reset);lineAvlbe = 1;}

        else {valid_choice = 1;chosenrows[totalmoves] = row;chosencols[totalmoves] = col;}

    }

    else if(!withinlimits) {
        printf(red "  Invalid Points, the points are beyond limits :)\n" reset);withinlimits = 1;
    }
    else{
        printf(red "  Invalid Points, you should enter adjacent points :)\n" reset);
    }


    if(valid_choice){

        // changing the right point on grid
        // if it's horizontal line
        if(row1 == row2){
                grid[row][col] = 205;
                colorsgrid[row][col] = colors[currentplaying%2];}
        // if it's vertical line
        if(col1 == col2){
                grid[row][col] = 186;
                colorsgrid[row][col] = colors[currentplaying%2];}

        //------------------------------ is it a box ?-----------------------------------
        redo:
        if(row % 2 == 0){ //if it's row
            if(!row){ //if it's not top row nor bottom row

                if(grid[row+2][col] != 32 && grid[row+1][col-1] != 32 && grid[row+1][col+1] != 32)
                        {grid[row+1][col] = currentplaying%2+65;colorsgrid[row+1][col] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

            }

            else if(row == 2*n){ // if it's top row , check only the box under it

                if(grid[row-2][col] != 32 && grid[row-1][col-1] != 32 && grid[row-1][col+1] != 32)
                        {grid[row-1][col] = currentplaying%2+65;colorsgrid[row-1][col] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

              }

            else{ // if it's bottom row , check only the box above it

                if(grid[row-2][col] != 32 && grid[row-1][col-1] != 32 && grid[row-1][col+1] != 32)
                        {grid[row-1][col] = currentplaying%2+65;colorsgrid[row-1][col] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

                if(grid[row+2][col] != 32 && grid[row+1][col-1] != 32 && grid[row+1][col+1] != 32)
                        {grid[row+1][col] = currentplaying%2+65;colorsgrid[row+1][col] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

              }
        }
        //if it's column
        if(row % 2 == 1){
            if(!col){

                if(grid[row][col+2] != 32 && grid[row-1][col+1] != 32 && grid[row+1][col+1] != 32)
                        {grid[row][col+1] = currentplaying%2+65;colorsgrid[row][col+1] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

            }

            else if(col == 2*m){

                if(grid[row][col-2] != 32 && grid[row-1][col-1] != 32 && grid[row+1][col-1] != 32)
                        {grid[row][col-1] = currentplaying%2+65;colorsgrid[row][col-1] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

            }

            else {

                if(grid[row][col-2] != 32 && grid[row-1][col-1] != 32 && grid[row+1][col-1] != 32)
                        {grid[row][col-1] = currentplaying%2+65;colorsgrid[row][col-1] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

                if(grid[row][col+2] != 32 && grid[row-1][col+1] != 32 && grid[row+1][col+1] != 32)
                        {grid[row][col+1] = currentplaying%2+65;colorsgrid[row][col+1] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

            }
        }



        moves[currentplaying%2]++;
        totalmoves = moves[0] + moves[1]; // number of moves increase for the player 1 or 2
        if(boxClosed){currentplaying--;}
        currentplaying++;

        end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

//--------------------------printing grid after each valid move------------------
              // columns rank before the grid
              undo:
              system("cls");
              printf("\n\n                                 ");
              for(int j = 0; j < m+1; j++){printf(yellow "%d.    " reset, j+1);}
              printf("\n\n");


              for(int i = 0;i < 2*n+1; i++){
                if(!(i%2))
                printf(yellow "                          %d.    " reset, i/2+1);  // rows rank left to the grid

                else
                printf("                                ");
                for(int j = 0; j < 2*m+1; j++){

                    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // Gets the standard output handle
                    SetConsoleTextAttribute(hOut, colorsgrid[i][j]); //The font is set to it's assigned color in my array colorsgrid

                    printf(" %c ", grid[i][j]);
                    SetConsoleTextAttribute(hOut, FOREGROUND_WHITE);

                }

                printf("\n");

              }

        printf("\n\n");
        print_board(scores, moves, maxmoves, time_spent);

    }


  }

    playersInfo[0].score = scores[0];
    playersInfo[1].score = scores[1];
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // Gets the standard output handle
  if(scores[0] > scores[1]){
        printf("\t\t\tCongratulations, ");
        SetConsoleTextAttribute(hOut, colors[0]);
        printf("%s\t\t\t You are the WINNER !\n", playersInfo[0].name);}


  else if(scores[0] < scores[1]){
        printf("\t\t\tCongratulations, ");
        SetConsoleTextAttribute(hOut, colors[1]);
        printf("%s\t\t\t You are the WINNER !\n", playersInfo[1].name);}

  else printf(cyan "\t\t\tNo Winners Today \n\t\t\t  It's a TIE !\n" reset);

  SetConsoleTextAttribute(hOut, FOREGROUND_WHITE);



  //-------------------------------comparing the players to the top 10 list -------------------


  // calling the top 10 in an array
    players top_ten[10];

    FILE *fp;
    char* file_name;
    file_name = "top_10_list.text";

    fp = fopen(file_name, "r");

    if (fp == NULL){printf("ERROR: can\'t open file\n");}

    for(int i = 0; i < 10; i++){
     fgets(top_ten[i].name, 30, fp);
     fscanf(fp, "%d\n", &top_ten[i].score);
    }

    fclose(fp);


    //comparing the ;last players to the top 10
    int index = 0;

    for(int j = 0; j < 2; j++){
        for(int i = 0; i < 10; i++){
         if(playersInfo[j].score == top_ten[i].score){index = i;break;}
        }

        players temp = playersInfo[j];
        for(int i = index; i < 10; i++){
            players tt;
            tt = temp;
            temp = top_ten[i];
            top_ten[i] = tt;
        }
    }


    // saving the new top 10 in the text file
    fp = fopen(file_name, "w");

    if (fp == NULL){printf("ERROR: can\'t open file\n");}

    for(int i = 0; i < 10; i++){
     fprintf(fp, "%s", top_ten[i].name);
     fprintf(fp, "%d\n", top_ten[i].score);
    }

    fclose(fp);

//-------------------- printing top ten list -----------------------

    top_ten_list();


  return 0;

}
