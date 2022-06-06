#ifndef stats_h
#define stats_h

#include <stdio.h>

//variables
typedef struct
{
  int userID;
  //math
  int mathWins;
  int mathLosses;
  //tic-tac-toe
}userStats;

//  GLOBALS
//take user id
void readUserStats(int userID);
void readStats(userStats allUserStats[]);
void writeStats(userStats allUserStats[], int userCount);

//  LOCALS

#endif