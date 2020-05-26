#include "helpers.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            // Calculate average brithness
            float gray = (float) (image[i][k].rgbtRed + image[i][k].rgbtGreen + image[i][k].rgbtBlue) / 3;

            // Assign average brightness to all RGB values
            image[i][k].rgbtRed = round(gray);
            image[i][k].rgbtGreen = round(gray);
            image[i][k].rgbtBlue = round(gray);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            // Calculate sepia red colour
            float sepiaRed = (float) ((0.393 * image[i][k].rgbtRed) + (0.769 * image[i][k].rgbtGreen) + (0.189 * image[i][k].rgbtBlue));
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            // Calculate sepia  green colour
            float sepiaGreen = (float) ((0.349 * image[i][k].rgbtRed) + (0.686 * image[i][k].rgbtGreen) + (0.168 * image[i][k].rgbtBlue));
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            // Calculate sepia blue colour
            float sepiaBlue = (float) ((0.272 * image[i][k].rgbtRed) + (0.534 * image[i][k].rgbtGreen) + (0.131 * image[i][k].rgbtBlue));
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Assing sepia colour values to pixel
            image[i][k].rgbtRed = round(sepiaRed);
            image[i][k].rgbtGreen = round(sepiaGreen);
            image[i][k].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Case 1: images of width of even number of pixels
    if (width % 2 == 0)
    {
    // Loop over each pixel on the left-hand side of the image
        for (int i = 0; i < height; i++)
        {
            for (int k = 0; k < width/2; k++)
            {
                // Calculate width of reflected pixel
                int newk = width - k - 1;

                // Save original RGB values
                RGBTRIPLE temp = image[i][k];

                // Adjust colour
                image[i][k] = image[i][newk];
                image[i][newk] = temp;
            }
        }
    }
    // Case 2: images of width of odd number of pixels
    else if (width % 2 != 0)
    {
    // Loop over each pixel on the left-hand side of the image, including the middle pixel
        for (int i = 0; i < height; i++)
        {
            for (int k = 0; k <= width/2; k++)
            {
                // Calculate width of reflected pixel
                int newk = width - k - 1;

                // Save original RGB values
                RGBTRIPLE temp = image[i][k];

                // Adjust colour
                image[i][k] = image[i][newk];
                image[i][newk] = temp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temp image file
    RGBTRIPLE(*imagetemp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            imagetemp[i][k] = image[i][k];
        }
    }

    // Loop over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            // Make RGB  floats
            float Red = (float) imagetemp[i][k].rgbtRed;
            float Green = (float) imagetemp[i][k].rgbtGreen;
            float Blue = (float) imagetemp[i][k].rgbtBlue;

            // Add all neighbouring pixels within image bounds
            if (i != 0 && k != 0)
            {
                Red += (float) imagetemp[i - 1][k - 1].rgbtRed;
                Green += (float) imagetemp[i - 1][k - 1].rgbtGreen;
                Blue += (float) imagetemp[i - 1][k - 1].rgbtBlue;

                Red += (float) imagetemp[i - 1][k].rgbtRed;
                Green += (float) imagetemp[i - 1][k].rgbtGreen;
                Blue += (float) imagetemp[i - 1][k].rgbtBlue;

                Red += (float) imagetemp[i][k - 1].rgbtRed;
                Green += (float) imagetemp[i][k - 1].rgbtGreen;
                Blue += (float) imagetemp[i][k - 1].rgbtBlue;
            }

            if (i != height - 1 && k != width - 1)
            {
                Red += (float) imagetemp[i][k + 1].rgbtRed;
                Green += (float) imagetemp[i][k + 1].rgbtGreen;
                Blue += (float) imagetemp[i][k + 1].rgbtBlue;

                Red += (float) imagetemp[i + 1][k].rgbtRed;
                Green += (float) imagetemp[i + 1][k].rgbtGreen;
                Blue += (float) imagetemp[i + 1][k].rgbtBlue;

                Red += (float) imagetemp[i + 1][k + 1].rgbtRed;
                Green += (float) imagetemp[i + 1][k + 1].rgbtGreen;
                Blue += (float) imagetemp[i + 1][k + 1].rgbtBlue;
            }

            if (i != 0 && k != width - 1)
            {
                Red += (float) imagetemp[i - 1][k + 1].rgbtRed;
                Green += (float) imagetemp[i - 1][k + 1].rgbtGreen;
                Blue += (float) imagetemp[i - 1][k + 1].rgbtBlue;

            }
            if (i != height - 1 && k != 0)
            {
                Red += (float) imagetemp[i + 1][k - 1].rgbtRed;
                Green += (float) imagetemp[i + 1][k - 1].rgbtGreen;
                Blue += (float) imagetemp[i + 1][k - 1].rgbtBlue;
            }

            // Average target pixel value depending on number of added pixels

            // Case 1: corner pixels
            if ((i == 0 || i == height - 1) && (k == 0 || k== width - 1))
            {
                Red /= 4;
                Green /= 4;
                Blue /= 4;
            }

            // Case 2: edge pixels
            if ((i == 0 || i == height - 1) && (k > 0 && k < width - 1))

            {
                Red /= 6;
                Green /= 6;
                Blue /= 6;
            }
            if ((i > 0 && i < height - 1) && (k == 0 || k == width - 1))
            {
                Red /= 6;
                Green /= 6;
                Blue /= 6;
            }

            // Case 3: body pixels
            if (i > 0 &&  i < height - 1 && k > 0 && k < width - 1)
            {
                Red /= 9;
                Green /= 9;
                Blue /= 9;
            }
            // Round all RGB values to integers
                image[i][k].rgbtRed = round(Red);
                image[i][k].rgbtGreen = round(Green);
                image[i][k].rgbtBlue = round(Blue);
        }
    }
    free (imagetemp);
    return;
}
