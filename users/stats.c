#include "stats.h"

void readUserStats(int userID)
{
  FILE *fp;
  fp = fopen("./users/games_stats", "r");
  int userCount=0;

  userCount = checkUserCount()+1;
  //sets all data to zero
  userStats tempUserStats[userCount];

  if (fp == NULL)//file does not exist
  {
    //write for all users
    for (int x=0; x<userCount; x++)
    {
      tempUserStats[x].mathWins = 0;
      tempUserStats[x].mathLosses = 0;
      tempUserStats[x].userID = x;
      writeStats(tempUserStats, userCount);
    }
  }
  else//found the file
  {
    readStats(tempUserStats);
    for (int x=0; x<userCount; x++)
    {
      printf("%i, %i\n", tempUserStats[x].mathWins, tempUserStats[x].mathLosses);
    }
  }
}

void readStats(userStats tempUserStats[])
{
  FILE *fp;
  fp = fopen("./users/games_stats", "r");
  int x=0;

  while (!feof(fp))
  {
    fscanf(fp, "%i", &tempUserStats[x].userID);
    //math
    fscanf(fp, "%i", &tempUserStats[x].mathWins);
    fscanf(fp, "%i", &tempUserStats[x].mathLosses);

    if (feof(fp))
      break;
    
    x++;
  }
  fclose(fp);
  return(x);
}

void writeStats(userStats allUserStats[], int userCount)
{
  FILE *fp = fopen("./users/games_stats", "w");
  int x=0;
  
  while (x!=userCount-1)
  {
    fprintf(fp, "%i ", allUserStats[x].userID);
    fprintf(fp, "%i ", allUserStats[x].mathWins);
    fprintf(fp, "%i\n", allUserStats[x].mathLosses);
    x++;
  }
  fclose(fp);
}