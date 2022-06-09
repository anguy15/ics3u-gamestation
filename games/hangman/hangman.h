#ifndef hangman_h
#define hangman_h

//variables
struct wordList
{
  struct wordlist *NEXT;
  char word[256];
};

typedef struct
{
  char wordGen[256];
  char wordGenCorrect[256];
  int wordGenLen;

  int userCorrectCount;
  int userCorrectGuesses[256];
  int incorrectGuesses;
}hangmanGameInfo;

//  GLOBAL
//returns loss or win
int playHangman();

//  LOCAL
//finds a random word from text file
static int chooseWord(hangmanGameInfo *hangmanInfo);

//makes a new word node
static struct wordList *makeWordNode();

//get user's inputs
//return win or loss
static int mainGame(hangmanGameInfo *hangmanInfo);
static char getGuessLetter(hangmanGameInfo *hangmanInfo, int userGuessLetterArr[]);
static void getGuessWord(hangmanGameInfo *hangmanInfo, int userGuessLetterArr[], char userGuessWord[]);
//checks inputs
//returns 0 for fail, 1 for correct
static int checkCorrectGuess(hangmanGameInfo *hangmanInfo, char guessLetter);

static void drawGame(hangmanGameInfo hangmanInfo, int userGuessLetterArr[]);
static void setupCorrectGuesses(hangmanGameInfo *hangmanInfo);

#endif