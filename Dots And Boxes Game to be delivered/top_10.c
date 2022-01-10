#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "playing.h"

#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define Background_Light_Red BACKGROUND_INTENSITY | BACKGROUND_RED
#define Background_Light_Blue BACKGROUND_GREEN | BACKGROUND_BLUE


void top_ten_list(){

    FILE *fp;
    char* file_name;
    file_name = "top_10_list.text";

    fp = fopen(file_name, "r");

    if (fp == NULL){printf("ERROR: can\'t open file\n");return;}
    char name[30];
    int score;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, 10);

    printf("\n\t\t\t\t===============================================");
    printf("\n\n\t\t\t\t\t\t Top 10 List\n");
    printf("\n\t\t\t\t===============================================\n\n\n");

    for(int i = 0; i < 10; i++){
     fgets(name, 30, fp);
     fscanf(fp, "%d\n", &score);
     SetConsoleTextAttribute(hOut, 14);
     printf("\t\t\t\t[%d]\t%d", i+1, score);
     printf("\t\t\t%s", name);

    }

    SetConsoleTextAttribute(hOut, FOREGROUND_WHITE); // resets the color

    fclose(fp);

    printf("\n\n\t\t\t Enter To Go Back To Main Menu :D\a");
    fgets(name, 30, stdin);

}


