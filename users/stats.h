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
//outputs the user's stats
void readUserStats(int userID);
//reads all stats
//takes a struct to write stats to
int readStats(userStats allUserStats[]);
//writes all stats
//takes stats struct, and amount of users
void writeStats(userStats allUserStats[], int userCount);

//  LOCALS

#endif