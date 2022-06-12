#ifndef user_info_h
#define user_info_h

//    variables
//users
typedef struct
{
  int uid;
  char username[64];
  int usertype;
  char password[64];
}tempUserData;

typedef struct
{
  int uid;
  char username[64];
  int usertype;
}userData;

//stats
typedef struct
{
  int uid;
  int playerFlag;
  //math
  int mathWins;
  int mathLosses;
  //tic-tac-toe
  int tttWins;
  int tttLosses;
  //hangman
  int hangmanWins;
  int hangmanLosses;
}userStats;

#endif