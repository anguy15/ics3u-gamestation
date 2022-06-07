#ifndef math_quiz_h
#define math_quiz_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//  GLOBALS
//main game
//returns the win 1 or loss 0
int mathQuiz();

//LOCALS
//takes difficulty and quiz type
//returns score
static int quizGame(int difficulty, char gameMode);

#endif