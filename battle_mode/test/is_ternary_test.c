
#include<stdio.h>
#include "../src/utils.h"

int helper(int expected, char *string)
{
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("%s %d\n", "Checking for value", expected);
    int value;
    if (!is_ternary(string, &value))
    {
        printf("%s %s\n", "unexpected error while processing ", string);
    }
    if (value != expected)
    {
        printf("Expected: %d got: %d\n", expected, value);
    }
    return 0;
}

int main()
{
    helper(12, "OON");
    helper(13, "OO_");
    return 0;
}