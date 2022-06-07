#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//users
#include "users/users.h"
#include "users/stats.h"

//game includes
#include "games/math_quiz/math_quiz.h"
#include "games/tic-tac-toe/tic-tac-toe.h"

//prototypes

int main(void) {
  srand(time(0));
  int userID=0;
  
  // login(&userID);

  // menu
  
    // edit users//call users/users.h func
      // add
      // edit
      // delete
    
    // stats//call users/stats.h func
      // readUserStats(userID);
  
    // games//call game menu games/games.h
      // playTicTacToe();
      // playMathQuiz();
      playHangman();
  
  return(0);
}

