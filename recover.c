#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Ensure only one command line argument entered
    if (argc != 2)
    {
        fprintf(stderr, "Enter name of target recovery file as command line argument. Enter a single argument.\n");
        return 1;
    }

    // Open target recovery file (entered as command line argument)
    FILE *card = fopen(argv[1], "r");

    // Ensure target recovery file can be opened
    if (card == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    // Define BYTE structure
    typedef uint8_t BYTE;

    // Create a buffer array of size 512 BYTE (i.e, FAT)
    unsigned char buffer[512 * sizeof(BYTE)];

    // Initialise JPEG file counter
    int recoveredJPEGS = 0;

    // Initialise filename string
    char *filename = malloc(7 * sizeof(char));
    sprintf(filename, "%03i.jpg", recoveredJPEGS);

    // Initialise a file img to store JPEG
    FILE *img = fopen(filename, "w");

    // Loop through card until less than 1 FAT remaining
    while (fread(&buffer, sizeof(BYTE), 512, card) == 512)
    {
        // Determine the type of FAT block read
        // Case 1: FAT begins as a JPEG file
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            // Case 1.1: If first JPEG recovered
            if (recoveredJPEGS == 0)
            {
                // Write JPEG from buffer to outfile img
                fwrite(buffer, sizeof(BYTE), 512, img);

                // Record in JPEG counter
                recoveredJPEGS++;
            }

            // Case 1.2: If not first JPEG
            else
            {
                // Close current JPEG
                fclose(img);

                // Create a filename using JPEG counter
                sprintf(filename, "%03i.jpg", recoveredJPEGS);

                // Create a JPEG file
                img = fopen(filename, "w");

                // Write JPEG from buffer to outfile img
                fwrite(buffer, sizeof(BYTE), 512, img);

                // Record in JPEG counter
                recoveredJPEGS++;
            }
        }
        // Case 2: Not the beginning of a new JPEG
        // Case 2.1: If already recovering JPEG files
        else if (recoveredJPEGS > 0)
        {
            // Continue writing to current JPEG outfile img from buffer
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
    }
    free (filename);
}
