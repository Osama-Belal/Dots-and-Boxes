#ifndef SAVING_H_INCLUDED
#define SAVING_H_INCLUDED

#include "save, load.c"

#endif // SAVING_H_INCLUDED

void save(int x, int time_spent, players playersInfo[], int scores[], int moves[], int maxmoves, int chosenrows[], int chosencols[],
          int redorows[], int redocols[], int redocounter, int currentplaying, int n, int m, int grid[2*n+1][2*m+1], int colorsgrid[2*n+1][2*m+1]);


void loadNM(int x, int* n, int* m);

void load(int x, int* time_spent, players playersInfo[], int* maxmoves, int scores[], int moves[], int* currentplaying,
          int chosenrows[], int chosencols[], int redocols[], int redorows[], int* redocounter,
          int* n, int* m, int grid[2*(*n)+1][2*(*m)+1], int colorsgrid[2*(*n)+1][2*(*m)+1]);
