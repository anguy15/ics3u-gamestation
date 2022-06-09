#include "menu.h"

void mainMenu(userData *userData, userStats *userStats)
{
  switch (userData->usertype)
  {
    case 0:
      userMenu(userData, userStats);
      break;

    case 1:
    case 2:
      adminMenu(userData, userStats);
      break;
  }
}

#include "admin_menu.h"

void adminMenu(userData *userData, userStats *userStats)
{
  printAllStats();
  //edit users
 
  //edit self
}

void userMenu(userData *userData, userStats *userStats)
{
  printAllStats();
  //mystats
  //games
  // gameMenu(userData, userStats);
  //edit self
}