#include "math_quiz.h"

int playMathQuiz()
{
  system("clear");
  int gameMode=0;
  int difficulty=0;
  printf("Welcome to the Math Quiz\n");
  printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n");
  //get game mode
  printf("Which game mode would you like to play? ");
  scanf("%i", &gameMode);
  //get difficulty
  printf("\n1. Easy\n2. Medium\n3. Hard\nWhich difficulty? ");
  scanf("%i", &difficulty);

  switch (gameMode)
  {
    case 1:
      return(quizGame(difficulty, '+'));
      break;
    case 2:
      return(quizGame(difficulty, '-'));
      break;
    
    case 3:
      return(quizGame(difficulty, '*'));
      break;
    case 4:
      return(quizGame(difficulty, '/'));
      break;
  }
}

static int quizGame(int difficulty, char gameMode)
{
  int arrLen;
  int values[5];
  int answerExact=0;
  int answerCheck=0;
  int userInput;

  //setup the difficulty
  switch (difficulty)
  {
    case 1:
      arrLen=2;
      break;
    
    case 2:
      arrLen=3;
      break;
    
    case 3:
      arrLen=5;
      break;
  }

  //calculate value
  for (int x=0; x<=arrLen; x++)
  {
    values[x] = rand()%(arrLen*arrLen)+1;
    //calculate answer depending on game mode
    switch (gameMode)
    {
      case '+'://get sum of all variables
        if (x!=arrLen)
        {
          answerExact+=values[x];
        }
        else if (x==arrLen)
        {
          answerCheck = answerExact;//for consistency with print
        }
        break;
      
      case '-'://start with a positive
        if (x==0)
          answerExact=values[x];
        else if (x==arrLen)//save for print
        {
          answerCheck = answerExact;
        }
        else//subtract from positive
          answerExact-=values[x];
        break;

      case '*':
        if (x==0)//set starting variable
          answerExact=values[x];
        else if (x==arrLen)//save variable
        {
          answerCheck = answerExact;
        }
        else//multiply to start
          answerExact*=values[x];
        break;

      case '/'://set first variable, becasue you cant do 0/var
        if (x==0)
          answerExact=values[x];
        else if (x==arrLen)//set multiple of all variables but the first as the first, and the first as the answer
        {
          answerCheck = values[0];
          values[0]=answerExact;
        }
        else//get the starting variable
          answerExact*=values[x];
        break;
    }
  }
  
  //print values
  for (int x=0; x<arrLen; x++)
  {
    if (x<arrLen-1)
      printf("%i %c ", values[x], gameMode);
    else
      printf("%i = ", values[x]);
  }

  //user inputs answer
  scanf("%i", &userInput);
  getchar();

  //check if they were correct
  if (userInput == answerCheck)
  {
    printf("You won!\n");
    return(1);
  }
  else
  {
    printf("You lost!\nThe answer was %i\n", answerCheck);
    return(0);
  }
}