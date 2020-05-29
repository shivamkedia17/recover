#include <stdio.h>
#include <cs50.h>

//For CS50x from harvard.edu 
//Hello
//Author - shivamkedia17 (GitHub)

/** This program says hello to the person whose name is entered.*/ 

int main(void)
{
    //Taking user input
    string name = get_string("Enter your name\n");
    
    //Saying hello to the name input
    printf("hello, %s\n", name);
}
