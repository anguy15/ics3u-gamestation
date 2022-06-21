#ifndef input_handler_h
#define input_handler_h

#include "users/users_info.h"

//globals
// static userData *_userDataPtr;
// static userStats (*_userStatsPtr)[1000];
// static int *_userCountPtr;

static int getUidInput();

//saves all data to public to menu var
static void constructor(userData *userData, userStats userStats[], int *userCount);

//prints all known usernames
static void printAllUsernames(userData userData[], int userCount);

void mainMenu();
//menu
static int statsMenu();
static int editUsersMenu();
  //admin
  static void adminMenu();
  //user
  static void userMenu();
    //game menu
    static int gameMenu();

#endif