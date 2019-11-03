#include<string.h>
#include <stdlib.h>

char *convert(char *buffer, int len)
{
  /*
    conver PI PI PIKA PIKACHU like string
    to - - 0 + to store in it machine memory
  */
  int i = 0, l = 1;
  char *program = malloc(sizeof(char) * l);

  char * tok = strtok(buffer, " ");
  while(tok != NULL)
  {
    if( strcmp(tok, "PI") == 0)
    {
      program[i] = '-';
    }
    else
    {
        if(strcmp(tok, "PIKA") == 0)
        {
          program[i] = '0';
        }
        else
        {
          if(strcmp(tok, "PIKACHU") == 0)
          {
            program[i] = '+';
          }
          else
          {
            free(program);
            return NULL;
          }
        }
    }
    i++;
    if(i == len)
    {
      len = len * 2;
      program = realloc(program, len * sizeof(char));
    }
  }
  return program;
}
