#ifndef stats_h
#define stats_h
#include "users_info.h"

//  GLOBALS
//take user id
//outputs the user's stats
void readUserStats(userData userData);
//updates a specific user's stats
void updateUserStats(userStats userStats, int userCount);
//the function called by adduser to update stats file
//this function is the same as updateUserStats, and was placed here for readability
void addUserStats(userStats userStats, int userCount);

//prints add user stats
void printAllStats();

//  LOCALS
//reads all stats
//takes a struct to write stats to
static int readStats(userStats allUserStats[]);
//writes all stats
//takes stats struct, and amount of users
static void writeStats(userStats allUserStats[], int userCount);

#endif
