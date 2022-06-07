#include "tic-tac-toe.h"

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
  
  do
  {
    drawGameBoard(gameBoard);
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
    do
    {
      drawGameBoard(gameBoard);
      if (userFlags.XFlag!=0)
      {
        printf("Invalid Column\n\n");
      }
      userFlags.XFlag=0;
      
      printf("Which column would you like: ");
      scanf("%i", &userXChoice);
      getchar();
      
      userFlags.XFlag++;
    }while(userXChoice<1 || userXChoice>3);
    userXChoice--;

    //get row input
    do
    {
      drawGameBoard(gameBoard);
      if (userFlags.YFlag!=0)
      {
        printf("Invalid Row\n\n");
      }
      userFlags.YFlag=0;
      
      printf("Which row would you like: ");
      scanf("%i", &userYChoice);
      getchar();
      
      userFlags.YFlag++;
    }while(userYChoice<1 || userYChoice>3);
    userYChoice--;
    
    userFlags.InputFlag++;
  }while(gameBoard[userYChoice][userXChoice]!=0);
  
  //write valid inputs
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
        //draw row markers
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
      
      //formatting
      if (y!=2)//not the last column
      {
        printf(" | ");//column separators
      }
      else if(x!=0)//not the last line
      {
        //draw row separators
        printf("\n  ");
        for (int z=0; z<3; z++)
        {
          printf("---");//row separators
        }
        printf("\n");
      }
      else//draw column markers
      {
        printf("\n  ");
        for (int z=0; z<3; z++)
        {
          printf(" %i ",z+1);//numbers for grid
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