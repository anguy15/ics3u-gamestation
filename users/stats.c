#include "stats.h"

void readUserStats(userData userData)
{
  system("clear");
  FILE *fp;
  fp = fopen("./users/games_stats", "r");
  int userCount=0;

  userCount = checkUserCount();
  //sets all data to zero
  userStats tempUserStats[userCount];

  if (fp == NULL)//file does not exist
  {
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
      
      writeStats(tempUserStats, userCount+1);
    }
  }
  else//found the file
  {
    //read all stats
    readStats(tempUserStats);

    //print specific user stats 
    //math
    printf("Math Quiz:\n\t%-20s%-10s%-10s\n", "Username", "Wins", "Losses");
    printf("\t%-20s%-10i%-10i\n", userData.username, tempUserStats[userData.uid].mathWins, tempUserStats[userData.uid].mathLosses);
    //tic tac toe
    printf("Tic-Tac-Toe:\n\t%-20s%-10s%-10s\n", "Username", "Wins", "Losses");
    printf("\t%-20s%-10i%-10i\n", userData.username, tempUserStats[userData.uid].tttWins, tempUserStats[userData.uid].tttLosses);
    //hangman
    printf("Hangman:\n\t%-20s%-10s%-10s\n", "Username", "Wins", "Losses");
    printf("\t%-20s%-10i%-10i\n", userData.username, tempUserStats[userData.uid].hangmanWins, tempUserStats[userData.uid].hangmanLosses);
  }
}

void updateStats(userData newUserData)
{
  int userCount = checkUserCount();
<<<<<<< Updated upstream
  userData userData[userCount];
  getUserInfo(userData);
  
  strcpy(userData[newUserData.uid].username,newUserData.username);
  userData[newUserData.uid].uid,newUserData.uid;
  userData[newUserData.uid].usertype=newUserData.usertype;
  
=======
  userStats userData[userCount];
  readStats(userData);

  //setup new stats
  //math
  userData[newUserData.uid].mathWins=newUserData.mathWins;
  userData[newUserData.uid].mathLosses=newUserData.mathLosses;
  
  //tic tac toe
  userData[newUserData.uid].tttWins=newUserData.tttWins;
  userData[newUserData.uid].tttLosses=newUserData.tttLosses;
  
  //hangman
  userData[newUserData.uid].hangmanWins=newUserData.hangmanWins;
  userData[newUserData.uid].hangmanLosses=newUserData.hangmanLosses;

  //save stats
>>>>>>> Stashed changes
  writeStats(userData, userCount);
}
      
static int readStats(userStats tempUserStats[])
{
  FILE *fp;
  fp = fopen("./users/games_stats", "r");
  int x=0;

  while (!feof(fp))
  {
    fscanf(fp, "%i", &tempUserStats[x].uid);
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
  return(x);
}

static void writeStats(userStats allUserStats[], int userCount)
{
  FILE *fp = fopen("./users/games_stats", "w");
  int x=0;

  //write all stats
  while (x!=userCount-1)
  {
    fprintf(fp, "%i ", allUserStats[x].uid);
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