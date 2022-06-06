#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//users
#include "users/users.h"
#include "users/stats.h"

//game includes
#include "games/math_quiz/math_quiz.h"

//prototypes

int main(void) {
  srand(time(0));
  int userID=0;
  login(&userID);

  readUserStats(userID);
  
  //mathQuiz();
  
  return(0);
}

