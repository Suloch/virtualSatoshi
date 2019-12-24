#include "../src/machine.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../src/utils.h"

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
