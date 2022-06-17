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

  userData userData;
  userStats userStats[getUserCount()];
  login(&userData, userStats);
  int userCount = getUserData(&userData);
  getUserStats(userStats);

  // debug
  // printf("%i %s %i", userData.uid, userData.username, userData.usertype);
  
  mainMenu(&userData, userStats, &userCount);
  
  return(0);
}


void clearInput()
{
  char buff;
  while (buff!='\n')
  {
    scanf("%c", &buff);
  }
}
