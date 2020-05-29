#include <stdio.h>
#include <cs50.h>

//For CS50x from harvard.edu 
//Mario (More Comfortable)
//Author - shivamkedia17 (GitHub)

/** This program generates two pyramids on the ground for mario. It has a space of two blocks in between.  */ 

int main(void)
{
    //Taking user input
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    /** Displaying the blocks albeit using '#'; In this section, we are generating the pyramids line by line using for loops */

    // The outer for loop generates a line.
    for (int i = 0; i < n; i++)
    {
        //Generating the left block
            
        //This for loop creates spaces in front of the left set of blocks
        for (int j = n - i - 1; j > 0; j--)
        {
            printf(" ");
        }
        
        //This for loop generates the blocks in the left set 
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }        
        
        //This line of code displays the spaces in between the two pyramids
        printf("  ");

        //Generating the right set of blocks
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        //After every line of code has been printed, this moves the cursor to the next line.
        printf("\n");
    }
}