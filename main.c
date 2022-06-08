#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//users
#include "users/users.h"
#include "users/stats.h"

//game includes
#include "games/games.h"

//prototypes

int main(void) {
  srand(time(0));
  int userID=0;
  
  login(&userID);

  
  
  return(0);
}

void mainMenu(int userID)
{
  // switch (checkAdmin(userID))
  // {
  //   case 1:
  //     adminMenu();
  //     break;

  //   case 2:
  //     playerMenu();
  //     break;
  // }
  
  
  // menu
  
    // edit users//call users/users.h func
      // add
      // edit
      // delete
    
    // stats//call users/stats.h func
      // readUserStats(userID);
  
    // gamesmenu//call game menu games/games.h
      // playTicTacToe();
      // playMathQuiz();
      // playHangman();
}

void adminMenu(int userID)
{
  //stats
  //edit users
  //add games
  //change password
}

void playerMenu(int userID)
{
  //stats
  //mystats
  //games
  //change password
}