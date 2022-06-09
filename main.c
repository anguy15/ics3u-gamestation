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

  userData userData;
  userStats userStats;
  login(&userData);
  //set same id for stats as data
  userStats.uid = userData.uid;

  // debug
  // printf("%i %s %i", userData.uid, userData.username, userData.usertype);

  // readUserStats(userData);

  // mainMenu(&userData, &userStats);
  addUser(0);

  return(0);
}

