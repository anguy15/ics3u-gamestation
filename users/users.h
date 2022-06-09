#ifndef users_h
#define users_h

//    needed libraries
#include <stdio.h>
#include <stdlib.h>
#include "encryption/simple_crypt.h"
#include "users_info.h"

//    prototypes

//    GLOBAL
//debugging
void printUserFile();

//return an updated array of user data
void getAllUsersInfo(userData userData[]);

//return user data
void getUserData(userData *userData);

//adds a user
void addUser(int usertype);

//edits a user given a userid
void editUser(int uid);

//return if logged in, and return the user id in userData.userID[]
int login(userData *userData);

//checks the user count
//return user count
int checkUserCount();

//    LOCAL
static void clearInput();

//return 1 if it is correct
static int checkPassword(tempUserData *tempUserData, char username[], char password[]);

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