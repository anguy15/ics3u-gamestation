#include "tic-tac-toe.h"

void playTicTacToe()
{
  system("clear");
  char gameboard[3][3]={0};
  // reset game board
  resetGameBoard(gameboard);
  
  //X: 0,1,2
  //Y: 3,4,5
  //diagonal: 6,7
  int winFlags[2][8]={0};//flags for user wins
  
  do
  {
    //run a full round
    for (int i=1; i<=2; i++)
    {
      getUserInputs(gameboard, winFlags, i);
    }
  }while(1);
}

void getUserInputs(int gameBoard[3][3], int winFlags[2][8], int player)
{
  int userXChoice, userYChoice;
  userErrorFlags userFlags;
    userFlags.XFlag = 0;
    userFlags.YFlag = 0;
    userFlags.InputFlag=0;
  do
  {
    drawGameBoard(gameBoard);
    if (userFlags.InputFlag!=0)
    {
      printf("Invalid input given, please try again\n\n");
    }
    
    userFlags.XFlag = 0;
    userFlags.YFlag = 0;
    userFlags.InputFlag=0;

    //user choices
    do
    {
      if (userFlags.XFlag!=0)
      {
        printf("Invalid Input, please try again");
      }
      userFlags.XFlag=0;
      printf("Which column would you like: ");
      scanf("%i", &userXChoice);
      getchar();
      userFlags.XFlag++;
    }while(userXChoice<1 || userXChoice>3);
    userXChoice--;

    do
    {
      if (userFlags.YFlag!=0)
      {
        printf("Invalid Input, please try again");
      }
      userFlags.YFlag=0;
      printf("Which row would you like: ");
      scanf("%i", &userYChoice);
      getchar();
      userFlags.YFlag++;
    }while(userYChoice<1 || userYChoice>3);
    userYChoice--;
    
    userFlags.InputFlag++;
  }while(gameBoard[userXChoice][userYChoice]!=0);
  
  //write valid inputs
  gameBoard[userXChoice][userYChoice]=player;
  // winFlags[player-1][userXChoice]++;
  // winFlags[player-1][userYChoice+3]++;
}

void drawGameBoard(int board[3][3])
{
  system("clear");
  for (int x=0; x<3; x++)
  {
    for (int y=0; y<3; y++)
    {
      // print the played piece
      switch (board[x][y])
      {
        case 0:
          printf(" ");
          break;
        case 1:
          printf("X");
          break;
        case 2:
          printf("O");
          break;
      }
      
      //formatting
      if (y!=2)//not the last column
      {
        printf(" | ");//column separators
      }
      else if(x!=2)//not the last line
      {
        printf("\n");
        for (int z=0; z<3; z++)
        {
          printf("---");//row separators
        }
        printf("\n");
      }
    }
  }
  printf("\n");
}

void resetGameBoard(int gameBoard[3][3])
{
  for (int x=0; x<3; x++)
  {
    for (int y=0; y<3; y++)
    {
      gameBoard[x][y]=0;
    }
  }
}