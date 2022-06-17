#include "stats.h"
#include <stdio.h>

//functions

void printUserStats(userStats userStats[], userData currentUserData, int printType)
{
  system("clear");
  FILE *fp;
  fp = fopen("./data/games_stats", "r");
  int userCount=0;

  userCount = getUserCount();
  //required for getting userflags through ids
  userData tempUserData[userCount];

  printf("%i ", printType);
  if (fp == NULL)//file does not exist
  {
    getAllUsersData(tempUserData);
    //write for all users
    for (int x=0; x<userCount; x++)
    {
      //setup all variables as 0
      userStats[x].mathWins = 0;
      userStats[x].mathLosses = 0;
      userStats[x].tttWins = 0;
      userStats[x].tttLosses = 0;
      userStats[x].hangmanWins = 0;
      userStats[x].hangmanLosses = 0;
      userStats[x].uid = x;
      //setting a flag for if the user is a player, dependent on whether they are admin
      if (tempUserData[x].usertype==0)
      {
        userStats[x].playerFlag=1;
      }
      else
      {
        userStats[x].playerFlag=0;
      }

      writeStats(userStats, userCount);
      //read the new stats
      readStats(userStats);
    }
  }
  else if (printType==1)//print 1 user
  {

    printStatTable(currentUserData, userStats[currentUserData.uid], 0);
    //print stats for every game
    for (int x=1; x<=info_game_count; x++)
    {
      printStatTable(currentUserData, userStats[currentUserData.uid], x);
    }
  }
  else if (printType==0)//print all users
  {
    //read all file
    getAllUsersData(tempUserData);

    //printing header
    printStatTable(currentUserData, userStats[0], 0);//tempUserStats array index does not matter
    //printing all users, not admins
    for (int x=1; x<=info_game_count; x++)
    {
      //print all users
      for (int y=0; y<userCount; y++)
      {
        if (tempUserData[y].usertype==0)//0 means user
        {
          printStatTable(tempUserData[y], userStats[y], x);
        }
      }
    }
    //plans
    //make sorted index for <game>
    //print <game>
  }
}

void printAllStats(userStats userStats[], userData currentUserData)
{
  printUserStats(userStats, currentUserData, 0);
}

void addUserStats(userStats newUserStats[], userData newUserData, int userCount)
{
  newUserStats[userCount].uid=userCount;
  newUserStats[userCount].playerFlag=newUserData.usertype<1;
  newUserStats[userCount].mathWins = 0;
  newUserStats[userCount].mathLosses = 0;
  newUserStats[userCount].tttWins = 0;
  newUserStats[userCount].tttLosses = 0;
  newUserStats[userCount].hangmanWins = 0;
  newUserStats[userCount].hangmanLosses = 0;
  updateUserStats(newUserStats, userCount+1);
}

void updateUserStats(userStats newUserStats[], int userCount)
{
  //save stats
  writeStats(newUserStats, userCount);
  readStats(newUserStats);
}

static void printStatTable(userData currentUserData, userStats currentUserStats, int table)
{
  switch (table)
  {
    case 0:
      //header
      printf("\t%-20s%-10s%-10s\n", "Username", "Wins", "Losses");
      break;
    
    case 1:
      //hangman
      printf("\t%-20s%-10i%-10i\n", currentUserData.username, currentUserStats.hangmanWins, currentUserStats.hangmanLosses);
      break;
    
    case 2:
      //math
      printf("\t%-20s%-10i%-10i\n", currentUserData.username, currentUserStats.mathWins, currentUserStats.mathLosses);
      break;

    case 3:
      //tic tac toe
      printf("\t%-20s%-10i%-10i\n", currentUserData.username, currentUserStats.tttWins, currentUserStats.tttLosses);
      break;
  }
}

void getUserStats(userStats tempUserStats[])
{
  readStats(tempUserStats);
}

static int readStats(userStats tempUserStats[])
{
  FILE *fp;
  fp = fopen("./data/games_stats", "r");
  int x=0;

  if (fp == NULL)//setup a file if it does not exist
  {
    FILE *fptr;
    fptr = fopen("./data/games_stats", "w");
  
    fprintf(fptr, "0\n");
    
    fclose(fptr);
    return 0;
  }
  else//read entire file and save data
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
  FILE *fp = fopen("./data/games_stats", "w");
  int x=0;

  //write all stats
  while (x!=userCount)
  {
    //checking if the user has just been deleted
    if (allUserStats[x].playerFlag!=-1)
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
  }
  fclose(fp);
}
