// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 378;

// Hash table
node *table[N];

// Initialise a dictionary size and bool for correct dictionary loading
int dict_size = 0;
bool dict_load = false;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");

    // Check if dictionary opened
    if (dict == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    // Initialise an index for the dictionary word and a temporary pointer
    char dict_word[LENGTH + 1];
    node *tmp = NULL;

    // Read one strting at a time until end of dictionary
    while(fscanf(dict, "%s", dict_word) != EOF)
    {
        // Get hash value for dictionary word
        int x = hash(dict_word);
        // printf("Hash value for word %s is %i\n", dict_word, x);

        // Dynamically allocate space for new node at hash value and check if there was enough memory to allocate it
        node *newnode = malloc(sizeof(node));
        if (newnode == NULL)
            return 1;

        // Initialize the new node
        strcpy(newnode->word, dict_word);
        newnode->next = NULL;

        // Update hash table with new node
        if (table[x] == NULL)
        {
            table[x] = newnode;
            free(newnode);
            // printf("Node created\n");
        }
        else if (table[x] != NULL)
        {
            newnode->next = table[x];
            table[x] = newnode;
            free(newnode);
            // printf("Node inserted\n");
        }
        dict_size++;
    }

    // Update global variable to record correct loading of dictionary
    dict_load = true;
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Initialise hash sum value
    int sum = 0;

    // For each letter in a word
    for (int j = 0; word[j] != '\0'; j++)
    {
        // Ensure only lowercase letters are hashed and update hash sum
        char temp = word[j];
        temp = tolower(temp);
        sum += temp - 30;
    }
    // Use mod of hash sum to obtain hash value
    return sum % N;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (dict_load == true)
    {
    // Return number of words in dictionary
    return dict_size;
    }

    else
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Obtain a hash value for word and go to corresponding linked list
    int y = hash(word);
    for (node* cursor = table[y]; cursor != NULL; cursor = cursor->next)
    {
        // Case-insensitive comparison
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
    }
    // If there is a next node - check it
   // else if (cursor->next != NULL)
     //   cursor = cursor->next;

    return false;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Free any memory allocated in load
    for (int i = 0; i < N; i++)
    {
        node* cursor = table[i];
        while (cursor->next != NULL)
        {
            node* tmp2 = cursor;
            cursor = cursor->next;
            free(tmp2);
        }
    free(table[i]);
    }
    return true;
}