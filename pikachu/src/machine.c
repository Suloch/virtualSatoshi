
#include "machine.h"
#include "utils.h"
#include "instruction.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<stdio.h>
#include <pthread.h>

pthread_mutex_t lock;

int NUM_REG = 9;
int LEN_REG = 9;
int NUM_MEMORY =  19683; /* 3 ^ 9 = 19683 */
int LEN_MEMORY = 1;
int LEN_OPCODE = 3;
int LEN_REG_NO = 3;
int OFFSET = -9841;
int STACK_START = -9598;
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
      m -> R[i][j] = '0';
    }
  }
  /*
  init the the program counter to "---------"
  */
  for(j = 0; j < LEN_REG; j++)
  {
    m -> R[8][j] = '-';
  }

  /*init the stack pointer
  */
  decimal_to_ternary(STACK_START, m -> R[6], 9);

  for(i = 0; i < NUM_MEMORY * LEN_MEMORY; i++)
  {
      m -> M[i] = '0';
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

char * read_reg(machine *m)
{
  /*read the number of the first register*/
  int program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;
  int reg = ternary_to_decimal((m -> M) + program_counter, LEN_REG_NO);
  /*move the program counter */
  decimal_to_ternary(program_counter + OFFSET + 3, m -> R[8], LEN_REG);
  /*check valid range or not
  */
  if(reg > 6 || reg < 0)
  {
    return NULL;
  }
  /*check if it points to memory
  */
  if(reg == 6)
  {
    /* return the memory pointer
    */
    return (m -> M) + (ternary_to_decimal(m -> R[1], LEN_REG) - OFFSET);
  }
  /*return the register pointer
  */
  return m -> R[reg];
}

int execute_program(machine *m)
{
  /*
  execute the program
  */
  char * op1, *op2;
  while(1)
  {
    get_machine_state(m, 1);
    sleep(2);
    /*
    read opcode(3 trits) starting from memory pointed by program counter
    */
    int num1, num2, carry, flag;
    int program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;
    int opcode = ternary_to_decimal((m -> M) + program_counter, LEN_OPCODE);
    /*
    move the program counter 3 trits
    */
    decimal_to_ternary(program_counter + OFFSET + 3, m -> R[8], LEN_REG);

    switch (opcode)
    {
      case -13: /*mov instructions*/
                op1 = read_reg(m);
                op2 = read_reg(m);
                mov(op1, op2, LEN_REG);
                break;

      case -12: /*mvi instructions*/
                /*read the number of the first register*/
                op1 = read_reg(m);
                program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;
                mov((m -> M) + program_counter, op1, LEN_REG);
                /* move the program counter
                */
                decimal_to_ternary(program_counter + OFFSET + 9, m -> R[8], LEN_REG);
                break;

      case -11: /*and with accumulator*/
                op1 = read_reg(m);

                and(op1, m->R[0], LEN_REG);
                break;

      case -10: /*or with accumulator*/
                /*read the number of the first register*/
                op1 = read_reg(m);
                or(op1, m->R[0], LEN_REG);
                break;

      case  -9: /*increment a register*/
                /*read the register to be incremented
                */
                op1 = read_reg(m);

                int num = ternary_to_decimal(op1, LEN_REG);
                /*increment the number
                */
                num++;
                /*initialize Carry
                */
                int carry = 0;
                /*check for overflow
                */
                if(num > -OFFSET)
                {
                  num = OFFSET;
                  carry = 1;
                }
                /*set the register and the carry
                */
                decimal_to_ternary(num, op1, LEN_REG);
                decimal_to_ternary(carry, m -> R[7], LEN_REG);
                break;

      case  -8: /*decrememt a register*/
                op1 = read_reg(m);

                num1 = ternary_to_decimal(op1, LEN_REG);
                /*increment the number
                */
                num1--;
                /*initialize Carry
                */
                carry = 0;
                /*check for overflow
                */
                if(num < OFFSET)
                {
                  num = -OFFSET;
                  carry = -1;
                }
                /*set the register and the carry
                */
                decimal_to_ternary(num1, op1, LEN_REG);
                decimal_to_ternary(carry, m -> R[7], LEN_REG);
                break;

      case  -7: /*compare two registers*/
                /* read the registers
                */
                op1 = read_reg(m);
                op2 = read_reg(m);
                /* convert the numbers
                */
                num1 = ternary_to_decimal(op1, LEN_REG);
                num2 = ternary_to_decimal(op2, LEN_REG);
                /*find the condition and store it in flag
                */
                if(num1 > num2)
                {
                  flag = 1;
                }
                else
                {
                  if(num1 == num2)
                  {
                    flag = 0;
                  }
                  else
                  {
                    flag = -1;
                  }
                }
                /*write the flag value to the register
                */
                decimal_to_ternary(flag, m -> R[7], LEN_REG);
                break;

      case  -6: /*rotate left a register(trit wise rotation)*/
                break;

      case  -5: /*rotate right a register(trit wise rotation)*/
                break;

      case  -4: /*Push the register variables on stack*/
                push(m -> M, ternary_to_decimal(m -> R[6], LEN_REG) - OFFSET, m -> R);
                /*move the stack pointer
                */
                decimal_to_ternary(program_counter + OFFSET + 81, m -> R[8], LEN_REG);
                /*move the program counter
                */
                decimal_to_ternary(program_counter + OFFSET + 3, m -> R[8], LEN_REG);
                break;

      case  -3: /*Pop register variables from stack */
                pop(m -> M, ternary_to_decimal(m -> R[6], LEN_REG) - OFFSET, m -> R);
                /*move the stack pointer
                */
                decimal_to_ternary(program_counter + OFFSET - 81, m -> R[8], LEN_REG);
                /*move the program counter
                */
                decimal_to_ternary(program_counter + OFFSET + 3, m -> R[8], LEN_REG);
                break;

      case  -2: /*Interrupt to display a register to stdout*/
                op1 = read_reg(m);

                display(op1, LEN_REG);
                break;
      case  -1: /*Interrupt to take input from stdin to buffer*/ break;

      case   0: /*Halt the machine*/ return 0; break;

      case   1: /*jump the program counter to a memory location
                */
                program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;
                /* set the program counter to the memory location in the instruction
                */
                mov((m -> M) + program_counter, m -> R[8], LEN_REG);
                break;

      case   2: /*jump if the flag is 0
                */
                program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;
                flag = ternary_to_decimal(m -> R[7], LEN_REG);

                if(flag == 0)
                {
                  /* if flag is zero copy the value in memory to program counter
                  */
                  mov((m -> M) + program_counter, m -> R[8], LEN_REG);
                }
                else
                {
                  /*if flag is not zero skip 12 trits used for the instruction
                  */
                  decimal_to_ternary(program_counter + OFFSET + 12, m -> R[8], LEN_REG);
                }
                break;

      case   3: /*jump if the flag is 1
                */
                program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;
                flag = ternary_to_decimal(m -> R[7], LEN_REG);

                if(flag == 1)
                {
                  /* if flag is 1 copy the value in memory to program counter
                  */
                  mov((m -> M) + program_counter, m -> R[8], LEN_REG);
                }
                else
                {
                  /*if flag is 1 skip 12 trits used for the instruction
                  */
                  decimal_to_ternary(program_counter + OFFSET + 12, m -> R[8], LEN_REG);
                }
                break;

      case   4: /*jump if the flag is -1
                */
                program_counter = ternary_to_decimal(m -> R[8], LEN_REG) - OFFSET;
                flag = ternary_to_decimal(m -> R[7], LEN_REG);

                if(flag == -1)
                {
                  /* if flag is -1 copy the value in memory to program counter
                  */
                  mov((m -> M) + program_counter, m -> R[8], LEN_REG);
                }
                else
                {
                  /*if flag is -1 skip 12 trits used for the instruction
                  */
                  decimal_to_ternary(program_counter + OFFSET + 12, m -> R[8], LEN_REG);
                }
                break;

      default : /*generate not implemented error*/;
    }
  }
}

char * get_machine_state(machine *m, int operation)
{
  static int last_operation;
  static char * state = NULL;
  pthread_mutex_lock(&lock);
  if(operation == 1)
  {
    state = malloc(sizeof(char ) * ((NUM_MEMORY * LEN_MEMORY)+82));
    memcpy(state, m -> M, NUM_MEMORY * LEN_MEMORY);
    int i;
    for(i = 0; i < NUM_REG; i++)
    {
      memcpy(state+(NUM_MEMORY * LEN_MEMORY)+(i * LEN_REG), m -> R[i], LEN_REG);
    }
    state[NUM_MEMORY * LEN_MEMORY + 81] = '\0';
    last_operation = 1;
    pthread_mutex_unlock(&lock);
    return NULL;
  }

  if(operation == 2)
  {
    if(last_operation == 1)
    {
      last_operation = 2;
      pthread_mutex_unlock(&lock);
      return state;

    }
    else
    {
      pthread_mutex_unlock(&lock);
      return NULL;
    }
  }
  pthread_mutex_unlock(&lock);
  return NULL;
}
