#include "menu.h"
#include "users/stats.h"
#include "input_handler.h"
#include <stdio.h>

//  globals  //
userData *_userDataPtr;
userStats (*_userStatsPtr)[1000];
int *_userCountPtr;
int _originalUserCount;
const int _userCountOffset = 1;
//           //

//takes the data pointers to save
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
  //NEVER PASS _userCountOffset MORE THAN INIT
  userStats userStats[userCount+_userCountOffset];//IMPORTANT FOR NOT CRASHING WHEN ADDING USERS
  _originalUserCount=userCount;
  
  login(&userData, userStats);
  getUserData(&userData);
  getUserStats(userStats, userCount);

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
  int returning=0;

  do//main menu loops the choices
  {
    getInputMenuINT(1, 3+1, &adminChoice, "MAIN MENU:\n\n1. User Stats\n2. Edit Users\n3. Edit Your Account\n4. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");
    do//loops the function if asked for
    {
      switch (adminChoice)
      {
        case 1:
          returning=statsMenu();
          break;
        
        case 2:
          returning=editUsersMenu();
          break;
    
        case 3:
          editUser(*_userDataPtr, _userDataPtr->uid);
          returning=1;
          break;
  
        case 4:
          return;
      }
    }while(!returning);

    system("clear");
  }while(1);
}

static void userMenu()
{
  system("clear");
  int userChoice=0;
  int returning=0;
  
  do
  {
    getInputMenuINT(1, 3+1, &userChoice, "MAIN MENU:\n\n1. View Stats\n2. Play Games\n3. Edit Your Account\n4. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");

    do
    {
      //swap to game
      switch (userChoice)
      {
        case 1://print all users
          returning=statsMenu();
          break;
        
        case 2://play games
          returning=gameMenu();
          break;
    
        case 3://edit self
          editUser(*_userDataPtr, _userDataPtr->uid);
          returning=1;
          break;
  
        case 4:
          return;
      }
    }while(!returning);
    
    
    system("clear");
  }while(1);
}

static int gameMenu()
{
  system("clear");
  int gameChoice=0;
  int gameChoiceFlag=0;
  char exitChoice='n';
  int gameStat=0;
  
  
    getInputMenuINT(1, 3+1, &gameChoice, "\033[36mGAME MENU\033[0m:\n\n1. Hangman\n2. Math Quiz\n3. Tic-Tac-Toe\n4. Return\n\nWhich game would you like to play?\n", "Invalid Game\n");

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
        return(1);//we are exiting
    }
    
    updateUserStats(_userStatsPtr, *_userCountPtr);

    //get any typeable letter/char
    getInputMenuYN(&exitChoice, "\nDo you wish to exit the game menu?", "Invalid Input\n");
    system("clear");
  return(exitChoice)=='y';
}

static int statsMenu()
{
  system("clear");
  int userChoice=0;
  char exitChoice='n';
  userData chosenUserData;
  
    
  //you are admin
  if (_userDataPtr->usertype!=0)
  {
    getInputMenuINT(1, 3+1, &userChoice, "\033[32mSTATS MENU\033[0m:\n\n1. All User Stats\n2. User Stats\n3. Specific Game Stats\n4. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");
    //printing a specific user's stats
    if (userChoice == 2)
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
    //1 is not actually my stats
    //2 is not actually return, change it if necessary
    userChoice = userChoice==1 ? 2 : 4;
    //copy the user to a temp user to keep it consistent with printuserstats 
    chosenUserData.uid = _userDataPtr->uid;
    chosenUserData.usertype = _userDataPtr->usertype;
    strcpy(chosenUserData.username, _userDataPtr->username);
  }
  

  //swap to user
  switch (userChoice)
  {
    case 1://print all users for all games
      printAllStats(_userStatsPtr, *_userDataPtr);
      break;
    
    case 2://print a specific user's stats
      printUserStats(_userStatsPtr, chosenUserData, 1);
      break;
    
    case 3://print all users for a game
      printUserStats(_userStatsPtr, chosenUserData, 2);
      break;

    default:
      return(1);//we are exiting
  }

  //get any typeable letter/char
  getInputMenuYN(&exitChoice, "\nDo you wish to exit the stats menu?", "Invalid Input\n");
  system("clear");
  return(exitChoice)=='y';
}

static int editUsersMenu()
{
  system("clear");
  int userChoice=0;
  char exitChoice='n';
  char restartChoice='n';
  int adminType=0;
  userData allUserData[*_userCountPtr];
  
  getInputMenuINT(1, 3+1, &userChoice, "\033[33mUSER MENU\033[0m:\n\n1. Add a User\n2. Edit User\n3. Remove User\n4. Return\n\nWhat would you like to do?\n", "Invalid Choice\n");

  //swap to game
  switch (userChoice)
  {
    case 1://add a user
      system("clear");
      getInputMenuINT(1,2, &adminType, "\033[33mADD USER\033[0m:\n\n1. Regular User\n2. Admin\n\nEnter an admin level: ", "Invalid user type\n");
      adminType--;
      (*_userCountPtr)++;
      addUser(_userStatsPtr, adminType);

      
      //if we are still able to run the program without smashing stack
      if (_originalUserCount+_userCountOffset!=(*_userCountPtr)-1)
      {
        getInputMenuYN(&restartChoice, "\033[33mADD USER\033[0m:\n\nRestarting is recommended for stability\nDo you wish to exit?", "Invalid Input\n");
      }
      else//exit to stop unexpected behaviour
      {
        printf("Restarting for stability\n\nPress Enter to Continue...");
        clearInput();//wait for input
        restartChoice='y';
      }

      
      if (restartChoice=='y')
        exit(0);
      else//user most likey wants to continue editing or adding users
        return(1);
      break;


    
    
    case 2://edit a user
      getAllUsersData(allUserData);
      printAllUsernames(allUserData, *_userCountPtr);
      editUser(*_userDataPtr, getUidInput());
      break;


    
    case 3://remove a user
      getAllUsersData(allUserData);
      printAllUsernames(allUserData, *_userCountPtr);
      removeUser(_userStatsPtr, getUidInput());
      break;


    
    case 4:
      return(1);//we are exiting
  }
  //get any typeable letter/char
  getInputMenuYN(&exitChoice, "\nDo you wish to exit the edit users menu?", "Invalid Input\n");
  
  system("clear");
  return(exitChoice)=='y';
}

static void printAllUsernames(userData userData[], int userCount)
{
  printf("\nUsers:\n");
  for (int x=0; x<userCount; x++)
  {
    printf("%s\n", userData[x].username);
  }
}

//finds and returns the id of a user based on a input
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