
#include "machine.h"

void init_machine()
{
  /*
  set all register and memory values to zero
  */
  int i, j;
  for(i = 0; i < NUM_REG; i++)
  {
    for(j = 0; j < LEN_REG; j++)
    {
      m.R = 0;
    }
  }

  for(i = 0; i < NUM_MEMORY; i++)
  {
    for(j = 0; j < LEN_MEMORY; j++)
    {
      m.M = 0;
    }
  }
}

int load_program(char *program, int len)
{
  /*
  load the input program in memory
  starting from the first trit
  */
  if(len >= NUM_MEMORY*LEN_MEMORY)
  {
    /*
    if program is greater than the size of the memory
    of the machine fail
    */
    return 1;
  }
  int i;
  for(i = 0; i < len; i++)
  {
    m.M + i = program[i]
  }
  return 0;
}
