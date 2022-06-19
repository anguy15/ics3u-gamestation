#include "hangman.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//globals

//functions
int playHangman()
{
  hangmanGameInfo hangmanInfo = {0};
  hangmanInfo.wordGenLen = chooseWord(&hangmanInfo);
  hangmanInfo.userCorrectCount=0;
  hangmanInfo.incorrectGuesses=0;
  setupCorrectGuesses(&hangmanInfo);

  switch (mainGame(&hangmanInfo))
  {
    case 0:
      printf("You lost");break;

    case 1:
      printf("You Won!");break;
  }
}

static int mainGame(hangmanGameInfo *hangmanInfo)
{
  int userGuessType;
  int inputFlag=0;
  char userGuessLetter;
  int userGuessLetterArr[50]={0};
  char userGuessWord[50];
  int winCond=0;

  //main game loop
  do
  {
    //reset flags
    userGuessType=-1;

    //user choices
    // get Guess Type
    do
    {
      drawGame(*hangmanInfo, userGuessLetterArr);
      if (inputFlag!=0)
      {
        printf("Invalid Guess Type\n\n");
      }

      printf("1. Letters\n2. Word\n");
      printf("Which Guess Type: ");
      scanf("%i", &userGuessType);
      clearInput();
      
    }while(userGuessType<0||userGuessType>2);

    //get guess
    switch (userGuessType)
    {
      case 1://letter
        userGuessLetter = getGuessLetter(hangmanInfo, userGuessLetterArr);
        //incorrect
        if (checkCorrectGuess(hangmanInfo, userGuessLetter) == 0)
        {
          hangmanInfo->incorrectGuesses++;
        }
        break;
      
      case 2://word
        getGuessWord(hangmanInfo, userGuessLetterArr, userGuessWord);
        if (compareStrCaseI(hangmanInfo->wordGen,userGuessWord)==0)
        {
          drawGame(*hangmanInfo, userGuessWord);
          return(1);//player won
        }
          //incorrect
        else
          hangmanInfo->incorrectGuesses++;
        break;
    }
    //check if the user won
    if (strcmp(hangmanInfo->wordGen,hangmanInfo->wordGenCorrect)==0)
    {
      drawGame(*hangmanInfo, userGuessLetterArr);
      return(1);//player won
    }

    //debugs
    // for(int x=0; x<26; x++)
    //   printf("%i", userGuessLetter[x]);
    // printf("\n%s", userGuessWord);getchar();
    
    drawGame(*hangmanInfo, userGuessLetterArr);
    
  }while(hangmanInfo->incorrectGuesses!=6);//7 incorrect guesses
  
  drawGame(*hangmanInfo, userGuessLetterArr);
  return(0);
}

static int checkCorrectGuess(hangmanGameInfo *hangmanInfo, char guessLetter)
{
  int check=0;
  //check if any letters match the word generated
  for (int x=0; x<strlen(hangmanInfo->wordGen); x++)
  {
    if (tolower(hangmanInfo->wordGen[x])==guessLetter)
    {
      //update the printed word generated
      hangmanInfo->wordGenCorrect[x] = hangmanInfo->wordGen[x];
      check=1;
    }
  }
  return check;
}

static int compareStrCaseI(char arr1[], char arr2[])
{
  //get the longer string
  int longer = strlen(arr1)>strlen(arr2) ? strlen(arr1) : strlen(arr2);
  for (int x=0; x<longer; x++)
  {
    //if they are not equal
    if(tolower(arr1[x])!=tolower(arr2[x]))
      return tolower(arr1[x])-tolower(arr2[x]);
  }
  return 0;
}

static char getGuessLetter(hangmanGameInfo *hangmanInfo, int userGuessLetterArr[])
{
  drawGame(*hangmanInfo, userGuessLetterArr);
  int inputFlag=0;
  char userLChoice=0;
  //loop until valid letter given, not already chosen
  do
  {
    if (userGuessLetterArr[userLChoice-97]!=0)
    {
      printf("Letter has been guessed before\n");
    }
    getInputMenuCHAR(65, 122, &userLChoice, "Which letter to guess??\n", "Invalid Guess Letter\n");
    userLChoice=tolower(userLChoice);
  }while(userGuessLetterArr[userLChoice-97]!=0);
  //make sure they havent inputted a previously guessed input

  //write choice to array
  userGuessLetterArr[userLChoice-97]=1;
  return userLChoice;
}

static void getGuessWord(hangmanGameInfo *hangmanInfo, int userGuessLetterArr[], char guessWord[])
{
  drawGame(*hangmanInfo, userGuessLetterArr);
  int inputFlag=0;
  char userWChoice[50]={0};
  //loop until word is possibly a valid word
  //regex says all english letters
  getInputMenuSTR("[a-zA-Z]*", &userWChoice, "Enter a Guess Word", "Invalid Guess Word\n");

  //write choice to array
  strcpy(guessWord, userWChoice);
}

static void setupCorrectGuesses(hangmanGameInfo *hangmanInfo)
{
  for (int x=0; x<strlen(hangmanInfo->wordGen); x++)
  {
    hangmanInfo->wordGenCorrect[x]='_';
  }
}

static void drawGame(hangmanGameInfo hangmanInfo, int userGuessLetterArr[])
{
  const char hangmanBoard[7][64] = {
  {"  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n"}, 
  {"  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n"}, 
  {"  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n"}, 
  {"  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n"}, 
  {"  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n"}, 
  {"  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n"}, 
  {"  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n"}
  };
  system("clear");

  //print the gallow
  printf("%s", hangmanBoard[hangmanInfo.incorrectGuesses]);

  //print the amount guess from the word
  printf("%s\n", hangmanInfo.wordGenCorrect);

  //print the letters guessed
  for (int x=0; x<26; x++)
  {
    if (userGuessLetterArr[x]==1)
      printf("%c ", x+97);
  }
  
  printf("\n");
}

static int chooseWord(hangmanGameInfo *hangmanInfo)
{
  FILE *fp;
  fp = fopen("./games/hangman/hangmanList.txt", "r");
  struct wordList *HEAD = makeWordNode();
  struct wordList *CURR = HEAD;
  int x=0;

  if (fp==NULL)//file open error
  {
    printf("Could not open hangman file. File could be corrupt.\n");
    return;
  }
  else
  {
    while (!feof(fp))//read all words to list
    {
      fscanf(fp, "%s", CURR->word);
      x++;
      if(!feof(fp))//make new storage nodes
      {
        CURR->NEXT = makeWordNode();
        CURR=CURR->NEXT;
      }
      else//end of file
      {
        break;
      }
    }
  }

  //find random word from list
  CURR=HEAD;
  for (int y=0; y<x-rand()%x;y++)
  {
    CURR=CURR->NEXT;
  }

  //save generated word
  strcpy(hangmanInfo->wordGen, CURR->word);
  return strlen(hangmanInfo->wordGen);
}

static struct wordList *makeWordNode()
{
  struct wordList *NODE = malloc(sizeof(struct wordList));
  NODE->NEXT=NULL;
  NODE->word[0]=0;
  return(NODE);
}