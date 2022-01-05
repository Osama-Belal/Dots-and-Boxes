#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "top_10.h"
#include "playing.h"

int random_number(int min, int max){
    int random = (rand() % (max - min + 1)) + min;
    return random;
}

int vs_computer(char x) {

  system("");//for enabling colors
  srand(time(0));

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
      case 'C':
        printf( cyan "\n\n  Grid is n X m boxes\n");
        printf("  n: " reset);scanf("%d", &n);
        while(n > 8 || n < 1){printf(red "  Invalid Number, Enter number from 1 to 8\n  " reset);scanf("%d", &n);}
        printf(cyan "  m: "reset);scanf("%d", &m);
        while(m > 8 || m < 1){printf(red "  Invalid Number, Enter number from 1 to 8\n  " reset);scanf("%d", &m);}
        system("cls");break;

  }

    char grid[2*n+1][2*m+1];
    int colorsgrid[2*n+1][2*m+1];

  // guarantee that all grid elements are empty
    for(int i = 0; i < 2*n+1; i++){

        for(int j = 0; j < 2*m+1; j++){

            grid[i][j] = ' ';
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
                grid[i][j] = ' ';
            }
        }

        else {
          for(int j = 0; j < 2*m+1; j+=2){
                grid[i][j] = ' ';
            }
        }

    }


  // --------------------------------------- starting the game -----------------------

  //whenever maxmoves is reached game is over
  int maxmoves =  m*(n+1) + n*(m+1);

  static struct players playersInfo[2];
  struct line lineD;

  int scores[2] = {0, 0}, boxClosed = 0;
  int moves[2] = {}, totalmoves = moves[0] + moves[1];
  int colors[2] = {9, 12}; // bright blue & bright red
  int backcolors[2] = {Background_Light_Blue, Background_Light_Red}; // background colors in case player scored a box
  int currentplaying = 0;
  int row1 = 0, row2 = 0, col1 = 0, col2 = 0;
  int row = 0, col = 0;
  int chosenrows[maxmoves], chosencols[maxmoves];
  int redorows[maxmoves], redocols[maxmoves], redocounter = 0;
  int valid_choice = 0, withinlimits = 1, lineAvlbe = 1;


  //----------------------Taking players Information----------------------------

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, backcolors[0]);
    printf("\n\n\t\t\t");
    playersInfo[0] = getplayerinfo();
    strcpy(playersInfo[1].name, "computer\n");
    SetConsoleTextAttribute(hOut, FOREGROUND_WHITE); // resets the color

    system("cls");

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
  print_board(scores, moves, maxmoves);


  while(maxmoves - moves[0] - moves[1]){
    no_moves_to_undo:
    no_moves_to_redo:

    valid_choice = 0;boxClosed = 0;
    totalmoves = moves[0] + moves[1];
    printf(green "   Turn OF: " reset);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, colors[currentplaying%2]);
    printf(" %s", playersInfo[currentplaying%2].name);
    SetConsoleTextAttribute(hOut, FOREGROUND_WHITE);


//------------------taking move from computer ---------------

/*
    row = random_number(1, 2*n);
    col = random_number(1, 2*m);

    while((row%2 && col%2) || (row%2==0 && col%2==0)){
        row = random_number(1, 2*n);
        col = random_number(1, 2*m);
    }*/

    if(currentplaying%2){

        move_chosen:

        //----------------------------------------- Almost Closed Box ----------------------------------------------
/*
        for(int i = 1; i < 2*m; i+=2){
            if(grid[1][i-1] != 32 && grid[1][i+1] != 32 && grid[2][i] != 32){row = 0;col = i;goto chosen;}
            if(grid[2*n-1][i-1] != 32 && grid[2*n-1][i+1] != 32 && grid[2*n-2][i] != 32){row = 2*n;col = i;goto chosen;}
        }

        for(int i = 2; i <= 2*n-2; i=+2){
            for(int j = 1; j <= 2*m-1; j=+2){
                if((grid[i-1][j-1] != 32 && grid[i-1][j+1] != 32 && grid[i-2][j] != 32) ||
                  (grid[i+1][j-1] != 32 && grid[i+1][j+1] != 32 && grid[i+2][j] != 32)){row = i;col = j;goto chosen;}
            }
        }

        for(int i = 1; i < 2*n; i+=2){
            if(grid[i-1][1] != 32 && grid[i+1][1] != 32 && grid[i][2] != 32){row = i;col = 0;goto chosen;}
            if(grid[i-1][2*m-1] != 32 && grid[i+1][2*m-1] != 32 && grid[i][2*m-2] != 32){row = i;col = 2*m;goto chosen;}
        }

        for(int i = 2; i <= 2*m-2; i=+2){
            for(int j = 1; j <= 2*n-1; j=+2){
                if( (grid[j-1][i-1] != 32 && grid[j+1][i-1] != 32 && grid[j][i-2] != 32) ||
                  (grid[j-1][i+1] != 32 && grid[j+1][i+1] != 32 && grid[j][i+2] != 32) ){row = j;col = i;goto chosen;}
            }
        }

        //----------------------------------------- Empty Box ----------------------------------------------

        for(int i = 1; i < 2*m; i+=2){
            if(grid[1][i-1] == 32 && grid[1][i+1] == 32 && grid[2][i] == 32){printf("2");row = 0;col = i;goto chosen;}
            if(grid[2*n-1][i-1] == 32 && grid[2*n-1][i+1] == 32 && grid[2*n-2][i] == 32){printf("1");row = 2*n;col = i;goto chosen;}
        }

        for(int i = 2; i <= 2*n-2; i=+2){
            for(int j = 1; j <= 2*m-1; j=+2){
                if( (grid[i-1][j-1] == 32 && grid[i-1][j+1] == 32 && grid[i-2][j] == 32) ||
                  (grid[i+1][j-1] == 32 && grid[i+1][j+1] == 32 && grid[i+2][j] == 32) ){printf("9");row = i;col = j;goto chosen;}
            }
        }

        for(int i = 1; i < 2*n; i+=2){
            if(grid[i-1][1] == 32 && grid[i+1][1] == 32 && grid[i][2] == 32){printf("7");row = i;col = 0;goto chosen;}
            if(grid[i-1][2*m-1] == 32 && grid[i+1][2*m-1] == 32 && grid[i][2*m-2] == 32){printf("6");row = i;col = 2*m;goto chosen;}
        }

        for(int i = 2; i <= 2*m-2; i=+2){
            for(int j = 1; j <= 2*n-1; j=+2){
                if( (grid[j-1][i-1] == 32 && grid[j+1][i-1] == 32 && grid[j][i-2] == 32) ||
                  (grid[j-1][i+1] == 32 && grid[j+1][i+1] == 32 && grid[j][i+2] == 32) ){printf("5");row = j;col = i;goto chosen;}
            }
        }
*/
        //------------------------------------- Pick Random Then -------------------------------------------------------

        row = random_number(1, 2*n);
        col = random_number(1, 2*m);

        while((row%2 && col%2) || (row%2==0 && col%2==0)){
            row = random_number(1, 2*n);
            col = random_number(1, 2*m);
        }

        chosen:
        for(int i = 0; i < totalmoves; i++){
           if(chosenrows[i] == row && chosencols[i] == col)goto move_chosen;
        }

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

        goto computer_turn;
    }

    //-------------------------taking move from player -------------------

    else{
        printf("row %d col %d", row, col);
        lineD = getLine();

        row1 = lineD.point1.row;
        row2 = lineD.point2.row;

        col1 = lineD.point1.col;
        col2 = lineD.point2.col;
    }



    row = 0;col = 0; // only for painting the chosen line



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
                    if(grid[row][col+1] == 65 || grid[row][col+1] == 67){undoclosedbox = 1;scores[currentplaying%2]--;
                    grid[row][col+1] = ' ';
                    colorsgrid[row][col+1] = FOREGROUND_WHITE ;}

                    if(grid[row][col-1] == 65 || grid[row][col-1] == 67){undoclosedbox = 1;scores[currentplaying%2]--;
                    grid[row][col-1] = ' ';
                    colorsgrid[row][col-1] = FOREGROUND_WHITE ;}
            }

            // if it's horizontal line
            else{
                if(grid[row+1][col] == 65 || grid[row+1][col] == 67){undoclosedbox = 1;scores[currentplaying%2]--;
                grid[row+1][col] = ' ';
                colorsgrid[row+1][col] = FOREGROUND_WHITE ;}

                if(grid[row-1][col] == 65 || grid[row-1][col] == 67){undoclosedbox = 1;scores[currentplaying%2]--;
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
        computer_turn:
        if(row % 2 == 0){ //if it's row
            if(!row){ //if it's not top row nor bottom row

                if(grid[row+2][col] != 32 && grid[row+1][col-1] != 32 && grid[row+1][col+1] != 32)
                        {grid[row+1][col] = (currentplaying%2)*2+65;colorsgrid[row+1][col] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

            }

            else if(row == 2*n){ // if it's top row , check only the box under it

                if(grid[row-2][col] != 32 && grid[row-1][col-1] != 32 && grid[row-1][col+1] != 32)
                        {grid[row-1][col] = (currentplaying%2)*2+65;colorsgrid[row-1][col] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

              }

            else{ // if it's bottom row , check only the box above it

                if(grid[row-2][col] != 32 && grid[row-1][col-1] != 32 && grid[row-1][col+1] != 32)
                        {grid[row-1][col] = (currentplaying%2)*2+65;colorsgrid[row-1][col] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

                if(grid[row+2][col] != 32 && grid[row+1][col-1] != 32 && grid[row+1][col+1] != 32)
                        {grid[row+1][col] = (currentplaying%2)*2+65;colorsgrid[row+1][col] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

              }
        }
        //if it's column
        if(row % 2 == 1){
            if(!col){

                if(grid[row][col+2] != 32 && grid[row-1][col+1] != 32 && grid[row+1][col+1] != 32)
                        {grid[row][col+1] = (currentplaying%2)*2+65;colorsgrid[row][col+1] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

            }

            else if(col == 2*m){

                if(grid[row][col-2] != 32 && grid[row-1][col-1] != 32 && grid[row+1][col-1] != 32)
                        {grid[row][col-1] = (currentplaying%2)*2+65;colorsgrid[row][col-1] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

            }

            else {

                if(grid[row][col-2] != 32 && grid[row-1][col-1] != 32 && grid[row+1][col-1] != 32)
                        {grid[row][col-1] = (currentplaying%2)*2+65;colorsgrid[row][col-1] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

                if(grid[row][col+2] != 32 && grid[row-1][col+1] != 32 && grid[row+1][col+1] != 32)
                        {grid[row][col+1] = (currentplaying%2)*2+65;colorsgrid[row][col+1] = backcolors[currentplaying%2];boxClosed = 1;scores[currentplaying%2]++;}

            }
        }



        moves[currentplaying%2]++;
        totalmoves = moves[0] + moves[1]; // number of moves increase for the player 1 or 2
        if(boxClosed){currentplaying--;}
        currentplaying++;

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
        print_board(scores, moves, maxmoves);

    }


  }

    playersInfo[0].score = scores[0];
    playersInfo[1].score = scores[1];

  if(scores[0] > scores[1]){
        printf("\t\t\tCongratulations, ");
        SetConsoleTextAttribute(hOut, colors[0]);
        printf("%s\t\t\t You are the WINNER !", playersInfo[0].name);}


  else if(scores[0] < scores[1]){
        printf("\t\t\t    Unfortunately, ");
        SetConsoleTextAttribute(hOut, colors[1]);
        printf("%s\t\t\t The Computer is the WINNNER !", playersInfo[0].name);}

  else printf(cyan "\t\t\tNo Winners Today \n\t\t\t  It's a TIE !" reset);

  SetConsoleTextAttribute(hOut, FOREGROUND_WHITE);

  return 0;

}
