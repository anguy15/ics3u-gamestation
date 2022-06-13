#include "users.h"
#include <stdio.h>
#include <stdlib.h>

//functions
int login(userData *currentUserData)
{  
  system("clear");
  int userCount = getUserCount();
  char username[256];
  char password[256];
  char passwordFails=0;
  tempUserData tempUserData = {0};
  
  if (userCount == 0)//no user exists
  {
    addUser(2);//make a admin user
    currentUserData->uid=0;
    getUserData(currentUserData);
    
    return 0;
  }
  else//a user exists
  {
    //get login credentials
    do
    {
      system("clear");
      if (passwordFails!=0) 
      {
        printf("Incorrect password or username\n%i times failed\n", passwordFails);
      }
      //get username
      printf("Username: ");
      scanf("%s", username);
      clearInput();
  
      //get password
      printf("Password: ");
      scanf("%s", password);
      clearInput();
      
      passwordFails++;
    }while(checkLogin(&tempUserData, username, password)==0);//check the login

    //copy temp data to program data
    currentUserData->uid = tempUserData.uid;
    strcpy(currentUserData->username, tempUserData.username);
    currentUserData->usertype = tempUserData.usertype;
    
    return(1);
  }
  return(0);
}

void removeUser(int uid)
{
  //update user file
  int userCount = getUserCount();
  tempUserData tempUserData[userCount];
  userStats userStats;
  readUsers(tempUserData);
  
  //setup write stats will check for a -1 when writing, and ignore the stat
  tempUserData[uid].usertype = -1;
  writeUsers(tempUserData, userCount);
  
  //update stats file
  //setup write stats will check for a -1 when writing, and ignore the stat
  userStats.playerFlag = -1;
  
  updateUserStats(userStats, userCount);
}

void addUser(int usertype)
{
  //update user file
  userData tempUserData;
  userStats userStats;
  int userCount = getUserCount();
  //uid will indicate a number one more than current amount, therefore adding a user
  tempUserData.uid = userCount;
  
  //add the new user
  makeUser(usertype);
  //get the user's data for later
  getUserData(&tempUserData);
  
  //update stats file
  //setup add
  userStats.uid = userCount;
  userStats.playerFlag = (usertype==0);//if it is a player then playerflag is one
  //math
  userStats.mathWins = 0;
  userStats.mathLosses = 0;
  //tictactoe
  userStats.tttWins = 0;
  userStats.tttLosses = 0;
  //hangman
  userStats.hangmanWins = 0;
  userStats.hangmanLosses = 0;
  
  addUserStats(userStats, userCount);
}

void editUser(int uid)
{
  //read all users to write to file later
  int userCount = getUserCount();
  tempUserData tempUserData[userCount];
  readUsers(tempUserData);

  int userChoice=0;
  int invalidInputFlag=0;

  getInputMenuINT(1,3, &userChoice, "1. Username\n2. Password\n3. Admin Level\nWhat would you like to edit: ", "Invalid Choice\n");
  

  system("clear");
  //setup new data
  switch (userChoice)
  {
    case 1:
      //regex says [valid characters], 4 to 64 as min to max amount of characters
      getInputMenuSTR("^[a-zA-Z0-9._]{4,64}$", tempUserData[uid].username, "Enter a username (no spaces): ", "Invalid username\nUsername must be 4 to 64 characters\n");
      break;
    
    case 2:
      //regex says 4 letters at least, one letter and one number
      getInputMenuSTR("^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{4,}$", tempUserData[uid].username, "Enter a username (no spaces): ", "Invalid username\nUsername must be at least 4 characters\n1 letter, and 1 number\n");
      break;

    
    case 3:
      getInputMenuINT(1,2, &tempUserData[uid].usertype, "1. Regular User\n2. Admin\nEnter an admin level: ", "Invalid user type\n");
      tempUserData[uid].usertype--;
      break;
  }

  //save data
  writeUsers(tempUserData, userCount);
}

int getUserCount()
{
  FILE *fp;
  fp = fopen("./data/user_data", "r");
  int userCount;

  if (fp == NULL)//if file does not exist
  {
    FILE *fptr;
    fptr = fopen("./data/user_data", "w");
  
    fprintf(fptr, "0\n");
    
    fclose(fptr);
    return 0;
  }
  else//we find the user count
  {
    fscanf(fp, "%i", &userCount);
  }

  fclose(fp);
  return userCount;
}

void getAllUsersData(userData userData[])
{
  int userCount = getUserCount();
  tempUserData tempUserData[userCount];//required to bypass the password reads
  readUsers(tempUserData);
  for (int x=0; x<userCount; x++)
  {
    userData[x].uid=tempUserData[x].uid;
    strcpy(userData[x].username,tempUserData[x].username);
    userData[x].usertype=tempUserData[x].usertype;
  }
}

void getUserData(userData *currentUserData)
{
  int userCount = getUserCount();
  tempUserData tempUserData[userCount];
  readUsers(tempUserData);
  for (int x=0; x<userCount; x++)
  {
    if (x==currentUserData->uid)
    {
      strcpy(currentUserData->username,tempUserData[x].username);
      currentUserData->usertype=tempUserData[x].usertype;
    }
  }
}

static int checkLogin(tempUserData *currentUserData, char username[], char password[])
{
  int userCount = getUserCount();
  tempUserData tempUserData[userCount];
  readUsers(tempUserData);
  int userFound=0;
  
  //return whether the password was correct
  encryptStr(password);
  for (int x=0; x<userCount; x++)
  {
    if (strcmp(tempUserData[x].username,username)==0)//if there is a username match
    {
      if (strcmp(tempUserData[x].password, password)==0)//if there is a password match
      {
        currentUserData->uid = tempUserData[x].uid;
        currentUserData->usertype = tempUserData[x].usertype;
        strcpy(currentUserData->username, tempUserData[x].username);
        strcpy(currentUserData->password, tempUserData[x].password);
        return 1;
      }
    }
  }
  return 0;//no found user/password
}

static int readUsers(tempUserData userData[])
{
  FILE *fp;
  fp = fopen("./data/user_data", "r");
  int x=0;
  int numOfUsers;

  fscanf(fp, "%i", &numOfUsers);
  while (!feof(fp))
  {
    //read uid
    fscanf(fp, "%i", &userData[x].uid);
    //read username
    fscanf(fp, "%s", userData[x].username);
    //read usertype
    fscanf(fp, "%i", &userData[x].usertype);
    //read password
    fscanf(fp, "%s", userData[x].password);

    //dont x++ if feof
    if (feof(fp))
      break;
    
    x++;
  }
  fclose(fp);
  return(x);
}

static int writeUsers(tempUserData userData[], int userCount)
{
  FILE *fp;
  fp = fopen("./data/user_data", "w");
  int x=0;

  fprintf(fp, "%i\n", userCount);
  while (x!=userCount)
  {
    //if the user has not been deleted
    if (userData[x].usertype!=-1)
    {
      //read uid
      fprintf(fp, "%i ", userData[x].uid);
      //read username
      fprintf(fp, "%s ", userData[x].username);
      //read usertype
      fprintf(fp, "%i ", userData[x].usertype);
      //read password
      fprintf(fp, "%s\n", userData[x].password);
    }
    x++;
  }

  fclose(fp);
  return(x);
}

static int makeUser(int usertype)
{
  //storing temp data to write later
  //new usercount
  int userCount=getUserCount();
  tempUserData tempUserData[userCount+1];
  if (userCount != 0)//there are users
  {
    readUsers(tempUserData);
  }
  
  //setup uid and usertype
  tempUserData[userCount].uid = userCount;
  tempUserData[userCount].usertype = usertype;
  
  //setup username and password
  //regex says [valid characters], 4 to 64 as min to max amount of characters
  getInputMenuSTR("^[a-zA-Z0-9._]{4,64}$", tempUserData[uid].username, "Enter a username (no spaces): ", "Invalid username\nUsername must be 4 to 64 characters\n");
  
  //regex says 4 letters at least, one letter and one number
  getInputMenuSTR("^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{4,}$", tempUserData[uid].username, "Enter a username (no spaces): ", "Invalid username\nUsername must be at least 4 characters\n1 letter, and 1 number\n");


  encryptStr(tempUserData[userCount].password);

  //write all data back to file
  writeUsers(tempUserData, userCount+1);
  
  return(0);
}

//debugger
static void printUserFile()
{
  FILE *fp;
  fp = fopen("./data/user_data", "r");
  char temp[256];
  
  while (!feof(fp))
  {
    fscanf(fp, "%s", temp);
    if (!feof(fp))
      printf("%s\n", temp);
  }
  fclose(fp);
}