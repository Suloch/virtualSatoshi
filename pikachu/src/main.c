
#include <stdio.h>
#include <stdlib.h>
#include "messages.h"

int main(int argc, char **argv)
{
  if(argc < 2)
  {
    fprintf(stderr, "%s\n", INVALID_ARGS0);
    return 1;
  }
  char *filename = argv[1];

  FILE * fp = fopen(filename, "r");
  if(fp == NULL)
  {
    fprintf(stderr, "%s\n", INVALID_ARGS1);
    return 2;
  }
  
  return 0;
}
