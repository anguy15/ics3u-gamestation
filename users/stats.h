#ifndef stats_h
#define stats_h
#include "users_info.h"

//  GLOBAL CONST VARS
#define info_game_count 3

//  GLOBALS
//take user id
//outputs the user's stats
//3 cases: (<missing file>)|(printType)
//case 0: no file is found, make a file
//case 1: print one user
//case 2: print all users
void printUserStats(userData userData, userStats userStats[], int printType);
//outputs all user stats
void printAllStats(userData currentUserData, userStats userStats[]);
//updates a specific user's stats
void updateUserStats(userStats userStats[], int userCount);
//the function called by adduser to update stats file
//this function is the same as updateUserStats, and was placed here for readability
void addUserStats(userStats userStats[], int userCount);
//function to read all users to stats array, useful during overhauls of code, to transfer between styles of reads
void getUserStats(userStats tempUserStats[]);

//  LOCALS
//reads all stats
//takes a struct to write stats to
static int readStats(userStats allUserStats[]);
//writes all stats
//takes stats struct, and amount of users
static void writeStats(userStats allUserStats[], int userCount);

//prints a formatted table of a user given the user's data and stats, and the table to print
static void printStatTable(userData currentUserData, userStats currentUserStats, int table);

#endif
