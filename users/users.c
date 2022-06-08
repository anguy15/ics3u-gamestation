#include "users.h"

//functions
int login(userData *userData)
{  
  system("clear");
  int userCount = getUserCount();
  char username[256];
  char password[256];
  char passwordFails=0;
  tempUserData tempUserData = {0};
  
  if (userCount == 0)//no user exists
  {
    makeUser(2, userData);//make a admin user
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
      getchar();
  
      //get password
      printf("Password: ");
      scanf("%s", password);
      getchar();
      
      passwordFails++;
    }while(checkPassword(&tempUserData, username, password)==0);

    //copy temp data to program data
    userData->uid = tempUserData.uid;
    strcpy(userData->username, tempUserData.username);
    userData->usertype = tempUserData.usertype;
    
    
  
    return(1);
  }
  return(0);
}

void addUser(int usertype)
{
  //update user file
  userData tempUserData;
  
  //add the new user
  makeUser(usertype, &tempUserData);
  
  //update stats file
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
    FILE *fp;
    fp = fopen("./users/user_data", "w");
  
    fprintf(fp, "0\n");
    
    fclose(fp);
    return 0;
  }
  else//we find the user count
  {
    fscanf(fp, "%i", &userCount);
  }

  fclose(fp);
  return userCount;
}

void updateUserData(tempUserData newUserData)
{
  int userCount = getUserCount();
  tempUserData userData[userCount];  
  readUsers(userData);
  
  strcpy(userData[newUserData.uid].username,newUserData.username);
  strcpy(userData[newUserData.uid].password,newUserData.password);
  userData[newUserData.uid].uid,newUserData.uid;
  userData[newUserData.uid].usertype=newUserData.usertype;
  
  writeUsers(userData, userCount);
}

void getAllUserInfo(userData userData[])
{
  int userCount = getUserCount();
  tempUserData tempUserData[userCount];
  readUsers(tempUserData);
  for (int x=0; x<userCount; x++)
  {
    userData[x].uid=tempUserData[x].uid;
    strcpy(userData[x].username,tempUserData[x].username);
    userData[x].usertype=tempUserData[x].usertype;
  }
}

static int checkPassword(tempUserData *userData, char username[], char password[])
{
  int userCount = getUserCount();
  tempUserData tempUserData[userCount];
  readUsers(tempUserData);
  int userFound=0;
  int userMatches[userCount];
  //set usermatches to 0
  for(int x=0; x<userCount; x++)
  {
    userMatches[x]=0;
  }

  for (int x=0; x<userCount; x++)
  {
    if (strcmp(tempUserData[x].username,username)==0)
    {
      userMatches[x]=1;
    }
  }
  
  //return whether the password was correct
  encryptStr(password);
  for (int x=0; x<userCount; x++)
  {
    if (userMatches[x]==1)
    {
      if (strcmp(tempUserData[x].password, password)==0)
      {
        strcpy(userData->username, tempUserData[x].username);
        strcpy(userData->password, tempUserData[x].password);
        return 1;
      }
      else
      {
        return 0;
      }
    }
  }
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
    //read uid
    fprintf(fp, "%i ", userData[x].uid);
    //read username
    fprintf(fp, "%s ", userData[x].username);
    //read usertype
    fprintf(fp, "%i ", userData[x].usertype);
    //read password
    fprintf(fp, "%s\n", userData[x].password);
    x++;
  }

  fclose(fp);
  return(x);
}

static int makeUser(int usertype, userData *permUserData)
{
  //storing temp data to write later
  //new usercount
  int userCount=getUserCount();
  tempUserData userData[userCount];
  if (userCount != 0)//there are users
  {
    readUsers(userData);
  }
  
  //setup uid and usertype
  userData[userCount].uid = userCount;
  userData[userCount].usertype = usertype;

  //setup username and password
  printf("Username (no spaces): ");
  scanf("%s", userData[userCount].username);
  getchar();

  printf("Password (no spaces): ");
  scanf("%s", userData[userCount].password);
  getchar();

  encryptStr(userData[userCount].password);


  //write all data back to file
  writeUsers(userData, userCount+1);

  //copy user info to program data
  permUserData->uid = userData[userCount].uid;
  strcpy(permUserData->username, userData[userCount].username);
  permUserData->usertype = userData[userCount].usertype;
  
  return(0);
}