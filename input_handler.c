#include "input_handler.h"
#include <stdio.h>
#include <regex.h>

int checkRegex(char string[], char regexComp[])
{
  regex_t regex;
  int reti;

  //compile the compare
  reti = regcomp(&regex, regexComp, REG_EXTENDED);
  if (reti)
  {
    return(0);
  }

  //compare
  reti = regexec(&regex, string, 0, NULL, 0);
  //free regex memory
  regfree(&regex);
  
  //return results
  if (!reti)//correct
  {
    return(1);
  }
  else if (reti == REG_NOMATCH)//incorrect
  {
    return(0);
  }
  else
  {
    printf("Unexpected behavior\n");
    return(0);//error
  }
}

void getInputMenuYN(char *userChoice, char question[], char invalidChoice[])
{
  char newQuestion[strlen(question)+40];
  strcpy(newQuestion,question);
  strcat(newQuestion," \033[32my\033[0m/\033[31mn\033[0m\n");
  getInputMenuCHAR(65,122, userChoice, newQuestion, invalidChoice);
}

void getInputMenuINT(int max, int min, int *userChoice, char question[], char invalidChoice[])
{
  int userChoiceFlag=0;//flags are for invalid choices
  do
  {
    if (userChoiceFlag==1)
    {
      printMenuBar();
      printf("%s", invalidChoice);
    }

    userChoiceFlag=0;
    
    printf("%s", question);
    scanf("%i", userChoice);
    clearInput();//remove extra inputs

    userChoiceFlag=1;
  }while(*userChoice<max||*userChoice>min);
}

void getInputMenuCHAR(int max, int min, char *userChoice, char question[], char invalidChoice[])
{
  int userChoiceFlag=0;//flags are for invalid choices
  do
  {
    if (userChoiceFlag==1)
    {
      printMenuBar();
      printf("%s", invalidChoice);
    }

    userChoiceFlag=0;
    
    printf("%s", question);
    scanf("%c", userChoice);
    clearInput();//remove extra inputs

    userChoiceFlag=1;
     }while((*userChoice<max||*userChoice>min));
}



void getInputMenuSTR(char regexCheck[], char userChoice[], char question[], char invalidChoice[])
{
  printf("%s\n", question);
  int userChoiceFlag=0;//flags are for invalid choices
  do
  {
    if (userChoiceFlag==1)
    {
      printMenuBar();
      printf("%s", invalidChoice);
    }

    userChoiceFlag=0;

    scanf("%s", userChoice);
    clearInput();//remove extra inputs

    userChoiceFlag=1;
  }while(!checkRegex(userChoice, regexCheck));
}

void clearInput()
{
  char buff;
  while (buff!='\n')
  {
    scanf("%c", &buff);
  }
}

void printMenuBar()
{
  printf("\n");
  for (int x=0; x<40; x++)
    printf("-");
  printf("\n");
}