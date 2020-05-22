int decimal_to_ternary(int n, char *number, int len)
{
    /*
  function to convert decimal to ternary
  */
    char a, b, c;
    if (n < 0)
    {
        a = '+';
        b = '0';
        c = '-';
        n = -n;
    }
    else
    {
        a = '-';
        b = '0';
        c = '+';
    }
    int i = 0;
    for (i = 0; i < len; i++)
    {
        int digit = n % 3;
        switch (digit)
        {
        case 0:
            number[len - i - 1] = b;
            n = n / 3;
            break;
        case 1:
            number[len - i - 1] = c;
            n = n / 3;
            break;
        case 2:
            number[len - i - 1] = a;
            n = (n + 1) / 3;
            break;
        }
    }
    return 0;
}