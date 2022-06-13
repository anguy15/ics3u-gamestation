#ifndef input_handler_h
#define input_handler_h

void clearInput();

//getting inputs
void getInputMenuINT(int max, int min, int *userChoice, char question[256], char invalidChoice[256]);
void getInputMenuCHAR(int max, int min, char *userChoice, char question[256], char invalidChoice[256]);
void getInputMenuSTR(char regexCheck[], char userChoice[], char question[256], char invalidChoice[256]);

//checks a string with regex
static int checkRegex(char string[], char regexComp[]);

#endif