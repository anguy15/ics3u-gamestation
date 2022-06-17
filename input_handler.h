#ifndef input_handler_h
#define input_handler_h

void clearInput();

//getting inputs
void getInputMenuINT(int max, int min, int *userChoice, char question[], char invalidChoice[]);
void getInputMenuCHAR(int max, int min, char *userChoice, char question[], char invalidChoice[]);
void getInputMenuSTR(char regexCheck[], char userChoice[], char question[], char invalidChoice[]);

//checks a string with regex
//returns 1 if match
static int checkRegex(char string[], char regexComp[]);
void printMenuBar();

#endif