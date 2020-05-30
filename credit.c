#include <stdio.h>
#include <cs50.h>

//For CS50x from harvard.edu
//Credit (More Comfortable)
//Author - shivamkedia17 (GitHub)

/** This program checks if a given credit card number is valid.*/

bool check();
string type();

int main(void)
{
    long n = get_long("Number: ");
// printf("%d\n", check(n));

    if (check(n) == 1)
    {
        printf("%s", type(n));
    }
    else
    {
        printf("INVALID\n");
    }
}

bool check(long card_no)
{
    int even_sum = 0;
    int odd_sum = 0;
    while (card_no != 0)
    {
        int a = card_no % 100;
        int product = (a / 10) * 2;
        even_sum = even_sum + (product % 10) + (product / 10);
        odd_sum = odd_sum + (a % 10);
        card_no /= 100;
    }
    int digit_sum = even_sum + odd_sum;
    if (digit_sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string type(long card_no)
{
    if (card_no / 10000000000000 == 0)
    {
        int x = card_no / 1000000000000000;
        if (x == 4)
        {
            return "VISA\n";
        }
    }
    else if (card_no / 1000000000000000 == 0)
    {
        int x = card_no / 10000000000000;
        if (x == 34 || x == 37)
        {
            return "AMEX\n";
        }
    }
    else if (card_no / 10000000000000000 == 0)
    {
        int x = card_no / 100000000000000;
        for (int i = 1; i <= 5; i++)
        {
            if (x == 50 + i)
            {
                return "MASTERCARD\n";
            }
        }
        if (x / 10 == 4)
        {
            return "VISA\n";
        }
    }
    return "INVALID\n";
}
