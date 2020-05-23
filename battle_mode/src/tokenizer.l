%{
  #include "y.tab.h"
  #include <stdlib.h>
  #include <string.h>
  void yyerror(char *s);
  int yylex();
  char *copytext(char *text)
  {
    int length = strlen(text);
    char *new_text = malloc(length * sizeof(char) + 1);
    strcpy(new_text, text);
    return new_text;
  }

%}

Label [a-z_]
Code [A-Z_ ]

%x Comments

%%
"-"                                         {BEGIN(Comments); return COMMENT_START;}
<Comments>[^\n]*                            {yylval.string = yytext; return COMMENT;}
<Comments>[\n]                              {BEGIN(0); return COMMENT_END;}
":"                                         {return LABEL_END;}
{Code}+{Label}*                             {yylval.string = copytext(yytext); return CODE;}
{Label}*                                    {yylval.string = copytext(yytext); return LABEL;}
{Code}*                                     {yylval.string = copytext(yytext); return CODE;}
[ \t]                                       {return SPACE;}
[\n]                                        {return NEW_LINE;}
%%
int yywrap(void)
{
  return 1;
}
