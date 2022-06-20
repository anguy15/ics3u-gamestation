#include "users.h"
#include <stdio.h>
#include <stdlib.h>

//functions
int login(userData *currentUserData, userStats userStats[])
{
  system("clear");
  
  int userCount = getUserCount();
  char username[256];
  char password[256];
  char passwordFails=0;
  tempUserData tempUserData = {0};
  
  if (userCount == 0)//no user exists
  {
    addUser(userStats, 2);//make a admin user
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
        //fix the grammar
        //time(s)
        printf("Incorrect password or username\n%i time%s failed\n", passwordFails, passwordFails==1 ? "" : "s");
        printMenuBar();
      }

      //empty fields for regex, since we dont really care what they put
      //get username
      getInputMenuSTR("", username, "LOGIN:\n\nUsername: ", "");

      //get password
      system("clear");
      getInputMenuSTR("", password, "LOGIN:\n\nPassword: ", "");
      system("clear");
      
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

void removeUser(userStats userStats[], int uid)
{
  //update user file
  int userCount = getUserCount();
  tempUserData tempUserData[userCount];
  readUsers(tempUserData);

  //cant edit a su
  if (tempUserData[uid].usertype==2)
  {
    printf("Invalid user\n");
    return;
  }
  
  //setup write stats will check for a -1 when writing, and ignore the stat
  tempUserData[uid].usertype = -1;
  writeUsers(tempUserData, userCount-1);
  
  //update stats file
  //setup write stats will check for a -1 when writing, and ignore the stat
  userStats[uid].playerFlag = -1;
  
  updateUserStats(userStats, userCount);
}

void addUser(userStats userStats[], int usertype)
{
  //update user file
  int userCount = getUserCount();
  userData tempUserData;
  
  //add the new user
  makeUser(usertype);
  //get the user's data for later
  getUserData(&tempUserData);
  
  //update stats file
  if (userCount!=0)
    getUserStats(userStats, userCount);
  
  //setup add
  userStats[userCount].uid = userCount;
  userStats[userCount].playerFlag = (usertype==0);//if it is a player then playerflag is one
  //math
  userStats[userCount].mathWins = 0;
  userStats[userCount].mathLosses = 0;
  //tictactoe
  userStats[userCount].tttWins = 0;
  userStats[userCount].tttLosses = 0;
  //hangman
  userStats[userCount].hangmanWins = 0;
  userStats[userCount].hangmanLosses = 0;
  
  addUserStats(userStats, tempUserData, userCount);
}

void editUser(userData currentUserData, int uid)
{
  system("clear");
  //read all users to write to file later
  int userCount = getUserCount();
  tempUserData tempUserData[userCount];
  readUsers(tempUserData);

  //cant edit a su, unless it is su
  //editing admin, can only happen if you are you
  if (tempUserData[uid].usertype!=0 && (uid != currentUserData.uid))
  {
    printf("Invalid user\n");
    return;
  }
  
  int userChoice=0;
  int invalidInputFlag=0;
  
  //get user menu choice
  //you are admin
  if (currentUserData.usertype!=0)
  {
    getInputMenuINT(1,3+1, &userChoice, "\033[33mEDIT USER\033[0m:\n\n1. Username\n2. Password\n3. Admin Level\n4. Return\n\nWhat would you like to edit: ", "Invalid Choice\n");
  }
  //you are user
  else
  {
    getInputMenuINT(1,2+1, &userChoice, "\033[33mEDIT USER\033[0m:\n\n1. Username\n2. Password\n3. Return\n\nWhat would you like to edit: ", "Invalid Choice\n");
    //return is not actually 3, change it to 4 if needed
    userChoice = (userChoice==3) ? 4 : userChoice;
  }
  
  
  system("clear");
  
  //setup new data
  switch (userChoice)
  {
    case 1:
      //regex says [valid characters], 4 to 64 as min to max amount of characters
      //get a username, and put into tempUserData[uid.username]
      getInputMenuSTR("^[a-zA-Z0-9._]{4,64}$", tempUserData[uid].username, "\033[33mEDIT USER\033[0m:\n\nEnter a username (no spaces): ", "Invalid username\nUsername must be 4 to 64 characters\n");
      break;
    
    case 2:
      //regex says 4 letters at least, one letter and one number
      //get a password, and put into tempUserData[uid].password
      getInputMenuSTR("^([1-zA-Z0-1@.]{4,255})$", tempUserData[uid].password, "\033[33mEDIT USER\033[0m:\n\nEnter a password (no spaces): ", "Invalid username\nPassword must be 4-255 characters\n1 letter, and 1 number\n");
      encryptStr(tempUserData[uid].password);
      break;
    
    case 3:
      //get an admin type
      getInputMenuINT(1,2, &tempUserData[uid].usertype, "\033[33mEDIT USER\033[0m:\n\n1. Regular User\n2. Admin\n\nEnter an admin level: ", "Invalid user type\n");
      tempUserData[uid].usertype--;
      break;

    default:
      return;
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

int getUserData(userData *currentUserData)
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
  return userCount;
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

int getUserID(char username[], int uidReturn[])
{
  int userCount = getUserCount();
  tempUserData tempUserData[userCount];
  readUsers(tempUserData);
  int userFound=0;
  int y=0;
  
  for (int x=0; x<userCount; x++)
  {
    if (strcmp(tempUserData[x].username,username)==0)//if there is a username match
    {
      uidReturn[y] = tempUserData[x].uid;
      y++;
    }
  }
  
  return y;//usercount
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
  int y=0;

  fprintf(fp, "%i\n", userCount);
  while (x!=userCount)
  {
    //if the user has not been deleted
    if (userData[x].usertype!=-1)
    {
      //read uid
      // fprintf(fp, "%i ", userData[x].uid);
      fprintf(fp, "%i ", y);//uid counts up from 0, because thats easier
      //read username
      fprintf(fp, "%s ", userData[x].username);
      //read usertype
      fprintf(fp, "%i ", userData[x].usertype);
      //read password
      fprintf(fp, "%s\n", userData[x].password);
      y++;
    }
    else//if they have been the userCount is one less than it was, maybe leaving a user out
    {
      userCount++;
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
  //get a username, and put into tempUserData[uid.username]
  system("clear");
  getInputMenuSTR("^[a-zA-Z0-9._]{4,64}$", tempUserData[userCount].username, "\033[33mADD USER\033[0m:\n\nEnter a username (no spaces): ", "Invalid username\nUsername must be 4 to 64 characters\n");
  
  //regex says 4 letters at least, one letter and one number
  //get a password, and put into tempUserData[uid].password
  system("clear");
  getInputMenuSTR("^([1-zA-Z0-1@.]{4,255})$", tempUserData[userCount].password, "\033[33mADD USER\033[0m:\n\nEnter a password (no spaces): ", "Invalid username\nUsername must be at least 4-63 characters\n");
  system("clear");

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