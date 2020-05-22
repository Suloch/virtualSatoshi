/*
 * node_type -> represents the type of the node 
 * C -> when the value of the node is known
 * L -> when there is a label and the value will be solved later
 * 
 * code_type -> represetns the type of the code value
 * O -> opcode and will take 3 trits
 * R -> register and will take 3 trirs
 * V -> value will take 9 trits
 */
typedef struct code_node
{
  char node_type ;
  char code_type;
  union
  {
    int code;
    char * label;
  }value;
  struct code_node * next;
}code_node;

int create_node(code_node **, char *);
int create_node_code_code(code_node **, int, char);
int create_node_code_label(code_node **, char *);