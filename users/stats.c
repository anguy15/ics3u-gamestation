#include "stats.h"

void readUserStats(userData currentUserData)
{
  system("clear");
  FILE *fp;
  fp = fopen("./users/games_stats", "r");
  int userCount=0;

  userCount = getUserCount();
  //temporary storage for data prints
  userStats tempUserStats[userCount];
  //required for getting userflags through ids
  userData tempUserData[userCount];

  if (fp == NULL)//file does not exist
  {
    getAllUsersInfo(tempUserData);
    //write for all users
    for (int x=0; x<userCount; x++)
    {
      //setup all variables as 0
      tempUserStats[x].mathWins = 0;
      tempUserStats[x].mathLosses = 0;
      tempUserStats[x].tttWins = 0;
      tempUserStats[x].tttLosses = 0;
      tempUserStats[x].hangmanWins = 0;
      tempUserStats[x].hangmanLosses = 0;
      tempUserStats[x].uid = x;
      //setting a flag for if the user is a player, dependent on whether they are admin
      if (tempUserData[x].usertype==0)
      {
        tempUserStats[x].playerFlag=1;
      }
      else
      {
        tempUserStats[x].playerFlag=0;
      }

      writeStats(tempUserStats, userCount);
    }
  }
  else//found the file
  {
    //read all stats
    readStats(tempUserStats);

    //print specific user stats
    //math
    printf("Math Quiz:\n\t%-20s%-10s%-10s\n", "Username", "Wins", "Losses");
    printf("\t%-20s%-10i%-10i\n", currentUserData.username, tempUserStats[currentUserData.uid].mathWins, tempUserStats[currentUserData.uid].mathLosses);
    //tic tac toe
    printf("Tic-Tac-Toe:\n\t%-20s%-10s%-10s\n", "Username", "Wins", "Losses");
    printf("\t%-20s%-10i%-10i\n", currentUserData.username, tempUserStats[currentUserData.uid].tttWins, tempUserStats[currentUserData.uid].tttLosses);
    //hangman
    printf("Hangman:\n\t%-20s%-10s%-10s\n", "Username", "Wins", "Losses");
    printf("\t%-20s%-10i%-10i\n", currentUserData.username, tempUserStats[currentUserData.uid].hangmanWins, tempUserStats[currentUserData.uid].hangmanLosses);
  }
}

void addUserStats(userStats newUserStats, int userCount)
{
  updateUserStats(newUserStats, userCount+1);
}

void updateUserStats(userStats newUserStats, int userCount)
{
  userStats userStats[userCount];
  readStats(userStats);

  //setup new stats
  //math
  userStats[newUserStats.uid].mathWins=newUserStats.mathWins;
  userStats[newUserStats.uid].mathLosses=newUserStats.mathLosses;

  //tic tac toe
  userStats[newUserStats.uid].tttWins=newUserStats.tttWins;
  userStats[newUserStats.uid].tttLosses=newUserStats.tttLosses;

  //hangman
  userStats[newUserStats.uid].hangmanWins=newUserStats.hangmanWins;
  userStats[newUserStats.uid].hangmanLosses=newUserStats.hangmanLosses;

  //save stats
  writeStats(userStats, userCount);
}

void printAllStats()
{
  int userCount=getUserCount();
  userStats userStats[userCount];
  readStats(userStats);

  for (int x=0; x<userCount; x++)
  {
    printf("%i ", userStats[x].uid);
    //math
    printf("%i ", userStats[x].mathWins);
    printf("%i ", userStats[x].mathLosses);
    //tic tac toe
    printf("%i ", userStats[x].tttWins);
    printf("%i ", userStats[x].tttLosses);
    //hangman
    printf("%i ", userStats[x].hangmanWins);
    printf("%i\n",userStats[x].hangmanLosses);
  }
}

static int readStats(userStats tempUserStats[])
{
  FILE *fp;
  fp = fopen("./users/games_stats", "r");
  int x=0;

  if (fp == NULL)
  {
    FILE *fptr;
    fptr = fopen("./users/games_stats", "w");
  
    fprintf(fptr, "0\n");
    
    fclose(fptr);
    return 0;
  }
  else
  {
    while (!feof(fp))
    {
      fscanf(fp, "%i", &tempUserStats[x].uid);
      fscanf(fp, "%i", &tempUserStats[x].playerFlag);
      //math
      fscanf(fp, "%i", &tempUserStats[x].mathWins);
      fscanf(fp, "%i", &tempUserStats[x].mathLosses);
      //tic-tac-toe
      fscanf(fp, "%i", &tempUserStats[x].tttWins);
      fscanf(fp, "%i", &tempUserStats[x].tttLosses);
      //hangman
      fscanf(fp, "%i", &tempUserStats[x].hangmanWins);
      fscanf(fp, "%i", &tempUserStats[x].hangmanLosses);
  
      if (feof(fp))
        break;
  
      x++;
    }
    fclose(fp);
  }
  
  return(x);
}

static void writeStats(userStats allUserStats[], int userCount)
{
  FILE *fp = fopen("./users/games_stats", "w");
  int x=0;

  //write all stats
  while (x!=userCount)
  {
    fprintf(fp, "%i ", allUserStats[x].uid);
    fprintf(fp, "%i ", allUserStats[x].playerFlag);
    //math
    fprintf(fp, "%i ", allUserStats[x].mathWins);
    fprintf(fp, "%i ", allUserStats[x].mathLosses);
    //tic tac toe
    fprintf(fp, "%i ", allUserStats[x].tttWins);
    fprintf(fp, "%i ", allUserStats[x].tttLosses);
    //hangman
    fprintf(fp, "%i ", allUserStats[x].hangmanWins);
    fprintf(fp, "%i\n", allUserStats[x].hangmanLosses);
    x++;
  }
  fclose(fp);
}
