#ifndef tic_tac_toe_h
#define tic_tac_toe_h

#include <stdio.h>
#include <stdlib.h>

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

//  GLOBALS
//return who won
int playTicTacToe();

//LOCALS
//gets all inputs for one round, and places them in gameboard
//winflags are setup depending on the inputs, and player
static void getUserInputs(int gameBoard[3][3], int winFlags[2][3][3], int player);

//resets the board to 0
static void resetGameBoard(int gameBoard[3][3]);

//draws the current game board
static void drawGameBoard(const int board[3][3]);

//check if the win flags are finished
//return place of win
//or -1 if no win
static int checkWinFlags(const int winFlags[2][3][3]);

//a debug function which prints the values of win flags
static void printDebugWinFlags(const int winFlags[2][3][3]);

//checks if the coordinate given by inputs of the player are valid
static void checkUserPlacement(int board[3][3], int xCoord, int yCoord);

#endif