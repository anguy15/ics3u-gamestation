#include "tic-tac-toe.h"
#include <stdio.h>

//variables
typedef struct
{
  int XFlag;
  int YFlag;
  int InputFlag;
}userErrorFlags;

typedef struct
{
  int winner;
  int type;
}winnerInformation;


//functions
int playTicTacToe()
{
  system("clear");
  int gameboard[3][3]={0};//[vertical pos][horizontal pos]
  
  //X: 0,1,2
  //Y: 0,1,2
  //diagonal: 0(top left),1(top right)
  //[player][x,y,d][type]
  int winFlags[2][3][3]={0};//flags for user wins
  winnerInformation winnerInfo;
  winnerInfo.type = -1;//setup the loop to detect when a winner has won
  
  resetGameBoard(gameboard);
  do
  {
    //run a full round
    for (int i=0; i<2; i++)
    {
      getUserInputs(gameboard, winFlags, i);
      
      winnerInfo.type = checkWinFlags(winFlags);//setup the win check
      if (winnerInfo.type!=-1)
      {
        winnerInfo.winner=i;
        break;
      }
    }
  }while(winnerInfo.type == -1);

  printf("Player %i won!", winnerInfo.winner+1);
  return winnerInfo.winner;
}

static void getUserInputs(int gameBoard[3][3], int winFlags[2][3][3], int player)
{
  int userXChoice, userYChoice;
  
  userErrorFlags userFlags;
  userFlags.XFlag = 0;
  userFlags.YFlag = 0;
  userFlags.InputFlag=0;

  //  get inputs  //
  do
  {
    drawGameBoard(gameBoard);
    printf("Player %i\n", player+1);
    if (userFlags.InputFlag!=0)
    {
      printf("Invalid Coordinate given, please try again\n\n");
    }

    //reset flags
    userFlags.XFlag = 0;
    userFlags.YFlag = 0;
    userFlags.InputFlag=0;

    //user choices
    //get column input
    drawGameBoard(gameBoard);
    getInputMenuINT(1,3, &userXChoice, "Which column would you like: ", "Invalid Column\n");
    userXChoice--;

    //get row input
    drawGameBoard(gameBoard);
    getInputMenuINT(1,3, &userYChoice, "Which row would you like: ", "Invalid row\n");
    userYChoice--;
    
    userFlags.InputFlag=1;
  }while(gameBoard[userYChoice][userXChoice]!=0);

  
  //  write valid inputs  //
  gameBoard[userYChoice][userXChoice]=player+1;
  
  //setup flags for x and y
  winFlags[player][0][userXChoice]++;
  winFlags[player][1][userYChoice]++;
  
  //setup flags from diagonals
  if ((userYChoice == 0 && userXChoice == 0) || (userYChoice == 2 && userXChoice == 2))
  {
    winFlags[player][2][1]++;//either corner connected with the top right diagonal
  }
  else if ((userYChoice == 0 && userXChoice == 2) || (userYChoice == 2 && userXChoice == 0))
  {
    winFlags[player][2][0]++;//either corner connected with the top left diagonal
  }
  else if ((userYChoice == 1 && userXChoice == 1))//center placed
  {
    winFlags[player][2][0]++;
    winFlags[player][2][1]++;
  }
}

static int checkWinFlags(const int winFlags[2][3][3])
{
  for (int x=0; x<2; x++)
  {
    for (int y=0; y<3; y++)
    {
      for (int t=0; t<3; t++)
      {
        if(winFlags[x][y][t]>=3)
        {
          return y;//true
        }
      }
    }
  }
  return -1;//false
}

static void printDebugWinFlags(const int winFlags[2][3][3])
{
  for (int x=0; x<2; x++)
  {
    for (int y=0; y<3; y++)
    {
      for (int t=0; t<3; t++)
      {
        printf("%i:%i  ",y,winFlags[x][y][t]);
      }
    }
    printf("\n");
  }
  getchar();
}

static void drawGameBoard(const int board[3][3])
{
  system("clear");
  for (int x=2; x>=0; x--)
  {
    for (int y=0; y<3; y++)
    {
      if (y==0)
      {
        //draw row numbers
        printf("%i ", x+1);
      }
      
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
      
      //formatting of walls and rows
      if (y!=2)//not the last column
      {
        printf(" | ");//column separators
      }
      else if(x!=0)//not the last line
      {
        printf("\n  ");
        for (int z=0; z<3; z++)
        {
          printf("---");//row separators
        }
        printf("\n");
      }
      else//draw column numbers
      {
        printf("\n  ");
        for (int z=0; z<3; z++)
        {
          printf(" %i ",z+1);//number columns
        }
      }
    }
  }
  printf("\n");
}

static void resetGameBoard(int gameBoard[3][3])
{
  for (int x=0; x<3; x++)
  {
    for (int y=0; y<3; y++)
    {
      gameBoard[x][y]=0;
    }
  }
}