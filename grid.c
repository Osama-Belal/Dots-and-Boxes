#include <stdio.h>
#include <stdlib.h>


int main() {
  
  int n, m;
  scanf("%d", &n);
  scanf("%d", &m);
  
  int grid[n+1][m+1];
  
  // borders
  for(int i = 0; i < n; i++){
    grid[0][i] = 1
  }
  
  for(int i = 0; i < n; i++){
    grid[i][0] = 1
  }
  
  for(int i = 0; i < n; i++){
    grid[n][i] = 1
  }
  
  for(int i = 0; i < n; i++){
    grid[i][m] = 1
  }
  
  // corners
  grid[0][0] = 2;grid[0][m] = 2;grid[n][0] = 2;grid[n][m] = 2;
  
  
  for(int i =1;i < n; i++){
    for(int j = 1; j < m; j++){
      grid[i][j] = 0;
    }
  }
  
  for(int i =1;i < n; i++){
    for(int j = 1; j < m; j++){
      printf("%d ", grid[i][j] = 0);
    }
    printf("\n");
  }
  
    return 0;
}
