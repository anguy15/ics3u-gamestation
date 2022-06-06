#include "users.h"

//functions
int login(int *userID)
{
  system("clear");
  int userCount = checkUsers();
  char username[256];
  char password[256];
  if (userCount == 0)
  {
    makeUser(2, userID);
  }
  else
  {
    do
    {
      //get username
      printf("Username: ");
      scanf("%s", username);
  
      //get password
      printf("Password: ");
      scanf("%s", password);
      
    }while(checkPassword(username, password, userID)==0);
  }
  return(1);
}

static int makeUserDB()
{
  FILE *fp;
  fp = fopen("./users/user_data", "w");

  fprintf(fp, "0\n");
  
  fclose(fp);
}

static int checkPassword(char username[], char password[], int *uid)
{
  FILE *fp;
  fp = fopen("./users/user_data", "r");
  char buffer[256];
  int userFound=0;

  fscanf(fp, "%s", buffer);
  while (!feof(fp) && userFound==0)
  {
    //read uid
    fscanf(fp, "%i", uid);
    //read username
    fscanf(fp, "%s", buffer);
    
    if (strcmp(buffer, username)==0)
    {
      userFound=1;
    }

    //read usertype
    fscanf(fp, "%s", buffer);
    //read password
    fscanf(fp, "%s", buffer);
  }
  fclose(fp);
  if (strcmp(buffer, password)==0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

static int checkUsers()
{
  FILE *fp;
  fp = fopen("./users/user_data", "r");
  int userCount;

  if (fp == NULL)//if file does not exist
  {
    makeUserDB();
    return 0;
  }
  else if (feof(fp)==1)//if file has no data//is separated from null check because of seg fault
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

static int makeUser(int usertype, int *userID)
{
  //storing temp data to write later
  //new usercount
  int userCount=checkUsers()+1;
  tempUserData userData[userCount];
  readUsers(userData);
  
  FILE *fp;
  fp = fopen("./users/user_data", "w");
  
  //setup uid and usertype
  userData[userCount-1].uid = userCount;
  *userID = userCount;
  userData[userCount-1].usertype = usertype;

  //setup username and password
  printf("Username (no spaces):");
  scanf("%s", userData[userCount-1].username);
  getchar();

  printf("Password (no spaces):");
  scanf("%s", userData[userCount-1].password);
  getchar();

  //write all data back to file
  writeUsers(userData, userCount);
  
  fclose(fp);
  return(0);
}