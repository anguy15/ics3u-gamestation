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
  //set same id for stats as data
  userStats.uid = userData.uid;

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
  printAllStats(*userData);
  // printUserStats(*userData);
  //edit users
  //edit self
}

static void userMenu(userData *userData, userStats *userStats)
{
  printAllStats(*userData);
  // printUserStats(*userData);
  // gameMenu(userData, userStats);
  //edit self
}

static void gameMenu(userData *userData, userStats *userStats)
{
  int gameChoice=0;
  int gameChoiceFlag=0;
  do
  {
    if (gameChoiceFlag==1)
    {
      printf("Invalid Input\n");
    }

    gameChoiceFlag=0;
    
    printf("1. Hangman\n2. Math Quiz\n3. Tic-Tac-Toe\n");
    printf("Which game would you like to play?\n");
    scanf("%i", &gameChoice);
    clearInput();

    gameChoiceFlag=1;
  }while(gameChoice<1||gameChoice>3);

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