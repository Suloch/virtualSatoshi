
#include <stdio.h>
#include "test_mvi.h"
#include "../src/machine.h"
#include "../src/utils.h"
#include <string.h>
#include<stdlib.h>
#include<string.h>

machine *test_program(char *buffer, int length)
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

int test_mvi(char *buffer, int reg, int value)
{
  printf("------------------------------------------------------------------------------------------------------------------\n");
  if(reg > 6 || reg < 0)
  {
    fprintf(stderr, "%s\n", "INVALID_REG");
    return 1;
  }
  if(reg == 6)
  {
    fprintf(stderr, "Copying %d to memory...\n", value);
  }
  else
  {
    fprintf(stderr, "Copying %d to %c\n", value, reg+65);
  }
  int l;

  machine *m = test_program(buffer, strlen(buffer));

  if(reg == 6)
  {
    printf("%s\n", "Checking the value at memory");
    if(ternary_to_decimal(m->M + ternary_to_decimal(m -> R[1], 9) + 9841, 9) != value)
    {
      fprintf(stderr, "memory not %d: %d\n", value, ternary_to_decimal(m -> R[0], 9));
      printf("------------------------------------------------------------------------------------------------------------------\n");
      return 2;
    }
    else
    {
      fprintf(stderr, "[✓] Succesfull!\n");
    }
  }
  else
  {
    printf("%s\n", "Checking the registers values");
    if(ternary_to_decimal(m -> R[reg], 9) != value)
    {
      fprintf(stderr, "%c not %d: %d\n", reg+65, value, ternary_to_decimal(m -> R[0], 9));
      printf("------------------------------------------------------------------------------------------------------------------\n");
      return 2;
    }
    else
    {
      fprintf(stderr, "[✓] Succesfull!\n");
    }
  }
  printf("------------------------------------------------------------------------------------------------------------------\n");
  delete_machine(m);
  return 0;
}

int test_mvi_main()
{
  printf("Testing MVI instruction\n");

  /*test A register with 0 value
  */
  test_mvi("PI PI PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA", 0, 0);

  /*test A register with 13 value
  */
  test_mvi("PI PI PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PIKACHU", 0, 13);

  /*test A register with -1231 value
  */
  test_mvi("PI PI PIKA PIKA PIKA PIKA PIKA PI PIKACHU PIKACHU PIKA PI PIKACHU PIKACHU PI", 0, -1231);

  /*test B register with 0 value
  */
  test_mvi("PI PI PIKA PIKA PIKA PIKACHU PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA", 1, 0);

  /*test B register with 13 value
  */
  test_mvi("PI PI PIKA PIKA PIKA PIKACHU PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PIKACHU", 1, 13);

  /*test B register with -1231 value
  */
  test_mvi("PI PI PIKA PIKA PIKA PIKACHU PIKA PI PIKACHU PIKACHU PIKA PI PIKACHU PIKACHU PI", 1, -1231);

  /*test C register with 0 value
  */
  test_mvi("PI PI PIKA PIKA PIKACHU PI PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA", 2, 0);

  /*test C register with 13 value
  */
  test_mvi("PI PI PIKA PIKA PIKACHU PI PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PIKACHU", 2, 13);

  /*test C register with -1231 value
  */
  test_mvi("PI PI PIKA PIKA PIKACHU PI PIKA PI PIKACHU PIKACHU PIKA PI PIKACHU PIKACHU PI", 2, -1231);

  /*test D register with 0 value
  */
  test_mvi("PI PI PIKA PIKA PIKACHU PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA", 3, 0);

  /*test D register with 13 value
  */
  test_mvi("PI PI PIKA PIKA PIKACHU PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PIKACHU", 3, 13);

  /*test D register with -1231 value
  */
  test_mvi("PI PI PIKA PIKA PIKACHU PIKA PIKA PI PIKACHU PIKACHU PIKA PI PIKACHU PIKACHU PI", 3, -1231);

  /*test E register with 0 value
  */
  test_mvi("PI PI PIKA PIKA PIKACHU PIKACHU PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA", 4, 0);

  /*test E register with 13 value
  */
  test_mvi("PI PI PIKA PIKA PIKACHU PIKACHU PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PIKACHU", 4, 13);

  /*test E register with -1231 value
  */
  test_mvi("PI PI PIKA PIKA PIKACHU PIKACHU PIKA PI PIKACHU PIKACHU PIKA PI PIKACHU PIKACHU PI", 4, -1231);

  /*test F register with 0 value
  */
  test_mvi("PI PI PIKA PIKACHU PI PI PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA", 5, 0);

  /*test F register with 13 value
  */
  test_mvi("PI PI PIKA PIKACHU PI PI PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PIKACHU", 5, 13);

  /*test F register with -1231 value
  */
  test_mvi("PI PI PIKA PIKACHU PI PI PIKA PI PIKACHU PIKACHU PIKA PI PIKACHU PIKACHU PI", 5, -1231);

  return 0;
}
