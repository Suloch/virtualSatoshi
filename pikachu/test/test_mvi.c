
#include <stdio.h>
#include "test_mvi.h"
#include "../machine.h"
#include "../utils.h"

machine *test_program(char *buffer, int length)
{
  int l;
  char * program = convert(buffer, , &l);
  machine *m = init_machine();
  load_program(m, program, l);
  free(program);
  execute(program);
  return machine;
}

int test_mvi_A_0()
{
  fprintf(stderr, "Copying 0 to A!");
  char *buffer = "";
  int l;
  m = test_program(buffer, 10);

  if(ternary_to_decimal(m -> A, 9) != 0)
  {
    fprintf(stderr, "%s%d\n", "A not 0 :", ternary_to_decimal(m- > A, 9));
    return 1;
  }
  else
  {
    fprintf(stderr, "Succesfull!");
  }
  delete_machine(m);
  return 0;
}

int test_mvi_A_13()
{
  fprintf(stderr, "Copying 13 to A!");
  char *buffer = "";
  int l;
  m = test_program(buffer, 10);

  if(ternary_to_decimal(m -> A, 9) != 13)
  {
    fprintf(stderr, "%s%d\n", "A not 0 :", ternary_to_decimal(m- > A, 9));
    return 1;
  }
  else
  {
    fprintf(stderr, "Succesfull!");
  }
  delete_machine(m);
  return 0;
}

int test_mvi_A_n1231()
{
  fprintf(stderr, "Copying -1231 to A!");
  char *buffer = "";
  int l;
  m = test_program(buffer, 10);

  if(ternary_to_decimal(m -> A, 9) != -1231)
  {
    fprintf(stderr, "%s%d\n", "A not 0 :", ternary_to_decimal(m- > A, 9));
    return 1;
  }
  else
  {
    fprintf(stderr, "Succesfull!");
  }
  delete_machine(m);
  return 0;
}

int test_mvi_main()
{
  test_mvi_A_0();
  return 0;
}
