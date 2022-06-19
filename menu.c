#include "menu.h"
#include "users/stats.h"
#include "input_handler.h"
#include <stdio.h>

//  globals  //
struct mainMenuVars
{
  userData *userDataPtr;
  userStats (*userStatsPtr)[1000];
  int *userCountPtr;
};
struct mainMenuVars MainMenu;
//           //

static void constructor(userData *userData, userStats userStats[], int *userCount)
{
  MainMenu.userDataPtr=userData;
  MainMenu.userStatsPtr=userStats;
  MainMenu.userCountPtr=userCount;
}

static void swapUserStatsArr(int changeNum)
{
  MainMenu.userStatsPtr=NULL;
  userStats userStats[(*MainMenu.userCountPtr)+changeNum];
  MainMenu.userStatsPtr=userStats;
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
  switch (MainMenu.userDataPtr->usertype)
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
        editUser(*MainMenu.userDataPtr, MainMenu.userDataPtr->uid);
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
        editUser(*MainMenu.userDataPtr, MainMenu.userDataPtr->uid);
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
    getInputMenuINT(1, 3+1, &gameChoice, "\033[36mGAME MENU\033[0m:\n\n1. Hangman\n2. Math Quiz\n3. Tic-Tac-Toe\n4. Return\n\nWhich game would you like to play?\n", "Invalid Game\n");

    gameStat=0;
    //swap to game
    switch (gameChoice)
    {
      //hangman
      case 1:
        gameStat=playHangman();
        if (gameStat==1)
          (*MainMenu.userStatsPtr)[MainMenu.userDataPtr->uid].hangmanWins++;
        else if (gameStat==0)
          (*MainMenu.userStatsPtr)[MainMenu.userDataPtr->uid].hangmanLosses++;
        break;

      //math
      case 2:
        gameStat=playMathQuiz();
        if (gameStat==1)
          (*MainMenu.userStatsPtr)[MainMenu.userDataPtr->uid].mathWins++;
        else if (gameStat==0)
          (*MainMenu.userStatsPtr)[MainMenu.userDataPtr->uid].mathLosses++;
        break;

      //tic tac toe
      case 3:
        gameStat=playTicTacToe();
        if (gameStat==1)
          (*MainMenu.userStatsPtr)[MainMenu.userDataPtr->uid].tttWins++;
        else if (gameStat==0)
          (*MainMenu.userStatsPtr)[MainMenu.userDataPtr->uid].tttLosses++;
        break;

      case 4:
        return;
    }
    
    updateUserStats(MainMenu.userStatsPtr, *MainMenu.userCountPtr);

    //get any typeable letter/char
    getInputMenuYN(&exitChoice, "\nDo you wish to exit the game menu?", "Invalid Input\n");
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
    if (MainMenu.userDataPtr->usertype!=0)
    {
      getInputMenuINT(1, 3+1, &userChoice, "\033[32mSTATS MENU\033[0m:\n\n1. User Stats\n2. All User Stats\n3. Specific Game Stats\n4. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");
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
      getInputMenuINT(1, 1+1, &userChoice, "\033[32mSTATS MENU\033[0m:\n\n1. My Stats\n2. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");
      //print all stats is part of admin
      //2 is not actually return, change it if necessary
      userChoice = userChoice==1 ? 1 : 4;
      //copy the user to a temp user to keep it consistent with printuserstats 
      chosenUserData.uid = MainMenu.userDataPtr->uid;
      chosenUserData.usertype = MainMenu.userDataPtr->usertype;
      strcpy(chosenUserData.username, MainMenu.userDataPtr->username);
    }
    
  
    //swap to game
    switch (userChoice)
    {
      case 1://print a specific user's stats
        printUserStats(MainMenu.userStatsPtr, chosenUserData, 1);
        break;
      
      case 2://print all users for all games
        printAllStats(MainMenu.userStatsPtr, *MainMenu.userDataPtr);
        break;
      
      case 3://print all users for all games
        printUserStats(MainMenu.userStatsPtr, chosenUserData, 2);
        break;

      default:
        return;
    }

    //get any typeable letter/char
    getInputMenuYN(&exitChoice, "\nDo you wish to exit the stats menu?", "Invalid Input\n");
    system("clear");
  }while(tolower(exitChoice)!='y');
}

static void editUsersMenu()
{
  system("clear");
  int userChoice=0;
  char exitChoice='n';
  int adminType=0;
  
  do
  {
    getInputMenuINT(1, 3+1, &userChoice, "\033[33mUSER MENU\033[0m:\n\n1. Add a User\n2. Edit User\n3. Remove User\n4. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");

    //swap to game
    switch (userChoice)
    {
      case 1:
        system("clear");
        getInputMenuINT(1,2, &adminType, "\033[33mEDIT USER\033[0m:\n\n1. Regular User\n2. Admin\n\nEnter an admin level: ", "Invalid user type\n");
        adminType--;
        (*MainMenu.userCountPtr)++;
        swapUserStatsArr(*MainMenu.userCountPtr);
        addUser(MainMenu.userStatsPtr, 0);
        break;
      
      case 2:
        editUser(*MainMenu.userDataPtr, getUidInput());
        break;
      
      case 3:
        removeUser(MainMenu.userStatsPtr, getUidInput());
        break;

      case 4:
        return;
    }
    //get any typeable letter/char
    getInputMenuYN(&exitChoice, "\nDo you wish to exit the edit users menu?", "Invalid Input\n");
    system("clear");
  }while(tolower(exitChoice)!='y');
}

static int getUidInput()
{
  int userChoice=0;
  char userChoiceStr[64];
  int uidMatches[*MainMenu.userCountPtr];
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
      getInputMenuINT(1, *MainMenu.userCountPtr, &userChoice, "Which user?\n", "Invalid Choice\n");
    }
    else if(uidMatchCount==1)
    {
      userChoice = uidMatches[0];
    }

    choiceFlag=1;
  }while(uidMatchCount==0);
  return(userChoice);
}