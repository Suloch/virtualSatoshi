%{
  void yyerror(char *s);
  int yylex();

  #include<stdio.h>
  #include "symbol_table.h"
  #include "utils.h"

  /*
   * size of the table
   */
  #define SIZE 100

  /*
   * input file
   */
  extern FILE *yyin;

  /*
   * offset from the starting adress
   */
  int offset = 0;

  /*
   * symbol table
   * index to the next entry to be filled in the table
   */
  symbol table[100];
  int table_index = 0;

  /*
   * string to be stored in the file
   */
   char *output = NULL;
  
  /*
   * head of the program code
   */
   code_node *head = NULL;
%}

%union {char *string;}
%start Program

%token COMMENT_START COMMENT_END SPACE NEW_LINE LABEL_END
%token <string> LABEL CODE COMMENT

%%

Program :                                                                       {}
          | Program Whitespace COMMENT_START COMMENT COMMENT_END                {}
          | Program Whitespace CODE Whitespace                                  { offset = offset + create_node(&head, $3);}
          | Program Whitespace LABEL Whitespace LABEL_END Whitespace NEW_LINE   {
                                                                                  if(find_symbol(table, table_index, $3) == -1)
                                                                                  {
                                                                                    set_symbol(table, table_index, $3, offset);
                                                                                    table_index++;
                                                                                  }
                                                                                  else
                                                                                  {
                                                                                    yyerror($3);
                                                                                  }
                                                                                }
          | Program Whitespace NEW_LINE                                         {}
          ;
Whitespace:                                                                     {}
          | Whitespace SPACE                                                    {}
          ;

%%
int main(int argc, char **argv)
{
  if (argc < 1)
  {
    printf("No file given");
    return 123;
  }
  yyin = fopen(argv[1], "r");
  if(yyin == NULL)
  {
    printf("Cannot open the given file");
    return 124;
  }
  /*
   * create the symbol table
   */
  yyparse();

  while(head != NULL)
  {
    printf("+-------------------------------------+\n");
    if(head -> node_type == 'C')
    {
      printf("|%37i|\n", head -> value.code); 
    }
    else
    {
      printf("|%37s|\n", head -> value.label); 
    }

    printf("+-------------------------------------+\n");
    head = head -> next;
  }

}
void yyerror(char *e)
{
}
