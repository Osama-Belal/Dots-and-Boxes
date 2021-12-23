#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

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

/*
void printgrid(int n, int m){

  // columns rank before the grid
  printf("\n\n                                ");
  for(int j = 0; j < m+1; j++){printf(cyan "%d.  " reset, j+1);}
  printf("\n\n");


  for(int i = 0;i < 2*n+1; i++){
    if(!(i%2))
    printf(cyan "                          %d.    " reset, i+1);  // rows rank left to the grid

    else
    printf("                                 ");  // rows rank left to the grid

    for(int j = 0; j < 2*m+1; j++){

        printf(" %c ", grid[i][j]);

    }

    printf("\n");

  }

}
*/

void print_board(int scores[], int moves[]){

    printf(blue "    Player 1 score: %d                     " reset, scores[0]);
    printf(red "    Player 2 score: %d\n" reset, scores[1]);

    printf(blue "    Player 1 moves: %d                     " reset, moves[0]);
    printf(red "    Player 2 moves: %d\n\n" reset, moves[1]);

    printf(black "    Player 1 moves: %d                     " reset, moves[0]);
    printf(black "    Player 2 moves: %d\n\n" reset, moves[1]);
}

void backgroundyellow(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // Gets the standard output handle
    SetConsoleTextAttribute(hOut, 100); //The font is set to it's assigned color in my array colorsgrid
}

struct point{
    int row;
    int col;
};

struct line{
    struct point point1;
    struct point point2;
};


struct players{
    int color;
};



// function returns struct
struct line getLine(){

  struct line lineG;

  printf(yellow "ROW: ");
  scanf ("%d", &lineG.point1.row);

  printf("ROW: ");
  scanf ("%d", &lineG.point2.row);

  printf("COL: ");
  scanf("%d", &lineG.point1.col);

  printf("COL: ");
  scanf("%d" reset, &lineG.point2.col);

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





// the previous version when i stored the grid as numbers
/*
  int grid[n+1][m+1];


  // all zeros
  for(int i =0;i < n+1; i++){
    for(int j = 0; j < m+1; j++){
      grid[i][j] = 0;
    }
  }

  // borders
  for(int i = 0; i < m+1; i++){
    grid[0][i] = 1;
  }

  for(int i = 0; i < n+1; i++){
    grid[i][0] = 1;
  }

  for(int i = 0; i < m+1; i++){
    grid[n][i] = 1;
  }

  for(int i = 0; i < n+1; i++){
    grid[i][m] = 1;
  }

  // corners
  grid[0][0] = 2;grid[0][m] = 2;grid[n][0] = 2;grid[n][m] = 2;

*/

  // --------------------------------------- starting the game -----------------------
  //whenever maxmoves is reached game is over
  int maxmoves =  m*(n+1) + n*(m+1);
  int scores[2] = {0, 23};
  int moves[2] = {};
  int colors[2] = {FOREGROUND_BLUE, FOREGROUND_RED};
  int totalmoves = 0;
  int row1 = 0, row2 = 0, col1 = 0, col2 = 0;
  int valid_choice = 0, withinlimits = 1, lineAvlbe = 1;

//--------------------------printing grid for the first time------------------
              // columns rank before the grid
              printf("\n\n                                 ");
              for(int j = 0; j < m+1; j++){printf(cyan "%d.    " reset, j+1);}
              printf("\n\n");


              for(int i = 0;i < 2*n+1; i++){
                if(!(i%2))
                printf(cyan "                          %d.    " reset, i/2+1);  // rows rank left to the grid

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
  print_board(scores, moves);


  while(totalmoves < maxmoves){

    valid_choice = 0;
    printf(green "  Player %d's turn \n" reset, (totalmoves%2)+1);
/*
    printf(yellow "  Row: ");
    scanf("%d", &row1);
    printf("  Row: ");
    scanf("%d", &row2);
    printf("  Column: ");
    scanf("%d", &col1);
    printf("  Column: ");
    scanf("%d" reset, &col2);
*/
    struct line lineD;
    lineD = getLine();

    row1 = lineD.point1.row;
    row2 = lineD.point2.row;

    col1 = lineD.point1.col;
    col2 = lineD.point2.col;


    int row = 0, col = 0; // only for painting the chosen line

    // changing the right point on grid
    // if it's horizontal line
    if(col1 < col2){row = 2*row1-2, col = 2*col1-1;}
    else if(col1 > col2){row = 2*row1-2, col = 2*col2-1;}
    // if it's vertical line
    if(row1 < row2){row = 2*row1-1, col = 2*col1-2;}
    else if(row1 > row2){row = 2*row2-1, col = 2*col1-2;}


    struct line linesArry[100];
    //linesArry[totalmoves] = lineD;

    int rowdiff = abs(row1 - row2);
    int coldiff = abs(col1 - col2);

    // check if the line is within limits of my grid
    if( (row1 > n+1) || (row2 > n+1) || (col1 > m+1) || (col2 > m+1) )withinlimits = 0; // if beyond limits number
    if( (row1 < 1) || (row2 < 1) || (col1 < 1) || (col2 < 1) )withinlimits = 0; // if -ve number


    if((rowdiff==1 && !coldiff && withinlimits) || (coldiff==1 && !rowdiff && withinlimits)){



        //----need to make sure these points have NOT been chosen before---------------
        // is line chosen ?
        for(int i = 0; i < totalmoves; i++){

           if( (lineD.point1.row == linesArry[i].point1.row || lineD.point1.row == linesArry[i].point2.row) &&
            (lineD.point1.col == linesArry[i].point1.col || lineD.point1.col == linesArry[i].point2.col) ){

                if( (lineD.point2.row == linesArry[i].point1.row || lineD.point2.row == linesArry[i].point2.row) &&
            (lineD.point2.col == linesArry[i].point1.col || lineD.point2.col == linesArry[i].point2.col) ){
                    lineAvlbe = 0;break;
                }

            }

        }

        if(!lineAvlbe){
            printf(red "Line Already Chosen, Stop ruining the game :(\n" reset);lineAvlbe = 1;}

        else {valid_choice = 1;linesArry[totalmoves] = lineD;}

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
        if(col1 < col2){
                grid[2*row1-2][2*col1-1] = 205;
                colorsgrid[2*row1-2][2*col1-1] = colors[totalmoves%2];}
        else if(col1 > col2){
                grid[2*row1-2][2*col2-1] = 205;
                colorsgrid[2*row1-2][2*col2-1] = colors[totalmoves%2];}
        // if it's vertical line
        if(row1 < row2){
                grid[2*row1-1][2*col1-2] = 186;
                colorsgrid[2*row1-1][2*col1-2] = colors[totalmoves%2];}
        else if(row1 > row2){
                grid[2*row2-1][2*col1-2] = 186;
                colorsgrid[2*row2-1][2*col1-2] = colors[totalmoves%2];}


        moves[totalmoves%2]++; // number of moves increase for the player 1 or 2
        totalmoves++;
        system("cls");

//--------------------------printing grid after each valid move------------------
              // columns rank before the grid
              printf("\n\n                                 ");
              for(int j = 0; j < m+1; j++){printf(cyan "%d.    " reset, j+1);}
              printf("\n\n");


              for(int i = 0;i < 2*n+1; i++){
                if(!(i%2))
                printf(cyan "                          %d.    " reset, i/2+1);  // rows rank left to the grid

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
        print_board(scores, moves);

    }


    // is line chosen ?
    /*
    for(int i = 0; i < totalmoves; i++){
           if( (linesArry[i].point1.row == lineD.point1.row || linesArry[i].point1.row == lineD.point2.row) &&
            (linesArry[i].point2.row == lineD.point1.row || linesArry[i].point1.row == lineD.point2.row) ){

                if( (linesArry[i].point1.col == lineD.point1.col || linesArry[i].point1.col == lineD.point2.col) &&
                (linesArry[i].point2.col == lineD.point1.col || linesArry[i].point1.col == lineD.point2.col) ){
                    lineAvlbe = 0;break;
                }

            }

        }
*/


  }


  if(scores[0] > scores[1])printf(red "          Player 1 is the WINNER!" reset);
  else if(scores[0] < scores[1])printf(blue "                   Player 2 is the WINNER!" reset);
  else printf(cyan "               It seems it's draw!" reset);

  return 0;

}
