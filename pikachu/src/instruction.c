#include "machine.h"
#include "instruction.h"
#include<stdio.h>

int mov(char * source, char * dest, int len)
{
  int  i;
  for(i = 0; i < len; i++)
  {
    dest[i] = source[i];
  }
  return 0;
}

int display(char *buffer, int len)
{
  int i;
  for(i = 0; i < len; i++)
  {
    fputc(buffer[i], stdin);
  }
}
