#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//users
#include "users/users.h"

//game includes
#include "games/games.h"

//tools
#include "input_handler.h"
#include "menu.h"

int main(void) {
  srand(time(0));
  char userLeave=0;

  //main menu loop
  do
  {
    mainMenu();
    system("clear");
    
    getInputMenuCHAR(65,122, &userLeave, "Would you like to exit the program? y/n\n", "Invalid Input\n");
    
  }while(tolower(userLeave)!='y');
  
  return(0);
}