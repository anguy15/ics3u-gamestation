#include "simple_crypt.h"


void encryptStr(char string[])
{
  int shift = sumOfString(string);

  for (int x=0; x<strlen(string); x++)
  {
    for (int y=0; y<shift; y++)
    {
      if (string[x]!=126)//the max range for the valid chars
      {
        string[x]++;
      }
      else
      {
        string[x]=33;//the lowest valid char
      }
    }
  }
}

static int sumOfString(char string[])
{
  int sum=0;

  for (int x=0; x<strlen(string); x++)
  {
    sum += string[x];
  }

  return sum;
}