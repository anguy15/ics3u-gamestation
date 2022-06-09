#include "stats.h"
#include <stdio.h>

//functions

void printUserStats(userData currentUserData, int printType)
{
  system("clear");
  FILE *fp;
  fp = fopen("./data/games_stats", "r");
  int userCount=0;

  userCount = getUserCount();
  //temporary storage for data prints
  userStats tempUserStats[userCount];
  //required for getting userflags through ids
  userData tempUserData[userCount];

  if (fp == NULL)//file does not exist
  {
    getAllUsersData(tempUserData);
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
  else if (printType==1)//print 1
  {
    //read all stats
    readStats(tempUserStats);

    printStatTable(currentUserData, tempUserStats[currentUserData.uid], 0);
    for (int x=1; x<=info_game_count; x++)
    {
      printStatTable(currentUserData, tempUserStats[currentUserData.uid], x);
    }
  }
  else if (printType==0)//print all
  {
    //read all file
    getAllUsersData(tempUserData);
    //read all stats
    readStats(tempUserStats);

    printStatTable(currentUserData, tempUserStats[0], 0);//tempUserStats array index does not matter
    for (int x=1; x<=info_game_count; x++)
    {
      printf("%i\n", x);
      for (int y=0; y<userCount; y++)
      {
        printStatTable(tempUserData[y], tempUserStats[y], x);
      }
    }
    //plans
    //make sorted index for <game>
    //print <game>
  }
}

void printAllStats(userData currentUserData)
{
  printUserStats(currentUserData, 0);
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
  userStats[newUserStats.uid].uid=newUserStats.uid;
  userStats[newUserStats.uid].playerFlag=newUserStats.playerFlag;
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
