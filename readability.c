#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>

//For CS50x from harvard.edu
//Readability
//Author - shivamkedia17 (GitHub)

/** This program accepts some text and calculates the no. of letters, words and sentences present in it.
    It then suggests a grade for the readability of the text according to the Coleman-Liau index. */

//letters() counts the number of letters in a given block of text.
int letters();
//words() counts the number of words in a given block of text.
int words();
//letters() counts the number of sentences in a given block of text.
//Any string terminating with '.', '!' or '?' is considered sentence here.
int sentences();

int main(void)
{
    //Taking input from the user
    string text = get_string("Text: ");
    //Stores length of the text
    int l = strlen(text);

    //Ensuring there is a whitespace present at the end of the text so that the last word is counted.
    if (text[l - 1] != ' ')
    {
        char space[] = {' '};
        text = strcat(text, space);
        l++;
    }

    //Stores total no. of letters
    int nl = letters(l, text);
    //Stores total no. of words
    int nw = words(l, text);
    //Stores total no. of sentences
    int ns = sentences(l, text);
    //Calculates and stores the no. of letters per 100 words
    float L = nl * 100 / nw; 
    //Calculates and stores the no. of sentences per 100 words
    float S = ns * 100 / nw;
    //Formula for calculating the grade of a given block of text 
    float index = 0.0588 * L - 0.296 * S - 15.8;

    /*
    //Displays the number of letter(s)
    printf("%i letter(s)\n", nl);

    //Displays the number of word(s)
    printf("%i word(s)\n", nw);

    //Displays the number of sentence(s)
    printf("%i sentence(s)\n", ns);
    */  
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
        
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }
}

int letters(int l, string s)
{
    int n = 0;
    for (int i = 0; i < l; i++ )
    {
        if (isalpha(s[i]) != 0)
        {
            n++;
        }
    }
    return n;
}

int words(int l, string s)
{
    int n = 0;
    for (int i = 0; i < l; i++ )
    {
        if (isspace(s[i]) != 0)
        {
            n++;
        }
    }
    return n;
}

int sentences(int l, string s)
{
    int n = 0;
    for (int i = 0; i < l; i++ )
    {
        if(s[i] == '?' || s[i] == '!' || s[i] == '.')
        {
            n++;
        }
    }
    return n;
}
