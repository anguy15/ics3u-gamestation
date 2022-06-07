#ifndef hangman_h
#define hangman_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//variables
typedef struct
{
  char wordGen[50];
  int wordGenLen;

  int userCorrectCount;
  int userCorrectGuesses[50];
}hangmanGameInfo;

struct wordList
{
  struct wordlist *NEXT;
  char word[50];
};

//  GLOBAL
//returns loss or win
int playHangman();

//  LOCAL
//finds a random word from text file
static int chooseWord(hangmanGameInfo hangmanInfo);

//makes a new word node
static struct wordList *makeWordNode();

//get user's inputs
static void getUserInputs(hangmanGameInfo hangmanInfo);
static void getGuessLetter(hangmanGameInfo hangmanInfo, int userGuessLetter[]);
static void getGuessWord(hangmanGameInfo hangmanInfo, int userGuessLetter[], char userGuessWord[]);

static void checkCorrectGuess(hangmanGameInfo hangmanInfo, int userGuessLetter[]);

static void drawGame(hangmanGameInfo hangmanInfo, int userGuessLetter[]);

#endif