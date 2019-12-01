#include "machine.h"
#include "instruction.h"

int mov(char * source, char * dest, int len)
{
  int  i;
  for(i = 0; i < len; i++)
  {
    dest[i] = source[i];
  }
  return 0;
}
