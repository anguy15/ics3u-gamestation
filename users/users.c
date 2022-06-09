#include "users.h"

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
    do
    {
      system("clear");
      if (passwordFails!=0) 
      {
        printf("%i times failed\n", passwordFails);
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
    }while(checkPassword(&tempUserData, username, password)==0);

    //copy temp data to program data
    currentUserData->uid = tempUserData.uid;
    strcpy(currentUserData->username, tempUserData.username);
    currentUserData->usertype = tempUserData.usertype;
    
    
  
    return(1);
  }
  return(0);
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
  userStats.playerFlag = (usertype==0);//if it is a play then playerflag is one
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
  //get new data
  printf("1. Username\n2. Password\n3. Admin Level\n");
  printf("What would you like to edit: ");
  scanf("%i", &userChoice);

  system("clear");
  //setup new data
  switch (userChoice)
  {
    case 1:
      printf("Enter a username (no spaces): ");
      scanf("%s", tempUserData[uid].username);
      clearInput();
      break;
    
    case 2:
      printf("Enter a password (no spaces): ");
      scanf("%s", tempUserData[uid].password);
      encryptStr(tempUserData[uid].password);
      clearInput();
      break;

    
    case 3:
      //while the input is invalid
      do
      {
        if(invalidInputFlag == 1)
        {
          printf("Invalid user type\n");
        }
        invalidInputFlag=0;

        //get input
        printf("1. Regular User\n2. Admin");
        printf("Enter a admin level: ");
        scanf("%i", &tempUserData[uid].usertype);
        tempUserData[uid].usertype--;
        clearInput();

        invalidInputFlag=1;
      }while(tempUserData[uid].usertype!=1 && tempUserData[uid].usertype!=0);
      break;
  }

  //save data
  writeUsers(tempUserData, userCount);
}

void printUserFile()
{
  FILE *fp;
  fp = fopen("./users/user_data", "r");
  char temp[256];
  
  while (!feof(fp))
  {
    fscanf(fp, "%s", temp);
    if (!feof(fp))
      printf("%s\n", temp);
  }
  fclose(fp);
}

int getUserCount()
{
  FILE *fp;
  fp = fopen("./users/user_data", "r");
  int userCount;

  if (fp == NULL)//if file does not exist
  {
    FILE *fptr;
    fptr = fopen("./users/user_data", "w");
  
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

void getAllUsersInfo(userData userData[])
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

static int checkPassword(tempUserData *currentUserData, char username[], char password[])
{
  int userCount = getUserCount();
  tempUserData tempUserData[userCount];
  readUsers(tempUserData);
  int userFound=0;
  
  //return whether the password was correct
  encryptStr(password);
  for (int x=0; x<userCount; x++)
  {
    if (strcmp(tempUserData[x].username,username)==0)
    {
      if (strcmp(tempUserData[x].password, password)==0)
      {
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
  fp = fopen("./users/user_data", "r");
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
  fp = fopen("./users/user_data", "w");
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
  printf("Username (no spaces): ");
  scanf("%s", tempUserData[userCount].username);
  clearInput();

  printf("Password (no spaces): ");
  scanf("%s", tempUserData[userCount].password);
  clearInput();

  encryptStr(tempUserData[userCount].password);

  //write all data back to file
  writeUsers(tempUserData, userCount+1);
  
  return(0);
}

static void clearInput()
{
  char buff;
  while (buff!='\n')
  {
    scanf("%c", &buff);
  }
}