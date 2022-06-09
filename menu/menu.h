#ifndef menu_h
#define menu_h

//NEVER USE RELATIVE PATHS
#include "../users/users.h"
#include "../users/admin_users.h"
#include "../users/stats.h"
//NEVER USE RELATIVE PATHS
#include "../users/users.h"
#include "../users/admin_users.h"
#include "../users/stats.h"

//  GLOBALS
void mainMenu(userData *userData, userStats *userStats);

//LOCALS
//all
  //read all stats
  //change self userData
  
    //admin
    void adminMenu(userData *userData, userStats *userStats);
    
    //user
    void userMenu(userData *userData, userStats *userStats);
      //game menu
      // static void gameMenu(userData *userData, userStats *userStats);
      //my stats

#endif