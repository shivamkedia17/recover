#include <stdio.h>
#include <cs50.h>

//For CS50x from harvard.edu
//Credit (More Comfortable)
//Author - shivamkedia17 (GitHub)

/** This program checks if a given credit card number is valid.
    It is the implementation of the checksum function built into credit cards.
    If a credit card number is valid it  states the type of the credit card. 
    (Eg: Visa, Mastercard, American Express)                                */

//check() contains the code to implement the checksum function. It returns a boolean value.
bool check();
//type() returns the type of credit card
string type();

int main(void)
{
    //Taking input from the user
    long n = get_long("Number: ");
    //If the card no. is valid acc. to Luhn's algorithm, the type of the card is determined.
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
    //The loop chops two digits in every iteration 
    while (card_no != 0)
    {
        //a recursively stores the last two digits of the credit card number
        int a = card_no % 100;
        //product stores the left digit multiplied by 2
        int product = (a / 10) * 2;
        //even_sum stores the sum of the digits of product
        even_sum = even_sum + (product % 10) + (product / 10);
        //the right digit is the one that is not multiplied. It is stored in odd_sum
        odd_sum = odd_sum + (a % 10);
        //the last two digits are now deleted 
        card_no /= 100;
    }
    //digit_sum stores the final sum according to Luhn's algorithm
    int digit_sum = even_sum + odd_sum;
    //if the last digit of the sum is 0 then the credit card no. is syntactically correct
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
    //In each if block, x stores the first few digits of the card no.
    //for 13 digit numbers
    if (card_no / 10000000000000 == 0)
    {
        int x = card_no / 1000000000000000;
        if (x == 4)
        {
            return "VISA\n";
        }
    }
    //for 15 digit numbers
    else if (card_no / 1000000000000000 == 0)
    {
        int x = card_no / 10000000000000;
        if (x == 34 || x == 37)
        {
            return "AMEX\n";
        }
    }
    //for 16 digit numbers
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
