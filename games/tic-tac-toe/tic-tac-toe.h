#ifndef math_quiz_h
#define math_quiz_h

#include <stdio.h>

//variables
typedef struct
{
  int XFlag, YFlag, InputFlag;//flags for user error messages
}userErrorFlags;

//  GLOBALS
void playTicTacToe();

//LOCALS
void getUserInputs(int gameBoard[3][3], int winFlags[2][8], int player);
void resetGameBoard(int gameBoard[3][3]);
void drawGameBoard(int board[3][3]);
void checkUserPlacement(int board[3][3], int xCoord, int yCoord);

#endif