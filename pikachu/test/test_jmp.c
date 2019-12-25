#include <stdio.h>
#include "test_mvi.h"
#include "../src/machine.h"
#include "../src/utils.h"
#include <string.h>
#include<stdlib.h>
#include<string.h>
#include "execute.h"

int test_jmp(char *buffer, int value)
{
  printf("------------------------------------------------------------------------------------------------------------------\n");

  int l;

  machine *m = test_program(buffer, strlen(buffer));
  printf("%s\n", "Checking the registers values");

  if(ternary_to_decimal(m -> R[8], 9) != value)
  {
    fprintf(stderr, "Flag not %d: %d\n", value, ternary_to_decimal(m -> R[8], 9));
    printf("------------------------------------------------------------------------------------------------------------------\n");
    return 1;
  }
  else
  {
    fprintf(stderr, "[✓] Succesfull!\n");
  }
  printf("------------------------------------------------------------------------------------------------------------------\n");
  delete_machine(m);
  return 0;
}

int test_jmp_main()
{
  printf("Testing JMP, JEQ, JGT, JLT instruction\n");

  /* jump to memory location 1213
  */
  test_jmp("PIKA PIKA PIKACHU PIKA PIKACHU PI PI PIKA PIKA PIKA PI PIKACHU", 1213);
  /*copy 13 to A and -1213 to B
    compare A and B
  */
  // test_cmp("PI PI PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PIKACHU PI PI PIKA PIKA PIKA PIKACHU PIKA PI PIKACHU PIKACHU PIKA PI PIKACHU PIKACHU PI PI PIKACHU PI PIKA PIKA PIKA PIKA PIKA PIKACHU", 1);

  /*copy 13 to A and -1213 to B
    compare B and A
  */
  // test_cmp("PI PI PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PIKACHU PI PI PIKA PIKA PIKA PIKACHU PIKA PI PIKACHU PIKACHU PIKA PI PIKACHU PIKACHU PI PI PIKACHU PI PIKA PIKA PIKACHU PIKA PIKA PIKA", -1);

  /*copy 0 to A and 0 to B
    compare B and A
  */
  // test_cmp("PI PI PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PI PI PIKA PIKA PIKA PIKACHU PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PI PIKACHU PI PIKA PIKA PIKACHU PIKA PIKA PIKA", 0);

  return 0;
}
