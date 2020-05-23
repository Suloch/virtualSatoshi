#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int create_node_code_code(code_node **head, int code, char code_type)
{
  code_node *new_node_code = malloc(sizeof(code_node));
  new_node_code -> node_type = 'C';
  new_node_code -> value.code = code;
  new_node_code -> code_type = code_type;
  new_node_code -> next = NULL;
  code_node * node = *head;
  if(node == NULL){
    *head = new_node_code;
    return 0;
  }
  
  while(node -> next != NULL)
  {
    node = node -> next;
  }
  node -> next = new_node_code;
  return 0;
}

int create_node_code_label(code_node **head, char *label)
{
  code_node *new_node_code = malloc(sizeof(code_node));
  code_node *node = *head;
  new_node_code->node_type = 'L';
  new_node_code -> value.label = malloc(strlen(label)+1);
  strcpy(new_node_code -> value.label, label);
  new_node_code -> next = NULL;
  if (node == NULL)
  {
    *head = new_node_code;
    return 0;
  }
  while(node -> next != NULL)
  {
    node = node -> next;
  }
  node -> next = new_node_code;
  return 0;
}

int is_register(char *name)
{
    char registers[7][15] = {"ELECTRIFY", "ELECTROWEB", "NUZZLE", "OVERDRIVE", "SPARK", "THUNDER", "CATASTROPIKA"};
    int i;
    for(i = 0; i < 7; i++)
    {
      if(strcmp(registers[i], name) == 0)
      {
        return i+1;
      }
    }
    return 0;
}
int is_opcode(char *op_code)
{
  char op_code_label[13][15] = {"CHARGE", "CHARGE_BEAM", "DISCHARGE", "THUNDER_FANG", "THUNDER_PUNCH", "THUNDER_SHOCK", "THUNDER_WAVE", "ION_DELUGE", "WILD_CHARGE", "BOLT_STRIKE", "BOLT_BEAK", "VOLT_TACKLE", "ZIPPY_ZAP"};
  int op_code_value[13] = {-13 ,-12, -2, 1, 2, 4 , 3, -11, -10, -9, -8 ,-7, 0};
  int i;
  for(i = 0; i < 13; i++)
  {
    if (strcmp(op_code_label[i], op_code) == 0)
    {
      return op_code_value[i];
    }
  }
  return 999;
}
int is_label(char *label)
{
  int n = strlen(label);
  int i;
  for(i = 0; i < n; i++)
  {
    if(label[i] != '_' )
    {
      if(label[i] < 97 || label[i] > 123)
      {
        return 0;
      }
    }
  }
  return 1;
}

int is_ternary(char *code, int *val)
{
  int n = strlen(code);
  int i;
  *val = 0;
  for(i = 0; i < n; i++)
  {
    if(code[i] != '_' )
    {
      if(code[i] < 65 || code[i] > 91)
      {
        return 0;
      }
      else
      {
        if(code[i] >= 65 && code[i] <= 77)
        {
          /*
           * A to M is -13 to -1
           */
          *val = (*val * 27) + code [i]- 77;
        }
        else
        {
            if(code[i] >= 80 && code[i] <= 91)
            {
              /*
               * P to Z is 1 to 11
               */
               *val = (*val * 27) + code[i] - 79;
            }
            else
            {
              if(code[i] == 'O')
              {
                /*
                 * O is 0
                 */
                 *val = (*val * 27);
              }
              else
              {
                /*
                 * N is 12
                 */
                 *val = (*val * 27) + 12;
              }
            }
        }
      }
    }
    else
    {
      /*
       * value of '-' is 13
       */
      *val = (*val * 27) + 13;
    }
  }
  return 1;
}

int create_node(code_node **head, char *code)
{
  /*
   * inputs a line of code and create nodes of the linked list
   * to store the program
   */
  char * tok = strtok(code, " ");
  int offset = 3;
  int code_val;
  /*
   * first element must be the op_code
   */
  code_val = is_opcode(tok);
  if(code_val == 999)
  {
    /*
     * if not op_code return -1 for error
     */
    printf("Invalid opcode: %s\n", tok);
    return -1;
  }
  else
  {
    /*
     * create a node with the value of the opcode
     */
    create_node_code_code(head, code_val, 'O');
  }
  tok = strtok(NULL, " ");
  while(tok != NULL)
  {
    /*
     * checks if the next code is register
     */
    code_val = is_register(tok);
    if(code_val)
    {
      /*
       * if the code is register value add it to the list
       */
      create_node_code_code(head, code_val, 'R');
      offset += 3;
    }
    else
    {
      /*
       * check if the next code is is_ternary number
       */
      if(is_ternary(tok, &code_val))
      {
        create_node_code_code(head, code_val, 'V');
      }
      else
      {
        /*
         * creates the label node in the list
         */
        if(is_label(tok))
        {
          create_node_code_label(head, tok);
        }
        else
        {
          printf("Invalid Code: %s\n", tok);
        }
      }
      offset += 9;
    }
    tok = strtok(NULL, " ");
  }
  /*
   * returns the number of trits used by this line of code
   */
  return offset;
}
