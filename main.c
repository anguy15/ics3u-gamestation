#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "users/users.h"

//game includes
#include "games/math_quiz/math_quiz.h"

//prototypes
void readStats(userID);

int main(void) {
  srand(time(0));
  int userID=0;
  login(&userID);

  readStats(userID);
  
  //mathQuiz();
  
  return(0);
}

void readStats(userID)
{
  FILE *fp;
  fp = fopen("games_stats", "r");

  if (fp == NULL)
  {
    
  }
}