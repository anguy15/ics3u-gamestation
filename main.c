#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//users
#include "users/users.h"

//game includes
#include "games/games.h"

//tools
#include "input_handler.h"
// #include "menu.h"

static void mainMenu(userData *userData, userStats userStats[], int *userCount);
//menu
static void statsMenu(userData *userData, userStats userStats[], int *userCount);
static void editUsersMenu(userData *userData, userStats userStats[], int *userCount);
    //admin
    static void adminMenu(userData *userData, userStats userStats[], int *userCount);
    //user
    static void userMenu(userData *userData, userStats userStats[], int *userCount);
      //game menu
      static void gameMenu(userData *userData, userStats userStats[], int *userCount);

int main(void) {
  srand(time(0));

  userData userData;
  userStats userStats[getUserCount()];
  login(&userData, userStats);
  int userCount = getUserData(&userData);
  getUserStats(userStats);
  printf("%p ", userStats);getchar();

  // debug
  // printf("%i %s %i", userData.uid, userData.username, userData.usertype);
  
  mainMenu(&userData, userStats, &userCount);
  
  return(0);
}

static void mainMenu(userData *userData, userStats userStats[], int *userCount)
{
  switch (userData->usertype)
  {
    case 0:
      userMenu(userData, userStats, userCount);
      break;

    case 1:
    case 2:
      adminMenu(userData, userStats, userCount);
      break;
  }
}

static void adminMenu(userData *userData, userStats userStats[], int *userCount)
{
  int adminChoice=0;
  char exitChoice='n';

  do
  {
    getInputMenuINT(1, 5+1, &adminChoice, "1. All User Stats\n2. A User's Stats\n3. Edit Users\n4. Edit Your Account\n5. Add User\n6. Return\nWhat would you like to do?\n", "Invalid Choice\n");
    switch (adminChoice)
    {
      case 1://print all users
        printAllStats(userStats, *userData);
        break;
      
      case 2://print a specific user's stats
        printUserStats(userStats, *userData, 1);
        break;
      
      case 3:
        //edit users
        break;
  
      case 4://edit self
        editUser(userData->uid);
        break;
  
      case 5:
        addUser(0, userStats);
        break;

      case 6:
        return;
    }

    printf("\nPress Enter to Continue ...");
    getchar();
    //get any typeable letter/char
    system("clear");
    getInputMenuCHAR(65,122, &exitChoice, "Do you wish to exit? y/n\n", "Invalid Input\n");
  }while(tolower(exitChoice)!='y');
}

static void userMenu(userData *userData, userStats userStats[], int *userCount)
{
  int userChoice=0;
  char exitChoice='n';
  
  do
  {
    getInputMenuINT(1, 4+1, &userChoice, "1. All User Stats\n2. My Stats\n3. Play Games\n4. Edit Users\n5. Return\nWhat would you like to do?\n", "Invalid Choice\n");
  
    //swap to game
    switch (userChoice)
    {
      case 1://print all users
        printAllStats(userStats, *userData);
        break;
      
      case 2://print a specific user's stats
        printUserStats(userStats, *userData, 1);
        break;
      
      case 3://play games
        gameMenu(userData, userStats, userCount);
        break;
  
      case 4://edit self
        editUser(userData->uid);
        break;

      case 5:
        return;
    }

    printf("\nPress Enter to Continue ...");
    getchar();
    //get any typeable letter/char
    system("clear");
    getInputMenuCHAR(65,122, &exitChoice, "Do you wish to exit? y/n\n", "Invalid Input\n");
  }while(tolower(exitChoice)!='y');
}

static void gameMenu(userData *userData, userStats userStats[], int *userCount)
{
  int gameChoice=0;
  int gameChoiceFlag=0;
  char exitChoice='n';
  int gameStat=0;
  do
  {
    getInputMenuINT(1, 3+1, &gameChoice, "1. Hangman\n2. Math Quiz\n3. Tic-Tac-Toe\n4. Return\nWhich game would you like to play?\n", "Invalid Game\n");

    gameStat=0;
    //swap to game
    switch (gameChoice)
    {
      //hangman
      case 1:
        gameStat=playHangman();
        if (gameStat==1)
          userStats[userData->uid].hangmanWins++;
        else
          userStats[userData->uid].hangmanLosses++;
        break;

      //math
      case 2:
        gameStat=playMathQuiz();
        if (gameStat==1)
          userStats[userData->uid].mathWins++;
        else
          userStats[userData->uid].mathLosses++;
        break;

      //tic tac toe
      case 3:
        gameStat=playTicTacToe();
        if (gameStat==1)
          userStats[userData->uid].tttWins++;
        else
          userStats[userData->uid].tttLosses++;
        break;

      case 4:
        return;
    }
    
    updateUserStats(userStats, *userCount);

    printf("\nPress Enter to Continue ...");
    getchar();
    //get any typeable letter/char
    system("clear");
    getInputMenuCHAR(65,122, &exitChoice, "Do you wish to exit? y/n\n", "Invalid Input\n");
  }while(tolower(exitChoice)!='y');
}

void clearInput()
{
  char buff;
  while (buff!='\n')
  {
    scanf("%c", &buff);
  }
}
