#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//users
#include "users/users.h"

//game includes
#include "games/games.h"

//prototypes

//tools
void clearInput();
void getInputMenuINT(int max, int min, int *userChoice, char question[256], char invalidChoice[256]);

//menu
static void mainMenu(userData *userData, userStats *userStats);

//LOCALS
//all
  //read all stats
  //change self userData
  
    //admin
    static void adminMenu(userData *userData, userStats *userStats);
    
    //user
    static void userMenu(userData *userData, userStats *userStats);
      //game menu
      static void gameMenu(userData *userData, userStats *userStats);
      //my stats

int main(void) {
  srand(time(0));

  userData userData;
  userStats userStats;
  login(&userData);
  getUserData(&userData);
  //set same id for stats as data
  userStats.uid = userData.uid;
  printf("%i",userData.usertype);

  // debug
  // printf("%i %s %i", userData.uid, userData.username, userData.usertype);
  
  mainMenu(&userData, &userStats);
  // addUser(0);
  // editUser(userData.uid);
  
  return(0);
}

static void mainMenu(userData *userData, userStats *userStats)
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

static void adminMenu(userData *userData, userStats *userStats)
{
  int adminChoice=0;
  getInputMenuINT(1, 4, &adminChoice, "1. User Stats\n2. Stats\n3. Play Games\n4. Edit Users\nWhat would you like to do?\n", "Invalid Choice\n");
  switch (adminChoice)
  {
    case 1://print all users
      printAllStats(*userData);
      break;
    
    case 2://print a specific user's stats
      printUserStats(*userData, 1);
      break;
    
    case 3:
      //edit users
      break;

    case 4://edit self
      editUser(userData->uid);
      break;
  }
}

static void userMenu(userData *userData, userStats *userStats)
{
  int userChoice=0;
  getInputMenuINT(1, 4, &userChoice, "1. User Stats\n2. Stats\n3. Play Games\n4. Edit Users\nWhat would you like to do?\n", "Invalid Choice\n");
  printf("%i", userChoice);getchar();

  //swap to game
  switch (userChoice)
  {
    case 1://print all users
      printAllStats(*userData);
      break;
    
    case 2://print a specific user's stats
      printUserStats(*userData, 1);
      break;
    
    case 3://play games
      gameMenu(userData, userStats);
      break;

    case 4://edit self
      editUser(userData->uid);
      break;
  }
}

static void gameMenu(userData *userData, userStats *userStats)
{
  int gameChoice=0;
  int gameChoiceFlag=0;
  getInputMenuINT(1, 3, &gameChoice, "1. Hangman\n2. Math Quiz\n3. Tic-Tac-Toe\nWhich game would you like to play?\n", "Invalid Game\n");

  //swap to game
  switch (gameChoice)
  {
    case 1:
      playHangman();
      break;
    
    case 2:
      playMathQuiz();
      break;
    
    case 3:
      playTicTacToe();
      break;
  }
}

void clearInput()
{
  char buff;
  while (buff!='\n')
  {
    scanf("%c", &buff);
  }
}

void getInputMenuINT(int max, int min, int *userChoice, char question[256], char invalidChoice[256])
{
  int userChoiceFlag=0;//flags are for invalid choices
  do
  {
    if (userChoiceFlag==1)
    {
      printf("%s", invalidChoice);
    }

    userChoiceFlag=0;
    
    printf("%s", question);
    scanf("%i", userChoice);
    clearInput();

    userChoiceFlag=1;
  }while((*userChoice)<max||(*userChoice)>min);
}