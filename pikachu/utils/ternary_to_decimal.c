
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../src/utils.h"

int main()
{
  char ch;
  while(1)
  {
    char input[80];
    printf("%s\n", "1: ternary_to_decimal");
    printf("%s\n", "2: decimal_to_ternary");
    printf("%s\n", "3: ternary to pikachu");
    printf("%s\n", "q: quit");
    scanf("%c \n", &ch);
    switch(ch)
    {
      case '1': fgets(input, 80, stdin); printf("%d\n", ternary_to_decimal(input, strlen(input)-1)); break;
      case '2': fgets(input, 80, stdin); int num = atoi(input); decimal_to_ternary(num, input, 9); input[9] = '\0'; printf("%s\n", input); printf("%s\n", "123456789");break;
      case '3': fgets(input, 80, stdin); int i; for(i=0; i < strlen(input)-1; i++) if(input[i] == '-') printf("PI ");else if(input[i] == '0') printf("PIKA "); else printf("PIKACHU "); printf("\n"); break;
      case 'q': return 0;
    }
  }
}
