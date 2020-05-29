#include <stdio.h>
#include <cs50.h>

//Mario (More Comfortable)

int main(void)
{
    //Taking user input
    int n; 
    do
    {
        n = get_int("Height: ");
    }while(n<1 || n>8);
    
    //Displaying the blocks
    
    for(int i = 0; i < n; i++)
    {
        for(int j = n - i - 1; j > 0; j--)
        {
            printf(" "); 
        }
        for(int j = 0; j <= i; j++)
        {
            printf("#");
        }
        
        printf("  ");
        
        for(int j = 0 ;j <= i; j++)
        {
            printf("#");
        }
        
        
        printf("\n");
    }
}