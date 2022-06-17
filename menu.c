#include "menu.h"
#include "users/stats.h"
#include "input_handler.h"

//globals
static userData *_userDataPtr;
static userStats (*_userStatsPtr)[1000];
static int *_userCountPtr;

static void constructor(userData *userData, userStats userStats[], int *userCount)
{
  _userDataPtr=userData;
  _userStatsPtr=userStats;
  _userCountPtr=userCount;
}

void mainMenu(userData *userData, userStats userStats[], int *userCount)
{
  constructor(userData, userStats, userCount);
  
  switch (_userDataPtr->usertype)
  {
    case 0:
      userMenu();
      break;

    case 1:
    case 2:
      adminMenu();
      break;
  }
}

static void adminMenu()
{
  system("clear");
  int adminChoice=0;
  char exitChoice='n';

  do
  {
    getInputMenuINT(1, 3+1, &adminChoice, "MAIN MENU:\n\n1. View All User Stats\n2. Users\n3. Edit Your Account\n4. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");
    switch (adminChoice)
    {
      case 1://print all users
        printAllStats(_userStatsPtr, *_userDataPtr);
        break;
      
      case 2:
        editUsersMenu();
        break;
  
      case 3:
        editUser(_userDataPtr->uid);
        break;

      case 4:
        return;
    }

    printf("\nPress Enter to Continue ...");
    clearInput();//wait for enter key
    //get any typeable letter/char
    system("clear");
  }while(tolower(exitChoice)!='y');
}

static void userMenu()
{
  system("clear");
  int userChoice=0;
  char exitChoice='n';
  
  do
  {
    getInputMenuINT(1, 3+1, &userChoice, "MAIN MENU:\n\n1. View Stats\n2. Play Games\n3. Edit Users\n4. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");
  
    //swap to game
    switch (userChoice)
    {
      case 1://print all users
        statsMenu();
        break;
      
      case 2://play games
        gameMenu();
        break;
  
      case 3://edit self
        editUser(_userDataPtr->uid);
        break;

      case 4:
        return;
    }
    //get any typeable letter/char
    system("clear");
  }while(tolower(exitChoice)!='y');
}

static void gameMenu()
{
  system("clear");
  int gameChoice=0;
  int gameChoiceFlag=0;
  char exitChoice='n';
  int gameStat=0;
  do
  {
    getInputMenuINT(1, 3+1, &gameChoice, "GAME MENU:\n\n1. Hangman\n2. Math Quiz\n3. Tic-Tac-Toe\n4. Return\n\nWhich game would you like to play?\n", "Invalid Game\n");

    gameStat=0;
    //swap to game
    switch (gameChoice)
    {
      //hangman
      case 1:
        gameStat=playHangman();
        if (gameStat==1)
          (*_userStatsPtr)[_userDataPtr->uid].hangmanWins++;
        else
          (*_userStatsPtr)[_userDataPtr->uid].hangmanLosses++;
        break;

      //math
      case 2:
        gameStat=playMathQuiz();
        if (gameStat==1)
          (*_userStatsPtr)[_userDataPtr->uid].mathWins++;
        else
          (*_userStatsPtr)[_userDataPtr->uid].mathLosses++;
        break;

      //tic tac toe
      case 3:
        gameStat=playTicTacToe();
        if (gameStat==1)
          (*_userStatsPtr)[_userDataPtr->uid].tttWins++;
        else
          (*_userStatsPtr)[_userDataPtr->uid].tttLosses++;
        break;

      case 4:
        return;
    }
    
    updateUserStats(_userStatsPtr, *_userCountPtr);

    printf("\nPress Enter to Continue ...");
    clearInput();//wait for enter key
    //get any typeable letter/char
    system("clear");
    getInputMenuCHAR(65,122, &exitChoice, "Do you wish to exit the game? y/n\n", "Invalid Input\n");
  }while(tolower(exitChoice)!='y');
}

static void statsMenu()
{
  system("clear");
  int userChoice=0;
  char exitChoice='n';
  
  do
  {
    getInputMenuINT(1, 2+1, &userChoice, "STATS MENU:\n\n1. All User Stats\n2. My Stats\n3. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");
  
    //swap to game
    switch (userChoice)
    {
      case 1://print all users
        printAllStats(_userStatsPtr, *_userDataPtr);
        break;
      
      case 2://print a specific user's stats
        printUserStats(_userStatsPtr, *_userDataPtr, 1);
        break;

      case 3:
        return;
    }

    printf("\nPress Enter to Continue ...");
    clearInput();//wait for enter key
    //get any typeable letter/char
    system("clear");
  }while(tolower(exitChoice)!='y');
}

static void editUsersMenu()
{
  system("clear");
  int userChoice=0;
  char exitChoice='n';
  
  do
  {
    getInputMenuINT(1, 3+1, &userChoice, "USER MENU:\n\n1. Add a User\n2. Edit User\n3. Remove User\n4. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");

    //swap to game
    switch (userChoice)
    {
      case 1:
        addUser(0, _userStatsPtr);
        break;
      
      case 2:
        editUser(getUidInput());
        break;
      
      case 3:
        removeUser(getUidInput(), _userStatsPtr);
        break;

      case 4:
        return;
    }
    //get any typeable letter/char
    system("clear");
  }while(tolower(exitChoice)!='y');
}

static int getUidInput()
{
  int userChoice=0;
  char userChoiceStr[64];
  int uidMatches[*_userCountPtr];
  int uidMatchCount=0;
  
  do
  {
    getInputMenuSTR("", &userChoiceStr, "\nWhich User?\n", "Invalid User\n");
  
    //print all matches
    uidMatchCount = getUserID(userChoiceStr, uidMatches);
    
    if (uidMatchCount>1)
    {
      printf("%-10s %-10s\n", "uid", "username");
      for (int x=0; x<uidMatchCount; x++)
      {
        printf("%-10i %-10s\n", uidMatches[x], userChoiceStr);
      }
      getInputMenuINT(1, *_userCountPtr, &userChoice, "Which user?\n", "Invalid Choice\n");
    }
    else if(uidMatchCount==1)
    {
      userChoice = uidMatches[0];
    }
  }while(uidMatchCount==0);
  return(userChoice);
}