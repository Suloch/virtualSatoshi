#include <stdio.h>
#include "test_mvi.h"
#include "../src/machine.h"
#include "../src/utils.h"
#include <string.h>
#include<stdlib.h>
#include<string.h>
#include "execute.h"

int test_push_pop(char *buffer, int reg1, int reg2, int value1, int value2)
{
  printf("------------------------------------------------------------------------------------------------------------------\n");
  printf("%s\n", "Executing program");
  machine *m = test_program(buffer, strlen(buffer));


  printf("%s\n", "Checking the registers");
  if(ternary_to_decimal(m -> R[reg1], 9) != value1 && ternary_to_decimal(m -> R[reg2], 9) != value2)
  {
    fprintf(stderr, "A not %d: %d\n",  value1, ternary_to_decimal(m -> R[reg1], 9));
    fprintf(stderr, "A not %d: %d\n",  value2, ternary_to_decimal(m -> R[reg2], 9));
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

int test_push_pop_main()
{
  /*copy 99 to A and -99 to F Push and pop
    check A and F
  */
  test_push_pop("PI PI PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKA PIKACHU PIKACHU PI PIKA PIKA PI PI PIKA PIKACHU PI PI PIKA PIKA PIKA PIKA PI PI PIKACHU PIKA PIKA PIKA PI PI PIKA PI PIKA", 0, 5, 99, -99);
}
