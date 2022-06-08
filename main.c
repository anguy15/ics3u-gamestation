#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//users
#include "users/users.h"
#include "users/stats.h"

//game includes
#include "games/games.h"

//prototypes
void mainMenu(userData *userData);
void adminMenu(userData *userData);
void playerMenu(userData *userData);

int main(void) {
  srand(time(0));
  userData userData;
  
  login(&userData);

  // debug
  // printf("%i %s %i", userData.uid, userData.username, userData.usertype);

  mainMenu(&userData);
  
  return(0);
}

void mainMenu(userData *userData)
{
  switch (userData->usertype)
  {
    case 0:
      playerMenu(userData);
      break;

    case 1:
    case 2:
      adminMenu(userData);
      break;
  }
  
  
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

void adminMenu(userData *userData)
{
  //stats
  //edit users
  //add games
  //change password
}

void playerMenu(userData *userData)
{
  //stats
  //mystats
  //games
  //change password
}