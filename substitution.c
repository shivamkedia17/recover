#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

//For CS50x from harvard.edu
//Substitution (more comfortable)
//Author - shivamkedia17 (GitHub)

/** This program accepts a key as a command line argument and some text.
 * It then encrypts the text according to the key if it is valid. */

//cipher accepts the key and encrypts the text
string cipher(string s, string key);

int main(int argc, string argv[])
{
    //Checking for proper cmd line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //checking if the key has a valid length
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        //checking for presence of invalid characters in key
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Invalid Characters in key.");
            return 1;
        }
        //checking for duplicate elements in key
        for (int j = i + 1; j < 26; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Duplicate Characters in key.");
                return 1;
            }
        }

    }
    //Changing key to Upper Case to maintain uniformity
    for (int i = 0; i < 26; i++)
    {
        argv[1][i] = toupper(argv[1][i]);
    }
    //Prompt user for input
    string input = get_string("plaintext:  ");
    //Printing the final output
    printf("ciphertext: %s\n", cipher(input, argv[1]));
    return 0;
}

string cipher(string s, string key)
{
    //Stores length of the text
    int l = strlen(s);
    //This loop encrypts the text character-wise
    for (int i = 0; i < l; i++)
    {
        //Checking if the character is an alphabet
        if (isalpha(s[i]) != 0)
        {
            bool caps = 1;
            //Checking if the alphabet is in lowercase
            if (s[i] >= 'a' && s[i] <= 'z')
            {
                caps = 0;
            }
            //letter is encrypted by changing it to UPPER case
            int index = (int)toupper(s[i]) - 65;
            s[i] = key[index];
            //If the letter was in lowercase it is changed back
            if (caps == 0)
            {
                s[i] = tolower(s[i]);
            }
        }
    }
    return s;
}
