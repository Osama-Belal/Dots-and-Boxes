#include <stdio.h>
#include <stdlib.h>

void red(){printf("\033[1;31m");}
void yellow(){printf("\033[1;33m");}
void blue(){printf("\033[0;34m");}
void resetColor(){printf("\033[0m");}


void printGrid(int n, int m){

  for(int i = 0;i < n+1; i++){

      for(int j = 0; j < m+1; j++){
        printf("🞇");
        if(j < m){
        printf("  ― ");}
      }

    printf("\n");

    if(i < n){
      for(int j = 0; j < m+1; j++){
      printf(" ▏  ");
      }
    }
    

    printf("\n");

  }

}

char Mode(){
  char mode;
  yellow();
  printf("Choose mode \'b\' for beginner and \'e\' for expert");
  printf("\nAlso type \'c\' for choosing your special grid ");
  scanf("%c", &mode);
  resetColor();

  
  while(mode != 'b' && mode != 'c' && mode != 'e'){
    red();
    printf("Please enter a valid charachter that represents meaningful mode :)\n");
    scanf("%c", &mode);
    resetColor();
  }

  
  return mode;
}

int main() {
  
  int n, m, mode;
  
  mode = Mode();
  
  switch(mode){
  
      case 'b':n = 2; m = 2;break;  // Beginners get 2 X 2 grid
      case 'B':n = 2; m = 2;break;  // Beginners get 2 X 2 grid
      
      case 'e':n = 5; m = 5;break;  // Expertss get 5 X 5 grid
      case 'E':n = 5; m = 5;break;  // Expertss get 5 X 5 grid
      
      case 'c':
        printf("Grid is n X m boxes\n");
        printf("n: ");scanf("%d", &n);
        printf("m: ");scanf("%d", &m);break;
      case 'C':
        printf("Grid is n X m boxes\n");
        printf("n: ");scanf("%d", &n);
        printf("m: ");scanf("%d", &m);break;
      
  }
  
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


  
  // columns rank before the grid
  blue();printf("    ");
  for(int j = 0; j < m+1; j++){printf("%d. ", j+1);}
  printf("\n");
  resetColor();

  for(int i = 0;i < n+1; i++){

    blue();
    printf("%d.  ", i+1);  // rows rank left to the grid
    resetColor();

    for(int j = 0; j < m+1; j++){
      printf("%d  ", grid[i][j]);
    }
    printf("\n");
  }
  
    return 0;
}

