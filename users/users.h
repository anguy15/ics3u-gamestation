#ifndef users_h
#define users_h

//    needed libraries
#include <stdio.h>
#include <stdlib.h>

//    variables
typedef struct
{
  int uid;
  char username[256];
  int usertype;
  char password[256];
}tempUserData;

//    prototypes

//    GLOBAL
//debugging
void printUserFile();

//return if logged in, and return the user id in userID[]
int login(int *userID);

//checks the user count
//return user count
int checkUserCount();

//    LOCAL
//returns 1 if it works
static int makeUserDB();

//return 1 if it is correct
static int checkPassword(char username[], char password[], int *uid);

//reads all usersdata to a struct
//returns a 0 if it fails, returns the amount read if it doesn't
static int readUsers(tempUserData readUsers[]);

//writes all users to database
//returns 1 if it works
static int writeUsers(tempUserData readUsers[], int userCount);

//return 1 if it works
//take type of user, 0,1,2, normal user,admin,super user
static int makeUser(int usertype, int *userID);

#endif