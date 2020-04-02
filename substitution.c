#include <cs50.h>
#include <stdio.h>
#include <string.h>

// 26 letter key must be provided as a command-line argument
int main(int argc, string argv[])
{
// Check for command-line argument
    if (argc != 2)
    {
        printf("Use a single command-line argument\n");
        return(1);
    }

// Check if key contains only letters and each letter only once, make cypher uppercase
    int sum_key = 0;
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
        {
            argv[1][i] -= 32;
            sum_key += argv[1][i];
        }
        else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
        {
            sum_key += argv[1][i];
        }
        else
        {
           printf("Your key must contain only letters\n");
           return(1);
        }
    }
    if (sum_key != 2015)
    {
        printf("Your key must contain 26 letters and each letter only once\n");
        return(1);
    }

// Get user input
    string plaintext  = get_string ("plaintext: ");

// Transform user input
    printf ("ciphertext: ");
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            plaintext[i] -= 32;
            for (int j = 0; j < 26; j++)
            {
                if (plaintext[i] == alphabet[j])
                {
                    printf("%c", argv[1][j] + 32);
                }
            }
        }
        else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            for (int j = 0; j < 26; j++)
            {
                if (plaintext[i] == alphabet[j])
                {
                    printf("%c", argv[1][j]);
                }
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return(0);
}

