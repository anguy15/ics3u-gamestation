#include "users.h"

//functions
int login(userData *userData)
{  
  system("clear");
  int userCount = checkUserCount();
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

static int makeUserDB()
{
  FILE *fp;
  fp = fopen("./users/user_data", "w");

  fprintf(fp, "0\n");
  
  fclose(fp);
}

static int checkPassword(tempUserData *tempUserData, char username[], char password[])
{
  FILE *fp;
  fp = fopen("./users/user_data", "r");
  char buffer[256];
  int userFound=0;
  int x=0;

  fscanf(fp, "%s", buffer);
  while (!feof(fp) && userFound==0)
  {
    //read uid
    fscanf(fp, "%i", &tempUserData->uid);
    //read username
    fscanf(fp, "%s", tempUserData->username);
    
    if (strcmp(tempUserData->username, username)==0)
    {
      userFound=1;
    }

    //read usertype
    fscanf(fp, "%i", &tempUserData->usertype);
    //read password
    fscanf(fp, "%s", tempUserData->password);
  }
  fclose(fp);
  
  //return whether the password was correct
  encryptStr(password);
  if (strcmp(tempUserData->password, password)==0 && userFound == 1)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int checkUserCount()
{
  FILE *fp;
  fp = fopen("./users/user_data", "r");
  int userCount;

  if (fp == NULL)//if file does not exist
  {
    makeUserDB();
    return 0;
  }
  else//we find the user count
  {
    fscanf(fp, "%i", &userCount);
  }

  fclose(fp);
  return userCount;
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
  int userCount=checkUserCount()+1;
  tempUserData userData[userCount];
  if (userCount != 1)//there are users
  {
    readUsers(userData);
  }
  
  FILE *fp;
  fp = fopen("./users/user_data", "w");
  
  //setup uid and usertype
  userData[userCount-1].uid = userCount-1;
  userData[userCount-1].usertype = usertype;

  //setup username and password
  printf("Username (no spaces):");
  scanf("%s", userData[userCount-1].username);
  getchar();

  printf("Password (no spaces):");
  scanf("%s", userData[userCount-1].password);
  getchar();

  encryptStr(userData[userCount-1].password);

  //write all data back to file
  writeUsers(userData, userCount);

  //copy user info to program data
  permUserData->uid = userData[userCount-1].uid;
  strcpy(permUserData->username, userData[userCount-1].username);
  permUserData->usertype = userData[userCount-1].usertype;
  
  
  fclose(fp);
  return(0);
}