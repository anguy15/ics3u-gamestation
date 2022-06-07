#include "hangman.h"

int playHangman()
{
  hangmanGameInfo hangmanInfo = {0};
  chooseWord(hangmanInfo);
  printf("%s", hangmanInfo.wordGen);

  do
  {
    getUserInputs(hangmanInfo);
    getchar();
  }while(1);
  // }while(gameEndCheck()==0 && turnCount!=5);
}

static void getUserInputs(hangmanGameInfo hangmanInfo)
{
  int userXChoice;
  int inputFlag=0;
  int userGuessLetter[50]={0};
  char userGuessWord[50];
  
  do
  {
    if (inputFlag!=0)
    {
      printf("Invalid Coordinate given, please try again\n\n");
    }

    //reset flags
    inputFlag=0;

    //user choices
    // get Guess Type
    do
    {
      if (!=0)
      {
        printf("Invalid Guess Type\n\n");
      }

      printf("1. Letters\n2. Word\n");
      printf("Which Guess Type: ");
      scanf("%i", &userXChoice);
      getchar();
      
    }while();

    //get guess
    // getGuessLetter(hangmanInfo, userGuessLetter);
    getGuessWord(hangmanInfo, userGuessLetter, userGuessWord);
    drawGame(hangmanInfo, userGuessLetter);
    
    // inputFlag++;
  }while(1);
}

static void getGuessLetter(hangmanGameInfo hangmanInfo, int userGuessLetter[])
{
  drawGame(hangmanInfo, userGuessLetter);
  int inputFlag=0;
  char userLChoice=0;
  do
  {
    if (inputFlag!=0)
    {
      printf("Invalid Guess Letter\n\n");
    }
    inputFlag=0;

    for (int x=0; x<26; x++)
    {
      if (userGuessLetter[x]==1)
      {
        printf("-%i-", x+97);
      }
    }
    
    printf("Which Letter: ");
    scanf("%c", &userLChoice);
    getchar();
    userLChoice = tolower(userLChoice);
    
    inputFlag++;
  }while(userGuessLetter[userLChoice-97]!=0 && userLChoice<97 && userLChoice>122);

  //write choice to array
  userGuessLetter[userLChoice-97]=1;
}

static void getGuessWord(hangmanGameInfo hangmanInfo, int userGuessLetter[], char guessWord[])
{
  drawGame(hangmanInfo, userGuessLetter);
  int inputFlag=0;
  char userWChoice[50]={0};
  
  do
  {
    if (inputFlag!=0)
    {
      printf("Invalid Guess Word\n\n");
    }
    inputFlag=0;

    for (int x=0; x<26; x++)
    {
      if (userGuessLetter[x]==1)
      {
        printf("-%i-", x+97);
      }
    }
    
    printf("Which Letter: ");
    scanf("%s", userWChoice);
    getchar();
    
    inputFlag++;
  }while(strlen(userWChoice)<1);

  //write choice to array
  strcpy(guessWord, userWChoice);
}

static void drawGame(hangmanGameInfo hangmanInfo, int userGuessLetter[])
{
  system("clear");
  
  for (int x=0; x<26; x++)
  {
    printf("%i ", userGuessLetter[x]);
  }
  printf("\n");
  
}

static void chooseWord(hangmanGameInfo hangmanInfo)
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
  strcpy(hangmanInfo.wordGen, CURR->word);
  hangmanInfo.wordGenLen = strlen(hangmanInfo.wordGen);
}

static struct wordList *makeWordNode()
{
  struct wordList *NODE = malloc(sizeof(struct wordList));
  NODE->NEXT=NULL;
  NODE->word[0]=0;
  return(NODE);
}