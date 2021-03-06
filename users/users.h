#ifndef users_h
#define users_h

//    needed libraries
#include "encryption/simple_crypt.h"
#include "users_info.h"
#include "stats.h"

//    prototypes

//    GLOBAL
//debugging
static void printUserFile();

//return an updated array of user data
void getAllUsersData(userData userData[]);
//return user data
int getUserData(userData *userData);

void removeUser(userStats userStats[], int uid);
//if you are adding a user, make a new larger array, data will be read for you
void addUser(userStats userStats[], int usertype);
void editUser(userData userData, int uid);
int getUserID(char username[], int uidReturn[]);

//return if logged in, and return the user id in userData.userID[]
int login(userData *currentUserData, userStats userStats[]);

//checks the user count
//return user count
int checkUserCount();

//    LOCAL

//return 1 if it is correct
static int checkLogin(tempUserData *tempUserData, char username[], char password[]);

//reads all usersdata to a struct
//returns a 0 if it fails, returns the amount read if it doesn't
static int readUsers(tempUserData readUsers[]);

//writes all users to database
//returns 1 if it works
static int writeUsers(tempUserData readUsers[], int userCount);

//return 1 if it works
//take type of user, 0,1,2, normal user,admin,super user
static int makeUser(int usertype);

#endif