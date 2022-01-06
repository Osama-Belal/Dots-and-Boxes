#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


int saving(int x, int scores[], int moves[], int maxmoves, int chosenrows[], int chosencols[]){


    FILE *fp;

    char* file_name;
    if(x == 1){file_name = "save_file_1.text";}
    if(x == 2){file_name = "save_file_2.text";}
    if(x == 3){file_name = "save_file_3.text";}

    fp = fopen(file_name, "w");


    if (fp == NULL){printf("ERROR: can\'t open file\n");return 0;}

    //f = fopen("save_file_1.text", "w");
    //fseek(f, 0, SEEK_SET);

    //print_board(scores, moves, maxmoves);

    fprintf(fp, "Player 1's score = %d, Player2's score = %d, Player 1's moves = %d, Player 2's moves = %d\n Remaining Moves = %d",
              scores[0], scores[1],
              moves[0], moves[1], maxmoves - moves[0] - moves[1]);

    fprintf(fp, "Chosen Rows: \n");
    for (int i = 0; i < maxmoves - moves[0] - moves[1]; i++){
            fprintf(fp, " %d ", chosenrows[i]);
    }

    fprintf(fp, "Chosen Columns: \n");
    for (int i = 0; i < maxmoves - moves[0] - moves[1]; i++){
            fprintf(fp, " %d ", chosencols[i]);
    }

    fclose(fp);
    return 0;

}

