#include "utils.h"
#include <string.h>

int isRegister(char *name)
{
    char registers[7][15] = {"ELECTRIFY", "ELECTROWEB", "NUZZLE", "OVERDRIVE", "SPARK", "THUNDER", "CATASTROPIKA"};
    int i;
    for(i = 0; i < 6; i++)
    {
      if(strcmp(registers[i], name) == 0)
      {
        return 1;
      }
    }
    return 0;
}

int calculate_length(char *code)
{
  char * tok = strtok(code, " ");
  int offset = 3;
  while(tok != NULL)
  {
    tok = strtok(NULL, " ");
    if(isRegister(tok))
    {
      offset += 3;
    }
    else
    {
      offset += 9;
    }
  }
  return 0;
}
