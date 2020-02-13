typedef struct code_node
{
  char node_type ;
  union
  {
    int code;
    char * label;
  }value;
  struct code_node * next;
}code_node;

int create_node(code_node *, char *);
int create_node_code_code(code_node *, int);
int create_node_code_label(code_node *, char *);
