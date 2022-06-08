#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//users
#include "users/users.h"
#include "users/stats.h"

//game includes
#include "games/games.h"

//prototypes
//main menus
void mainMenu(userData *userData, userStats *userStats);
void adminMenu(userData *userData, userStats *userStats;
void playerMenu(userData *userData, userStats *userStats);

//menu
void gameMenu(userData *userData, userStats *userStats);

int main(void) {
  srand(time(0));
  
  userData userData;
  userStats userStats;
  login(&userData);
  userStats.uid = userData.uid;

  // debug
  // printf("%i %s %i", userData.uid, userData.username, userData.usertype);
  
  // readUserStats(userData);
  
  mainMenu(&userData, &userStats);
  
  return(0);
}

void mainMenu(userData *userData, userStats *userStats)
{
  switch (userData->usertype)
  {
    case 0:
      playerMenu(userData, userStats);
      break;

    case 1:
    case 2:
      adminMenu(userData, userStats);
      break;
  }
  
  
  // menu
  
    // edit users//call users/users.h func
      // add
      // edit
      // delete
    
    // stats//call users/stats.h func
      // readUserStats(uid);
  
    // gamesmenu//call game menu games/games.h
      // playTicTacToe();
      // playMathQuiz();
      // playHangman();
}

void adminMenu(userData *userData, userStats *userStats)
{
  //stats
  //edit users
  //add games
  //change password
}

void playerMenu(userData *userData, userStats *userStats)
{
  //stats
  //mystats
  //games
  gameMenu(userData, userStats);
  //change password
}