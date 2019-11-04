
typedef struct
{
  /*
  registers
   */
  char **R;
  /*
  main memory
  */
  char *M;

}machine;

machine *init_machine();

int load_program(machine *, char *, int);

int delete_machine(machine *);
