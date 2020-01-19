
#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>

int create_table(int size)
{
  symbol *table = malloc(size * sizeof(table));
  return table;
}

int find_symbol(symbol *table, int size, char *name)
{
  int i;
  for(i = 0; i < size; i++)
  {
    if(strcmp(table[i].name, name) == 0)
    {
      return table[i].value;
    }
  }
  return -1;
}

int set_symbol(symbol *table, int index, char *name, int value)
{
  table[index].name = malloc((strlen(name) + 1) * sizeof(char));
  strcpy(table[index].name, name);
  table[index].value = value;
  return 1;
}
