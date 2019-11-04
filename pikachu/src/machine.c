
#include "machine.h"
#include "utils.h"
#include <stdlib.h>

int NUM_REG = 9;
int LEN_REG = 16;
int NUM_MEMORY =  19683; /* 3 ^ 9 = 19683 */
int LEN_MEMORY = 6;
int LEN_OPCODE = 3;
/*
  R[0] : A(accumulator)
  R[1] : B
  R[2] : C
  R[3] : D
  R[4] : E
  R[5] : F
  R[6] : Stack Pointer
  R[7] : Carry / Condition check register
  R[8] : Program Counter
*/

machine *init_machine()
{
  int i, j;
  /*
  allocate space for registers and memory
  */

  machine * m = malloc(sizeof(machine));
  m -> R = malloc(sizeof(char *) * NUM_REG);
  for(i = 0; i < NUM_REG; i++)
  {
    m -> R[i] = malloc(sizeof(char) * LEN_REG);
  }
  m -> M = malloc(sizeof(char ) * (NUM_MEMORY * LEN_MEMORY));
  /*
  set all register and memory values to zero
  */
  for(i = 0; i < NUM_REG; i++)
  {
    for(j = 0; j < LEN_REG; j++)
    {
      m -> R[i][j] = 0;
    }
  }

  for(i = 0; i < NUM_MEMORY * LEN_MEMORY; i++)
  {
      m -> M[i] = 0;
  }

  return m;
}

int load_program(machine *m, char *program, int len)
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
    m -> M[i] = program[i];
  }
  return 0;
}

int delete_machine(machine *m)
{
  /*
  free memory from the machine
  */
  int i;
  for(i = 0; i < NUM_REG; i++)
  {
    free(m -> R[i]);
  }
  free(m -> M);
  free(m -> R);
  free(m);
  return 0;
}

int execute_program(machine *m)
{
  /*
  execute the program
  */
  while(1)
  {
    /*
    read opcode(3 trits) starting from memory pointed by program counter
    */
    int program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - ternary_to_decimal("---------", LEN_REG);
    int opcode = ternary_to_decimal((m -> M) + program_counter, LEN_OPCODE);
    switch (opcode)
    {
      case -13: /*mov instructions*/break;
      case -12: /*mvi instructions*/break;
      case -11: /*and with accumulato*/break;
      case -10: /*or with accumulator*/break;
      case  -9: /*increment a register*/break;
      case  -8: /*decrememt a register*/break;
      case  -7: /*compare two registers*/ break;
      case  -6: /*rotate left a register*/break;
      case  -5: /*rotate right a register*/ break;
      case  -4: /*Push the register variables on stack*/break;
      case  -3: /*Pop register variables from stack */ break;
      case  -2: /*Interrupt to display a register to stdout*/break;
      case  -1: /*Interrupt to input from stdin to buffer*/ break;
      case   0: /*Halt the machine*/break;
      default : /*generate not implemented error*/
    }
  }
}
