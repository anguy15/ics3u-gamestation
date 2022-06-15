#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//users
#include "users/users.h"

//game includes
#include "games/games.h"

//tools
#include "input_handler.h"

//menu
static void mainMenu(userData *userData, userStats userStats[]);

//LOCALS
//all
  //read all stats
  //change self userData
  
    //admin
    static void adminMenu(userData *userData, userStats userStats[]);
    
    //user
    static void userMenu(userData *userData, userStats userStats[]);
      //game menu
      static void gameMenu(userData *userData, userStats userStats[], int userCount);
      //my stats

int main(void) {
  srand(time(0));

  userData userData;
  userStats userStats[getUserCount()];
  login(&userData);
  getUserData(&userData);
  getUserStats(userStats);

  // debug
  // printf("%i %s %i", userData.uid, userData.username, userData.usertype);
  
  mainMenu(&userData, userStats);
  // addUser(0);
  // editUser(userData.uid);
  
  return(0);
}

static void mainMenu(userData *userData, userStats userStats[])
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

static void adminMenu(userData *userData, userStats userStats[])
{
  int adminChoice=0;
  getInputMenuINT(1, 5, &adminChoice, "1. All User Stats\n2. A User's Stats\n3. Edit Users\n4. Edit Your Account\n5. Add User\nWhat would you like to do?\n", "Invalid Choice\n");
  switch (adminChoice)
  {
    case 1://print all users
      printAllStats(*userData, userStats);
      break;
    
    case 2://print a specific user's stats
      printUserStats(*userData, userStats, 1);
      break;
    
    case 3:
      //edit users
      break;

    case 4://edit self
      editUser(userData->uid);
      break;

    case 5:
      addUser(0);
      break;
  }
}

static void userMenu(userData *userData, userStats userStats[])
{
  int userChoice=0;
  getInputMenuINT(1, 4, &userChoice, "1. All User Stats\n2. My Stats\n3. Play Games\n4. Edit Users\nWhat would you like to do?\n", "Invalid Choice\n");

  //swap to game
  switch (userChoice)
  {
    case 1://print all users
      printAllStats(*userData, userStats);
      break;
    
    case 2://print a specific user's stats
      printUserStats(*userData, userStats, 1);
      break;
    
    case 3://play games
      gameMenu(userData, userStats, getUserCount());
      break;

    case 4://edit self
      editUser(userData->uid);
      break;
  }
}

static void gameMenu(userData *userData, userStats userStats[], int userCount)
{
  int gameChoice=0;
  int gameChoiceFlag=0;
  char exitChoice='n';
  int gameStat=0;
  do
  {
    getInputMenuINT(1, 3, &gameChoice, "1. Hangman\n2. Math Quiz\n3. Tic-Tac-Toe\nWhich game would you like to play?\n", "Invalid Game\n");

    gameStat=0;
    //swap to game
    switch (gameChoice)
    {
      case 1:
        gameStat=playHangman();
        if (gameStat==1)
          userStats[userData->uid].hangmanWins++;
        else
          userStats[userData->uid].hangmanLosses++;
        break;
      
      case 2:
        gameStat=playMathQuiz();
        if (gameStat==1)
          userStats[userData->uid].mathWins++;
        else
          userStats[userData->uid].mathLosses++;
        break;
      
      case 3:
        gameStat=playTicTacToe();
        if (gameStat==1)
          userStats[userData->uid].tttWins++;
        else
          userStats[userData->uid].tttLosses++;
        break;
    }
    
    updateUserStats(userStats, userCount);

    printf("Press Enter to Continue ...");
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
