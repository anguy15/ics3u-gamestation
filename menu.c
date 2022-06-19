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

void mainMenu()
{
  //login
  int userCount = getUserCount();
  userData userData;
  userStats userStats[userCount+10];
  
  login(&userData, userStats);
  getUserData(&userData);
  getUserStats(userStats);

  //save data for later
  constructor(&userData, userStats, &userCount);

  //start menu
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

  do
  {
    getInputMenuINT(1, 3+1, &adminChoice, "MAIN MENU:\n\n1. User Stats\n2. Edit Users\n3. Edit Your Account\n4. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");
    switch (adminChoice)
    {
      case 1:
        statsMenu();
        break;
      
      case 2:
        editUsersMenu();
        break;
  
      case 3:
        editUser(*_userDataPtr, _userDataPtr->uid);
        break;

      case 4:
        return;
    }

    system("clear");
  }while(1);
}

static void userMenu()
{
  system("clear");
  int userChoice=0;
  
  do
  {
    getInputMenuINT(1, 3+1, &userChoice, "MAIN MENU:\n\n1. View Stats\n2. Play Games\n3. Edit Your Account\n4. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");
  
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
        editUser(*_userDataPtr, _userDataPtr->uid);
        break;

      case 4:
        return;
    }
    
    system("clear");
  }while(1);
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
        else if (gameStat==0)
          (*_userStatsPtr)[_userDataPtr->uid].hangmanLosses++;
        break;

      //math
      case 2:
        gameStat=playMathQuiz();
        if (gameStat==1)
          (*_userStatsPtr)[_userDataPtr->uid].mathWins++;
        else if (gameStat==0)
          (*_userStatsPtr)[_userDataPtr->uid].mathLosses++;
        break;

      //tic tac toe
      case 3:
        gameStat=playTicTacToe();
        if (gameStat==1)
          (*_userStatsPtr)[_userDataPtr->uid].tttWins++;
        else if (gameStat==0)
          (*_userStatsPtr)[_userDataPtr->uid].tttLosses++;
        break;

      case 4:
        return;
    }
    
    updateUserStats(_userStatsPtr, *_userCountPtr);

    //get any typeable letter/char
    getInputMenuCHAR(65,122, &exitChoice, "\nDo you wish to exit the game menu? y/n\n", "Invalid Input\n");
    system("clear");
  }while(tolower(exitChoice)!='y');
}

static void statsMenu()
{
  system("clear");
  int userChoice=0;
  char exitChoice='n';
  userData chosenUserData;
  
  do
  {
    
    //you are admin
    if (_userDataPtr->usertype!=0)
    {
      getInputMenuINT(1, 3+1, &userChoice, "STATS MENU:\n\n1. User Stats\n2. All User Stats\n3. Specific Game Stats\n4. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");
      //printing a specific user's stats
      if (userChoice == 1)
      {
        //find that user's uid
        chosenUserData.uid=getUidInput();
        getUserData(&chosenUserData);
      }
    }
    //you are user
    else
    {
      getInputMenuINT(1, 1+1, &userChoice, "STATS MENU:\n\n1. My Stats\n2. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");
      //print all stats is part of admin
      //2 is not actually return, change it if necessary
      userChoice = userChoice==1 ? 1 : 4;
      //copy the user to a temp user to keep it consistent with printuserstats 
      chosenUserData.uid = _userDataPtr->uid;
      chosenUserData.usertype = _userDataPtr->usertype;
      strcpy(chosenUserData.username, _userDataPtr->username);
    }
    
  
    //swap to game
    switch (userChoice)
    {
      case 1://print a specific user's stats
        printUserStats(_userStatsPtr, chosenUserData, 1);
        break;
      
      case 2://print all users for all games
        printAllStats(_userStatsPtr, *_userDataPtr);
        break;
      
      case 3://print all users for all games
        printUserStats(_userStatsPtr, chosenUserData, 2);
        break;

      default:
        return;
    }

    //get any typeable letter/char
    getInputMenuCHAR(65,122, &exitChoice, "\nDo you wish to exit the stats menu? y/n\n", "Invalid Input\n");
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
        editUser(*_userDataPtr, getUidInput());
        break;
      
      case 3:
        removeUser(getUidInput(), _userStatsPtr);
        break;

      case 4:
        return;
    }
    //get any typeable letter/char
    getInputMenuCHAR(65,122, &exitChoice, "\nDo you wish to exit the edit users menu? y/n\n", "Invalid Input\n");
    system("clear");
  }while(tolower(exitChoice)!='y');
}

static int getUidInput()
{
  int userChoice=0;
  char userChoiceStr[64];
  int uidMatches[*_userCountPtr];
  int uidMatchCount=0;
  int choiceFlag=0;
  
  do
  {
    if (choiceFlag==1)
    {
      printf("Invalid User\n");
    }
    choiceFlag=0;
    
    getInputMenuSTR("", &userChoiceStr, "\nWhich User?\n", "");
  
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

    choiceFlag=1;
  }while(uidMatchCount==0);
  return(userChoice);
}