
#include "machine.h"
#include "utils.h"
#include "instruction.h"
#include <stdlib.h>

int NUM_REG = 9;
int LEN_REG = 9;
int NUM_MEMORY =  19683; /* 3 ^ 9 = 19683 */
int LEN_MEMORY = 6;
int LEN_OPCODE = 3;
int LEN_REG_NO = 3;
int OFFSET = -9841;
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
  /*
  init the the program counter to "---------"
  */
  for(j = 0; j < LEN_REG; j++)
  {
    m -> R[8][j] = '-';
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
  int reg1, reg2;
  char * op1, *op2;
  while(1)
  {
    /*
    read opcode(3 trits) starting from memory pointed by program counter
    */
    int program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;
    int opcode = ternary_to_decimal((m -> M) + program_counter, LEN_OPCODE);
    /*
    move the program counter 3 trits
    */
    decimal_to_ternary(program_counter + OFFSET + 3, m -> R[8], LEN_REG);

    switch (opcode)
    {
      case -13: /*mov instructions*/
                /*read the number of the first register*/
                program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;
                reg1 = ternary_to_decimal((m -> M) + program_counter, LEN_REG_NO);
                /*move the program counter */
                decimal_to_ternary(program_counter + OFFSET + 3, m -> R[8], LEN_REG);
                /*read the number of second register */
                program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;
                reg2 = ternary_to_decimal((m -> M) + program_counter, LEN_REG_NO);
                /*move the program_counter */
                decimal_to_ternary(program_counter + OFFSET + 3, m -> R[8], LEN_REG);
                program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - ternary_to_decimal("---------", LEN_REG);

                if(reg1 > 6 || reg1 < 0)
                {
                  return -1;
                }
                if(reg2 > 6 || reg2 < 0)
                {
                  return -1;
                }

                if(reg1 == 6)
                {
                  op1 = (m -> M) + (ternary_to_decimal(m -> R[1], LEN_REG) - OFFSET);
                  if(reg2 == 6)
                  {
                    op2 = (m -> M) + (ternary_to_decimal(m -> R[1], LEN_REG) - OFFSET);
                  }
                  else
                  {
                    op2 = m -> R[reg2];
                  }
                }
                else
                {
                  op1 = m -> R[reg1];
                  if(reg2 == 6)
                  {
                    op2 = (m -> M) + (ternary_to_decimal(m -> R[1], LEN_REG) - OFFSET);
                  }
                  else
                  {
                    op2 = m -> R[reg2];
                  }
                }
                mov(op1, op2, LEN_REG);
                /*move the program_counter */
                decimal_to_ternary(program_counter + OFFSET 3, m -> R[8], LEN_REG);
                break;

      case -12: /*mvi instructions*/

                program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;
                reg1 = ternary_to_decimal((m -> M) + program_counter, LEN_REG_NO);

                decimal_to_ternary(program_counter + OFFSET + 3, m -> R[8], LEN_REG);


                program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;


                if(reg1 < 0 || reg1 > 6)
                {
                  return -1;
                }
                if(reg1 == 6)
                {
                  op1 = (m -> M) + (ternary_to_decimal(m -> R[1], LEN_REG) - OFFSET);
                }
                else
                {
                  op1 = m -> R[reg1];
                }

                mov((m -> M) + program_counter, op1, LEN_REG);
                program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;
                break;

      case -11: /*and with accumulato*/break;
      case -10: /*or with accumulator*/break;
      case  -9: /*increment a register*/break;
      case  -8: /*decrememt a register*/break;
      case  -7: /*compare two registers*/ break;
      case  -6: /*rotate left a register*/break;
      case  -5: /*rotate right a register*/ break;
      case  -4: /*Push the register variables on stack*/break;
      case  -3: /*Pop register variables from stack */ break;
      case  -2: /*Interrupt to display a register to stdout*/
                program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;
                reg1 = ternary_to_decimal((m -> M) + program_counter, LEN_REG_NO);
                if(reg1 < 0 || reg1 > 6)
                {
                  return -1;
                }
                if(reg1 == 6)
                {
                  op1 = (m -> M) + (ternary_to_decimal(m -> R[1], LEN_REG) - OFFSET);
                }
                display(op1, LEN_REG);
                break;
      case  -1: /*Interrupt to take input from stdin to buffer*/ break;
      case   0: /*Halt the machine*/ return 0; break;
      default : /*generate not implemented error*/;
    }
  }
}
