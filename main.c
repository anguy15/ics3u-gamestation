#include <stdio.h>
#include <stdlib.h>

//users
#include "users/users.h"

//game includes
#include "games/games.h"

//tools
#include "input_handler.h"
#include "menu.h"

int main(void) {
  char userLeave=0;

  //main menu loop
  do
  {
    mainMenu();
    system("clear");
    
    getInputMenuYN(&userLeave, "Would you like to exit the program?", "Invalid Input\n");
    
  }while(tolower(userLeave)!='y');
  
  return(0);
}