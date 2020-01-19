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
   * int to represent which pass of the parser is running
   * pass = 0 for creating the symbol table
   * pass = 1 for writing the output file
   */
  int pass = 0;
%}

%union {char *string;}
%start Program

%token COMMENT_START COMMENT_END SPACE NEW_LINE LABEL_END SPACE
%token <string> LABEL CODE COMMENT

%%

Program :                                                                       {}
          | Program Whitespace COMMENT_START COMMENT COMMENT_END                {}
          | Program Whitespace CODE Whitespace                                  {if(!pass){offset = offset + calculate_length($3);}}
          | Program Whitespace LABEL Whitespace LABEL_END Whitespace NEW_LINE   {if(!pass){if(find_symbol(table, SIZE, $3) == -1){set_symbol(table, table_index, $3, offset); table_index++;}}}
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
  yyparse();
}
void yyerror(char *e)
{
}
