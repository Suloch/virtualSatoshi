typedef struct {
  char *name;
  int value;
}symbol;
int create_table(int);
int find_symbol(symbol *, int, char *);
int set_symbol(symbol *, int, char *, int);
