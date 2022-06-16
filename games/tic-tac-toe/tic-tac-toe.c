#include "tic-tac-toe.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//variables
typedef struct
{
  int winner;
  int type;
}winnerInformation;


//functions
int playTicTacToe()
{
  system("clear");
  int gameBoard[3][3]={0};//[vertical pos][horizontal pos]
  
  //X: 0,1,2
  //Y: 0,1,2
  //diagonal: 0(top left),1(top right)
  //[player][x,y,d][type]
  int winFlags[2][3][3]={0};//flags for user wins
  winnerInformation winnerInfo;
  winnerInfo.type = -1;//setup the loop to detect when a winner has won
  
  resetGameBoard(gameBoard);
  do
  {
    //run a full round
    for (int i=0; i<2; i++)
    {
      if (i==1)
      {
        getAiInputs(gameBoard, winFlags);
      }
      else
      {
        getUserInputs(gameBoard, winFlags, i);
      }

      //game over/draw check
      if (checkGameBoard(gameBoard)==1)
      {
        winnerInfo.type=-2;
        break;
      }
      
      //win check
      winnerInfo.type = checkWinFlags(winFlags);//setup the win check
      if (winnerInfo.type!=-1)
      {
        winnerInfo.winner=i;
        break;
      }
    }
  }while(winnerInfo.type == -1);

  drawGameBoard(gameBoard);
  if (winnerInfo.type == 0 || winnerInfo.type == 1)//someone won
  {
    printf("Player %i won!", winnerInfo.winner+1);
    return !winnerInfo.winner;//winner will be 0 or 1, 0 for player one. the stats will track if player one wins
  }
  else//draw
  {
    printf("Draw Game");
    return 0;
  }
}

static void getUserInputs(int gameBoard[3][3], int winFlags[2][3][3], int player)
{
  int userXChoice, userYChoice;
  
  int userInputFlag=0;

  //  get inputs  //
  do
  {
    drawGameBoard(gameBoard);
    if (userInputFlag!=0)
    {
      printf("Invalid Coordinate given, please try again\n\n");
    }
    userInputFlag=0;

    //user choices
    //get column input
    drawGameBoard(gameBoard);
    printf("Player %i\n", player+1);
    getInputMenuINT(1,3, &userXChoice, "Which column would you like: ", "Invalid Column\n");
    userXChoice--;

    //get row input
    drawGameBoard(gameBoard);
    printf("Player %i\n", player+1);
    getInputMenuINT(1,3, &userYChoice, "Which row would you like: ", "Invalid row\n");
    userYChoice--;
    
    userInputFlag=1;
  }while(gameBoard[userYChoice][userXChoice]!=0);

  
    //  write valid inputs  //
  gameBoard[userYChoice][userXChoice]=player+1;
  updateWinFlags(winFlags, userYChoice, userXChoice, player);
}

static void updateWinFlags(int winFlags[2][3][3], int userYChoice, int userXChoice, int player)
{
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
          return x;//return play number
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

static int checkGameBoard(int gameBoard[3][3])
{
  int spotPlacedCount=0;
  for (int x=0; x<3; x++)
  {
    for (int y=0; y<3; y++)
    {
      if (gameBoard[x][y]!=0)//spot was placed on
      {
        spotPlacedCount++;
      }
    }
  }
  if (spotPlacedCount!=9)//not all spots filled
  {
    return(0);
  }
  else//all spots filled
  {
    return(1);
  }
}


static void getAiInputs(int gameBoard[3][3], int winFlags[2][3][3])
{
  int board[3][3];
  int winCheck=0;
  int winSum=0;
  srand(time(0));

  int winningX=0, winningY=0, tempWinSum=0;


  //simulate
  while (winCheck!=1)//max random checks
  {
    //simulate al posibilities
    for (int posY=0; posY<3; posY++)
    {
      for (int posX=0; posX<3; posX++)
      {
        //copy the board to a temp board
        for (int x=0; x<3; x++)
        {
          for (int y=0; y<3; y++)
          {
            board[x][y]=gameBoard[x][y];
          }
        }
        tempWinSum = simulateAiGame(board, winFlags, posY, posX, 1);//ai sim won
        if (tempWinSum>winSum)
        {
          winSum=tempWinSum;
          winningX=posX;
          winningY=posY;
        }
      }
    }
    
    winCheck++;
  }
  
  //  write valid inputs  //
  gameBoard[winningY][winningX]=1+1;//player 2
  updateWinFlags(winFlags, winningY, winningX, 1);
}

static int simulateAiGame(int board[3][3], int winnerFlags[2][3][3], int firstY, int firstX, int player)
{
  int winFlags[2][3][3]={0};//flags for user wins
  int gameBoard[3][3]={0};
  int winSum=0;

  //copy the winflags to temp flags
  for (int x=0; x<2; x++)
  {
    for (int y=0; y<3; y++)
    {
      for (int z=0; z<3; z++)
      {
        winFlags[x][y][z]=winnerFlags[x][y][z];
      }
    }
  }
  //copy the board to a temp board
  for (int x=0; x<3; x++)
  {
    for (int y=0; y<3; y++)
    {
      gameBoard[x][y]=board[x][y];
    }
  }
  //base case
  if (checkGameBoard(gameBoard)==1 || checkWinFlags(winFlags)!=-1)
  {
    return(checkWinFlags(winFlags));
  }
  else
  {
    //this permutation does not exist
    if (gameBoard[firstY][firstX]!=0)
    {
      return(0);//return ai did not win
    }
    else//start the permutation
    {
      gameBoard[firstY][firstX]=player+1;
    }
    
    //  write valid inputs  //
    updateWinFlags(winFlags, firstY, firstX, player);
    
    player = !player;//swap players

    //get and return results
    for (int x=0; x<3; x++)
    {
      for (int y=0; y<3; y++)
      {
        winSum+=simulateAiGame(gameBoard, winFlags, x, y, player);
      }
    }
    return(winSum);
  }
}