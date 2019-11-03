
int NUM_REG = 9;
int LEN_REG = 16;
int NUM_MEMORY =  19683 /* 3 ^ 9 = 19683 */
int LEN_MEMORY = 6;

typedef struct
{
  /*
  registers
   */
  char R[LEN_REG][NUM_REG];
  /*
  main memory
  */
  char M[LEN_MEMORY][NUM_MEMORY];

}machine;
machine m;

void init_machine();
int load_program(char *, int);
