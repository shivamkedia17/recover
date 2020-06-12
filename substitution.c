#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

string cipher(string s, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if(strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    string input = get_string("plaintext:  ");
    for (int i=0; i < 25; i++)
    {
        argv[1][i] = toupper(argv[1][i]);
    }
    printf("ciphertext: %s\n", cipher(input, argv[1]));
    return 0;
}

string cipher(string s, string key)
{
    string cipher = "";
    int l = strlen(s);
    for (int i = 0; i < l; i++)
    {
        bool caps = 1;

        if (s[i] >= 'a' && s[i] <= 'z')
        {
            caps = 0;
        }
        if (isalpha(s[i]) != 0)
        {
            int index = (int)toupper(s[i]) - 65;

            s[i] = key[index];

            if (caps == 0)
            {
                s[i] = tolower(s[i]);
            }
        }
    }

    return s;

}
