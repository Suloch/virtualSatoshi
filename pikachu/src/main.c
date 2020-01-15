
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "messages.h"
#include "machine.h"
#include "utils.h"
#include "server.h"

int main(int argc, char **argv)
{
  /*
  read the Executable
  */
  if(argc < 2)
  {
    fprintf(stderr, "%s\n", INVALID_ARGS0);
    return 1;
  }
  char *filename = argv[1];

  FILE * fp = fopen(filename, "r");
  if(fp == NULL)
  {
    fprintf(stderr, "%s\n", INVALID_ARGS1);
    return 2;
  }

  char ch, *buffer;
  int len=1, i=0;
  buffer = malloc(sizeof(char) * len);

  if(buffer == NULL)
  {
      fprintf(stderr, "%s\n", MEMORY_ALLOC0);
  }

  ch = fgetc(fp);
  while(ch != EOF)
  {
    buffer[i] = ch;
    i++;
    if(i == len)
    {
      len = len * 2;
      buffer = realloc(buffer, sizeof(char)*len);
    }
    ch = fgetc(fp);
  }
  /*
  convert into -1, 0, +1
  */
  int l;
  char *program = convert(buffer, i, &l);

  if(program == NULL){
    fprintf(stderr, "%s\n", INVALID_CODE0);
    return 3;
  }

  free(buffer);
  /*
  initialize the machine
  */
  machine *m = init_machine();
  /*
  load the program
  */
  load_program(m, program, l);
  free(program);
  /*
    todo: execute the program
  */

  /*start the server in another thread
    */
  pthread_t server_thread;
  pthread_create(&server_thread, NULL, &start, NULL);
  execute_program(m);
  /*
  delete the machine
  */
  delete_machine(m);
  /* wait for the server to exit
  */
  pthread_join(server_thread, NULL);

  return 0;
}
