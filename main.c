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

  do
  {
    int userCount = getUserCount();
    userData userData;
    userStats userStats[userCount+10];
    login(&userData, userStats);
    getUserData(&userData);
    getUserStats(userStats);
    
    // debug
    // printf("%i %s %i", userData.uid, userData.username, userData.usertype);
    
    mainMenu(&userData, userStats, &userCount);

    system("clear");
    getInputMenuCHAR(65,122, &userLeave, "Would you like to leave? y/n\n", "Invalid Input\n");
  }while(tolower(userLeave)!='y');
  
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

