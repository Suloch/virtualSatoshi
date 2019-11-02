
#include <stdio.h>
#include <stdlib.h>
#include "messages.h"
#include "machine.h"

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

  char ch, *buffer;
  int len=1, i=0;
  buffer = malloc(sizeof(1) * char);

  if(buffer == NULL)
  {
      fprintf(stderr, "%s\n", MEMORY_ALLOC0);
  }
  ch = fgetc(fp);
  while(ch != EOF)
  {
    buffer[i] = ch;
    i++;
    if(i == len)
    {
      len = len * 2;
      buffer = realloc(buffer, sizeof(len));
    }
  }
  return 0;
}
