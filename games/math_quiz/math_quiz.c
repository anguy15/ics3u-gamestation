#include "math_quiz.h"

void mathQuiz()
{
  system("clear");
  int gameMode=0;
  int difficulty=0;
  printf("Welcome to the Math Quiz\n");
  printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Division (rounded)\n");
  //get game mode
  printf("Which game mode would you like to play? ");
  scanf("%i", &gameMode);
  //get difficulty
  printf("\n1. Easy\n2. Medium\n3. Hard\nWhich difficulty? ");
  scanf("%i", &difficulty);

  switch (gameMode)
  {
    case 1:
      quizGame(difficulty, '+');
      break;
    case 2:
      quizGame(difficulty, '-');
      break;
    
    case 3:
      quizGame(difficulty, '*');
      break;
    case 4:
      quizGame(difficulty, '/');
      break;
  }
}

static int quizGame(int difficulty, char gameMode)
{
  int arrLen;
  int values[5];
  double answerExact=0;
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
  for (int x=0; x<arrLen; x++)
  {
    values[x] = rand()%(arrLen*arrLen)+1;
    //calculate answer depending on game mode
    switch (gameMode)
    {
      case '+':
        answerExact+=values[x];break;
      
      case '-':
        if (x==0)
          answerExact=values[x];
        else
          answerExact-=values[x];
        break;

      case '*':
        if (x==0)
          answerExact=values[x];
        else
          answerExact*=values[x];
        break;

      case '/':
        if (x==0)
          answerExact=values[x];
        else
          answerExact/=values[x];
        break;
    }
  }
  //round answers to int
  answerCheck = round(answerExact);
  
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
  }
  else
  {
    printf("You lost!\nThe answer was %i\n", answerCheck);
  }
}