// Assessing the readibility (in grades) of text using Coleman-Liau formula
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
// Get user input
    string user_text = get_string("Please type in the text you want assessed: ");
// Count the number of letters
    int letters = 0;
    for (int i = 0, n = strlen(user_text); i < n; i++)
    {
        if ((user_text[i] >= 'a' && user_text[i] <= 'z') || (user_text[i] >= 'A' && user_text[i] <= 'Z'))
        {
            letters++;
        }
        else {}
    }

// Count the number of sentences
    int sentences = 0;
    for (int i = 0, n = strlen(user_text); i < n; i++)
    {
        if (user_text[i] == '.' || user_text[i] == '!' || user_text[i] == '?')
        {
            sentences++;
        }
        else {}
    }

// Count the number of words
    int words = 0;
    for (int i = 0, n = strlen(user_text); i < n; i++)
    {
        if (user_text[i] == ' ')
        {
            words++;
        }
        else {}
    }
    words++;

// Calculate the Coleman-Liau index
    float CL_index = (0.0588 * 100 * letters / words) - (0.296 * 100 * sentences / words) - 15.8;
    if (CL_index >= 1 && CL_index <= 16)
    {
        printf("Grade %.0f\n", CL_index);
    }
    else if (CL_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}
