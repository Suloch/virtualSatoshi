
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "messages.h"
#include "machine.h"
#include "utils.h"

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
  buffer = malloc(sizeof(char) * len);

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
      buffer = realloc(buffer, sizeof(char)*len);
    }
    ch = fgetc(fp);
  }
  int l;
  char *program = convert(buffer, i, &l);

  if(program == NULL){
    fprintf(stderr, "%s\n", INVALID_CODE0);
    return 3;
  }
  machine *m = init_machine();
  load_program(m, program, l);
  free(buffer);
  free(program);
  delete_machine(m);
  return 0;
}
