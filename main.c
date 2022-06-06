#include <stdio.h>
#include "users/users.h"



int main(void) {
  int userID=0;
  login(&userID);

  printf("%i", userID);
  
  return(0);
}

