
#include<stdio.h>
#include "stdio.h"

int main()
{
  int ch;
  while(1)
  {
    scanf("%c ", &ch);
    switch(ch)
    {
      case '1':
      case '2':
      case 'q': break;
    }
  }
  return 0;
}
