#include <stdio.h>
#include <stdlib.h>

int Mode(){
  int mode;
  printf("Choose mode:\nPlayer VS Player: 1");
  printf("\nPlayer VS Computer: 2");
  printf("\nFor multiple players (maximum 4 players): 3");
  scanf("%d", &mode);
  
  while(mode != 1 || mode != 2 || mode != 3){
    printf("Enter a valid number that represents meaningful mode :)");
    scanf("%c", &mode);
  }
  return mode;
}


int main() {
  
  int mode = Mode();
  
    return 0;
}
