
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

int test_mvi_A_0()
{
  fprintf(stderr, "Copying 0 to A...\n");
  char *buffer = "PI PI PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA";
  int l;

  machine *m = test_program(buffer, strlen(buffer));

  printf("%s\n", "Checking the registers values");
  if(ternary_to_decimal(m -> R[0], 9) != 0)
  {
    fprintf(stderr, "%s%d\n", "A not 0 :", ternary_to_decimal(m -> R[0], 9));
    return 1;
  }
  else
  {
    fprintf(stderr, "[✓] Succesfull!\n");
  }
  delete_machine(m);
  return 0;
}

int test_mvi_A_13()
{
  fprintf(stderr, "Copying 13 to A...");
  char *buffer = "";
  int l;
  machine *m = test_program(buffer, 10);

  if(ternary_to_decimal(m -> R[0], 9) != 13)
  {
    fprintf(stderr, "%s%d\n", "A not 0 :", ternary_to_decimal(m -> R[0], 9));
    return 1;
  }
  else
  {
    fprintf(stderr, "Succesfull!\n");
  }
  delete_machine(m);
  return 0;
}

int test_mvi_A_n1231()
{
  fprintf(stderr, "Copying -1231 to A...");
  char *buffer = "";
  int l;
  machine *m = test_program(buffer, 10);

  if(ternary_to_decimal(m -> R[0], 9) != -1231)
  {
    fprintf(stderr, "%s%d\n", "A not 0 :", ternary_to_decimal(m -> R[0], 9));
    return 1;
  }
  else
  {
    fprintf(stderr, "Succesfull!\n");
  }
  delete_machine(m);
  return 0;
}

int test_mvi_main()
{
  test_mvi_A_0();
  return 0;
}
