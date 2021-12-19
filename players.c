#include <stdio.h>
#include <stdlib.h>

int Gameplay(){
  int gameplay;
  printf("Choose mode:\nPlayer VS Player: 1");
  printf("\nPlayer VS Computer: 2");
  printf("\nFor multiple players (maximum 4 players): 3\n");
  scanf("%d", &gameplay);
  
  while(gameplay != 1 || gameplay != 2 || gameplay != 3){
    printf("Enter a valid number that represents meaningful mode :)");
    scanf("%c", &gameplay);
  }
  return gameplay;
}


int main() {
  
  int gameplay = Gameplay();
  
    return 0;
}
