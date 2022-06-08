#ifndef stats_h
#define stats_h

#include <stdio.h>
#include "users.h"

//variables
typedef struct
{
  int uid;
  //math
  int mathWins;
  int mathLosses;
  //tic-tac-toe
  int tttWins;
  int tttLosses;
  //hangman
  int hangmanWins;
  int hangmanLosses;
}userStats;

//  GLOBALS
//take user id
//outputs the user's stats
void readUserStats(userData userData);
//updates a specific user's stats
void updateUserStats(userData userData);

//  LOCALS
//reads all stats
//takes a struct to write stats to
static int readStats(userStats allUserStats[]);
//writes all stats
//takes stats struct, and amount of users
static void writeStats(userStats allUserStats[], int userCount);

#endif