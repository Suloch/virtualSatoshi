#include "machine.h"
#include "instruction.h"
#include<stdio.h>

int mov(char * source, char * dest, int len)
{
  int  i;
  for(i = 0; i < len; i++)
  {
    dest[i] = source[i];
  }
  return 0;
}

int display(char *buffer, int len)
{
  int i;
  for(i = 0; i < len; i++)
  {
    fputc(buffer[i], stdin);
  }
}

int and(char* op, char *A, int len)
{
  int i;
  char res;
  for(i = 0; i < len; i++)
  {
    if(op[i] == '+' && A[i] == '+')
    {
      res = '+';
    }

    if(op[i] == '+' && A[i] == '0')
    {
      res = '0';
    }

    if(op[i] == '+' && A[i] == '-')
    {
      res = '-';
    }

    if(op[i] == '0' && A[i] == '+')
    {
      res = '0';
    }

    if(op[i] == '0' && A[i] == '0')
    {
      res = '0';
    }

    if(op[i] == '0' && A[i] == '-')
    {
      res = '0';
    }

    if(op[i] == '-' && A[i] == '+')
    {
      res = '-';
    }

    if(op[i] == '-' && A[i] == '0')
    {
      res = '0';
    }

    if(op[i] == '-' && A[i] == '-')
    {
      res = '+';
    }
    A[i] = res;
  }

  return 0;
}

int or(char* op, char *A, int len)
{
  int i;
  char res;
  for(i = 0; i < len; i++)
  {
    if(op[i] == '+' && A[i] == '+')
    {
      res = '+';
    }

    if(op[i] == '+' && A[i] == '0')
    {
      res = '+';
    }

    if(op[i] == '+' && A[i] == '-')
    {
      res = '0';
    }

    if(op[i] == '0' && A[i] == '+')
    {
      res = '+';
    }

    if(op[i] == '0' && A[i] == '0')
    {
      res = '0';
    }

    if(op[i] == '0' && A[i] == '-')
    {
      res = '-';
    }

    if(op[i] == '-' && A[i] == '+')
    {
      res = '0';
    }

    if(op[i] == '-' && A[i] == '0')
    {
      res = '-';
    }

    if(op[i] == '-' && A[i] == '-')
    {
      res = '-';
    }
  }

  return 0;
}
