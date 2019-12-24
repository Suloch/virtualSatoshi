#include <stdio.h>
#include "test_mvi.h"
#include "../src/machine.h"
#include "../src/utils.h"
#include <string.h>
#include<stdlib.h>
#include<string.h>
#include "execute.h"


int test_and(char *buffer, int value)
{
  printf("------------------------------------------------------------------------------------------------------------------\n");
  printf("%s\n", "Executing program");
  machine *m = test_program(buffer, strlen(buffer));


  printf("%s\n", "Checking the accumulator");
  if(ternary_to_decimal(m -> R[0], 9) != value)
  {
    fprintf(stderr, "A not %d: %d\n",  value, ternary_to_decimal(m -> R[0], 9));
    printf("------------------------------------------------------------------------------------------------------------------\n");
    return 2;
  }
  else
  {
    fprintf(stderr, "[✓] Succesfull!\n");
  }

  printf("------------------------------------------------------------------------------------------------------------------\n");
  delete_machine(m);
  return 0;
}

int test_and_main()
{
  /*copy -1213 to A, then copy -9143 to B, 'and A'
  check A
  */
  test_and("PI PI PIKA PIKA PIKA PIKA PIKA PI PIKACHU PIKACHU PIKA PIKA PIKA PIKACHU PI PI PI PIKA PIKA PIKA PIKACHU PI PI PI PIKACHU PIKACHU PIKA PIKACHU PIKA PIKACHU PI PI PIKACHU PIKA PIKA PIKACHU", 1700);
  return 0;
}
