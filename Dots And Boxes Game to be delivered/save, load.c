#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "playing.h"


 typedef struct players{
    char name[30];
    int color;
    int score;
}players;



void save(int x, int time_spent, players playersInfo[], int scores[], int moves[], int maxmoves, int chosenrows[], int chosencols[],
          int redorows[], int redocols[], int redocounter, int currentplaying, int n, int m, int grid[2*n+1][2*m+1], int colorsgrid[2*n+1][2*m+1]){

    FILE *fp;
    char* file_name;
    if(x == 1){file_name = "save_file_1.text";}
    if(x == 2){file_name = "save_file_2.text";}
    if(x == 3){file_name = "save_file_3.text";}

    fp = fopen(file_name, "w");
    printf("SAVING..........\n");

    if (fp == NULL){printf("ERROR: can\'t open file\n");return;}

    fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
      n, m, currentplaying,
      scores[0], moves[0],
      scores[1], moves[1],
      maxmoves, redocounter);

    for (int i = 0; i < moves[0] + moves[1]; i++){
            fprintf(fp, "%d,", chosenrows[i]);
    }

    fprintf(fp, "\n");
    for (int i = 0; i < moves[0] + moves[1]; i++){
            fprintf(fp, "%d,", chosencols[i]);
    }

    fprintf(fp, "\n");
    for (int i = 0; i < redocounter; i++){
            fprintf(fp, "%d,", redorows[i]);
    }

    fprintf(fp, "\n");
    for (int i = 0; i < redocounter; i++){
            fprintf(fp, "%d,", redocols[i]);
    }

    fprintf(fp, "\n");
    for(int i = 0; i < 2*n+1; i++){
        for(int j = 0; j < 2*m+1; j++){
            fprintf(fp, "%d,", grid[i][j]);
        }
    }

    fprintf(fp, "\n");
    for(int i = 0; i < 2*n+1; i++){
        for(int j = 0; j < 2*m+1; j++){
            fprintf(fp, "%d,", colorsgrid[i][j]);
        }
    }

    fprintf(fp, "\n%d", time_spent);

    fprintf(fp, "\n%s%s", playersInfo[0].name, playersInfo[1].name);

    fclose(fp);

    printf("\t\t\t File Saved in %s :)", file_name);
    Sleep(3000);
}

void load(int x, int* time_spent, players playersInfo[], int* maxmoves, int scores[], int moves[], int* currentplaying,
          int chosenrows[], int chosencols[], int redocols[], int redorows[], int* redocounter,
          int* n, int* m, int grid[2*(*n)+1][2*(*m)+1], int colorsgrid[2*(*n)+1][2*(*m)+1]){

    FILE *fp;
    char* file_name;
    if(x == 1){file_name = "save_file_1.text";}
    if(x == 2){file_name = "save_file_2.text";}
    if(x == 3){file_name = "save_file_3.text";}

    fp = fopen(file_name, "r");
    printf("Loading..........\n");

    if (fp == NULL){printf("ERROR: can\'t open file\n");return;}

    fseek(fp, 0, SEEK_SET);
    fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
      n, m, currentplaying,
      &scores[0], &moves[0],
      &scores[1], &moves[1], maxmoves, redocounter);

    for (int i = 0; i < moves[0] + moves[1]; i++){
            fscanf(fp, "%d,", &chosenrows[i]);
    }

    fscanf(fp, "\n");
    for (int i = 0; i < moves[0] + moves[1]; i++){
            fscanf(fp, "%d,", &chosencols[i]);
    }

    fscanf(fp, "\n");
    for (int i = 0; i < *redocounter; i++){
            fscanf(fp, "%d,", &redorows[i]);
    }

    fscanf(fp, "\n");
    for (int i = 0; i < *redocounter; i++){
            fscanf(fp, "%d,", &redocols[i]);
    }

    fscanf(fp, "\n");
    for(int i = 0; i < 2*(*n)+1; i++){
        for(int j = 0; j < 2*(*m)+1; j++){
            fscanf(fp, "%d,", &grid[i][j]);
        }
    }

    fscanf(fp, "\n");
    for(int i = 0; i < 2*(*n)+1; i++){
        for(int j = 0; j < 2*(*m)+1; j++){
            fscanf(fp, "%d,", &colorsgrid[i][j]);
        }
    }

    fscanf(fp, "\n");
    fscanf(fp, "%d\n", time_spent);

    fgets(playersInfo->name, 30, fp);
    fgets((playersInfo+1)->name, 30, fp);

    fclose(fp);

}

void loadNM(int x, int* n, int* m){

    FILE *fp;
    char* file_name;
    if(x == 1){file_name = "save_file_1.text";}
    if(x == 2){file_name = "save_file_2.text";}
    if(x == 3){file_name = "save_file_3.text";}

    fp = fopen(file_name, "r");
    printf("Loading..........\n");

    if (fp == NULL){printf("ERROR: can\'t open file\n");return;}
    fseek(fp, 0, SEEK_SET);
    fscanf(fp, "%d,%d", n, m);
    fclose(fp);

}


