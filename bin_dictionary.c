    // Initialise an index for number of characters in word and for the dictionary word
    int word_char = 0;
    char dict_word[LENGTH + 1];

    // Read until end of dictionary
        // while(fread(&buffer, sizeof(char), 1, dict) == 1)
        // or
        // for (int c = fgetc(dict); c != EOF; c = fgetc(dict))
        {
        // Read strings from file one at a time
            // Allow only alphabetical characters and apostrophes (when not beginning of word)
            // if(&buffer != '\n')
            // if (isalpha(c) || (c == ''' && word_char > 0))
            // {
                 // Append character to word
                 // dict_word[word_char] = c;
                    // word_char++;
            // }
            // When a whole word recoreded
            // else if (c == '\n' && word_char >0)
            //{
 
            // Prepare for new word
            // word_char = 0;        
            
    // Check if dictionary loaded correctly
    return true;

    // Memory error
    return false;