#include "test_mov.h"
#include <stdio.h>
#include "../src/machine.h"
#include "../src/utils.h"
#include <string.h>
#include<stdlib.h>

machine *test_program_mov(char *buffer, int length)
{
  int l;
  printf("%s\n", "Converting input to ternary...");
  char temp[1000];
  strcpy(temp, buffer);
  char * program = convert(temp, length, &l);
  printf("%s\n", "Initializing machine");
  machine *m = init_machine();
  printf("%s\n", "Loading program");
  load_program(m, program, l);
  free(program);
  printf("%s\n", "Executing program");
  execute_program(m);
  return m;
}

int test_mov(char *buffer, int reg1, int reg2)
{
  printf("------------------------------------------------------------------------------------------------------------------\n");
  if(reg1 > 6 || reg1 < 0 || reg2 > 6 || reg2 < 0)
  {
    fprintf(stderr, "%s\n", "INVALID_REG");
    return 1;
  }
  fprintf(stderr, "copying from %c to %c\n", reg1+65, reg2+65);
  machine *m = test_program_mov(buffer, strlen(buffer));
  char *op1, *op2;
  if(reg1 == 6)
  {
    op1 = (m -> M) + (ternary_to_decimal(m -> R[1], 9) + 9841);
  }
  else
  {
    op1 = m -> R[reg1];
  }
  if(reg2 == 6)
  {
    op2 = (m -> M) + (ternary_to_decimal(m -> R[1], 9) + 9841);
  }
  else
  {
    op2 = m -> R[reg2];
  }
  fprintf(stderr, "checking values of %c %c\n", reg1+65, reg2+65);
  fprintf(stderr, "%d %d\n", ternary_to_decimal(op1, 9), ternary_to_decimal(op2, 9));
  if(ternary_to_decimal(op1, 9) != ternary_to_decimal(op2, 9))
  {
    fprintf(stderr, "%c not %c: %d\n", reg1+65, reg2+64, ternary_to_decimal(m -> R[0], 9));
    printf("------------------------------------------------------------------------------------------------------------------\n");
    return 1;
  }
  else
  {
    fprintf(stderr, "[✓] Successful\n");
  }
  printf("------------------------------------------------------------------------------------------------------------------\n");
  delete_machine(m);
  return 0;
}

int test_mov_main()
{
  printf("Testing MOV instruction\n");
  /*copy A to B
  */
  test_mov("PI PI PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PIKACHU PI PI PI PIKA PIKA PIKA PIKA PIKA PIKACHU", 0, 1);

  /*copy B to C
  */
  test_mov("PI PI PIKA PIKA PIKA PIKACHU PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PIKACHU PI PI PI PIKA PIKA PIKACHU PIKA PIKACHU PI", 1, 2);

  /*copy C to D
  */
  test_mov("PI PI PIKA PIKA PIKACHU PI PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PIKACHU PI PI PI PIKA PIKACHU PI PIKA PIKACHU PIKA", 2, 3);

  /*copy F to M
  */
  test_mov("PI PI PIKA PIKA PIKA PIKACHU PIKA PI PIKACHU PIKACHU PIKA PI PIKACHU PIKACHU PI PI PI PIKA PIKACHU PI PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PIKACHU PI PI PI PIKACHU PI PIKA PIKACHU PI PI", 5, 6);

  /*copy M to F
  */
  test_mov("PI PI PIKA PIKA PIKACHU PIKACHU PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PIKACHU PI PI PI PIKA PIKACHU PIKACHU PIKACHU PI PIKA", 4, 6);
  return 0;
}
