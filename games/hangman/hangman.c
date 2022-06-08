#include "hangman.h"

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
  
  // }while(gameEndCheck()==0 && turnCount!=5);
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
    if (inputFlag!=0)
    {
      printf("Invalid Coordinate given, please try again\n\n");
    }

    //reset flags
    inputFlag=0;
    userGuessType=-1;

    //user choices
    // get Guess Type
    do
    {
      drawGame(*hangmanInfo, userGuessLetter);
      if (inputFlag!=0)
      {
        printf("Invalid Guess Type\n\n");
      }

      printf("1. Letters\n2. Word\n");
      printf("Which Guess Type: ");
      scanf("%i", &userGuessType);
      getchar();
      
    }while(userGuessType<0);

    //get guess
    switch (userGuessType)
    {
      case 1://letter
        userGuessLetter = getGuessLetter(hangmanInfo, userGuessLetterArr);
        if (checkCorrectGuess(hangmanInfo, userGuessLetter) == 0)
        {
          hangmanInfo->incorrectGuesses++;
        }
        break;
      
      case 2://word
        getGuessWord(hangmanInfo, userGuessLetter, userGuessWord);
        if (strcmp(hangmanInfo->wordGen,userGuessWord)==0)
        {
          drawGame(*hangmanInfo, userGuessLetter);
          return(1);//player won
        }
        break;
    }
    //check if the user won
    if (strcmp(hangmanInfo->wordGen,hangmanInfo->wordGenCorrect)==0)
    {
      drawGame(*hangmanInfo, userGuessLetter);
      return(1);//player won
    }

    //debugs
    // for(int x=0; x<26; x++)
    //   printf("%i", userGuessLetter[x]);
    // printf("\n%s", userGuessWord);getchar();
    
    drawGame(*hangmanInfo, userGuessLetter);

    inputFlag++;
  }while(hangmanInfo->incorrectGuesses!=5);//5 incorrect guesses
  
  return(0);
}

static int checkCorrectGuess(hangmanGameInfo *hangmanInfo, char guessLetter)
{
  int check=0;
  for (int x=0; x<strlen(hangmanInfo->wordGen); x++)
  {
    if (tolower(hangmanInfo->wordGen[x])==guessLetter)
    {
      hangmanInfo->wordGenCorrect[x] = hangmanInfo->wordGen[x];
      check=1;
    }
  }
  return check;
}

static char getGuessLetter(hangmanGameInfo *hangmanInfo, int userGuessLetterArr[])
{
  drawGame(*hangmanInfo, userGuessLetterArr);
  int inputFlag=0;
  char userLChoice=0;
  //loop until valid letter given, not already chosen
  do
  {
    if (inputFlag!=0)
    {
      printf("Invalid Guess Letter\n\n");
    }
    inputFlag=0;
    
    printf("Which Letter: ");
    scanf("%c", &userLChoice);
    getchar();
    userLChoice = tolower(userLChoice);
    
    inputFlag++;
  }while(userGuessLetterArr[userLChoice-97]!=0 && userLChoice<97 && userLChoice>122);

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
  do
  {
    if (inputFlag!=0)
    {
      printf("Invalid Guess Word\n\n");
    }
    inputFlag=0;
    
    printf("Guess a Word: ");
    scanf("%s", userWChoice);
    getchar();
    
    inputFlag++;
  }while(strlen(userWChoice)<2);

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
  system("clear");
  
  printf("%s", hangmanInfo.wordGenCorrect);
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