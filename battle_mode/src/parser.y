%{
  void yyerror(char *s);
  int yylex();

  #include<stdio.h>
  #include "symbol_table.h"
  #include "utils.h"
  #include "conversion.h"
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

   char pikachu[3][7] = {"PI", "PIKA", "PIKACHU"};
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
int ternary_to_pikachu(char trit)
{
  switch(trit)
  {
    case '+': return 2;
    case '0': return 1;
    case '-': return 0;
  }
  return -1;
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("No input file given");
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
  char value3[10];
  char value9[10];
  int i;
  FILE * fp = NULL;
  if(argc < 3)
  {
    fp = fopen("output", "w+");
  }
  else
  {
    fp = fopen(argv[2], "w+");
  }
  if(fp == NULL)
  {
    printf("unable to open output file\n");
    return 125;
  }
  while(head != NULL)
  {
    printf("+---------+\n");
    if(head -> node_type == 'C')
    {
      if(head -> code_type == 'O' || head -> code_type == 'R')
      {
        decimal_to_ternary(head -> value.code, value3, 3);
        for(i = 0; i < 3; i++)
        {
          fprintf(fp, "%s ", pikachu[ternary_to_pikachu(value3[i])]);
        }
        printf("|%9s|\n", value3); 
      }
      else
      {
        decimal_to_ternary(head -> value.code, value9, 9);
        for(i = 0; i < 9; i++)
        {
          fprintf(fp, "%s ", pikachu[ternary_to_pikachu(value9[i])]);
        }
        printf("|%9s|\n", value9); 
      }

    }
    else
    {
      printf("|%9s|\n", head -> value.label); 
    }
    printf("+---------+\n\n");

    head = head -> next;
  }
  for(i = 0; i < table_index; i++)
  {
    printf("%s -> %i\n", table[i].name, table[i].value);
  }
  fclose(fp);
}
void yyerror(char *e)
{
}
