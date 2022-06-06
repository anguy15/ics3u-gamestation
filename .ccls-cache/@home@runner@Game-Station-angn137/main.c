#include <stdio.h>
#include "main.h"


int main(void) {
  FILE *fp = fopen("./test/a", "w");
  fclose(fp);
  return(0);
}