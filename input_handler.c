#include "input_handler.h"
#include <stdio.h>
#include <regex.h>

int checkRegex(char string[], char regexComp[])
{
  regex_t regex;
  int reti;

  //compile the compare
  reti = regcomp(&regex, regexComp, REG_EXTENDED);

  //compare
  reti = regexec(&regex, string, 0, NULL, 0);
  //free regex memory
  regfree(&regex);
  
  //return results
  if (!reti)//correct
  {
    printf("a");
    return(1);
  }
  else if (reti == REG_NOMATCH)//incorrect
  {
    printf("b");
    return(0);
  }
}


void getInputMenuINT(int max, int min, int *userChoice, char question[], char invalidChoice[])
{
  int userChoiceFlag=0;//flags are for invalid choices
  do
  {
    if (userChoiceFlag==1)
    {
      printf("%s", invalidChoice);
    }

    userChoiceFlag=0;
    
    printf("%s", question);
    scanf("%i", userChoice);
    clearInput();

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
      printf("%s", invalidChoice);
    }

    userChoiceFlag=0;
    
    printf("%s", question);
    scanf("%c", userChoice);
    clearInput();

    userChoiceFlag=1;
  }while((*userChoice<max||*userChoice>min));
}



void getInputMenuSTR(char regexCheck[], char userChoice[], char question[256], char invalidChoice[256])
{
  int userChoiceFlag=0;//flags are for invalid choices
  do
  {
    if (userChoiceFlag==1)
    {
      printf("%s", invalidChoice);
    }

    userChoiceFlag=0;
    
    printf("%s", question);
    scanf("%s", userChoice);
    clearInput();
    printf("%s\n", userChoice);

    userChoiceFlag=1;
  }while(!checkRegex(userChoice, regexCheck));
}