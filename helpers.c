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
    // Loop over each pixel on the left-hand side of the image
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
            // Make RGB values floats
                image[i][k].rgbtRed = (float) image[i][k].rgbtRed;
                image[i][k].rgbtGreen = (float) image[i][k].rgbtGreen;
                image[i][k].rgbtBlue = (float) image[i][k].rgbtBlue;
            // Average target pixel value depending on number of added pixels

            // Case 1: corner pixels
            if ((i == 0) && (k == 0))
            {
                image[i][k].rgbtRed = (float) (imagetemp[i][k].rgbtRed + imagetemp[i][k+1].rgbtRed + imagetemp[i+1][k].rgbtRed + imagetemp[i+1][k+1].rgbtRed)/4;
                image[i][k].rgbtGreen = (float) (imagetemp[i][k].rgbtGreen + imagetemp[i][k+1].rgbtGreen + imagetemp[i+1][k].rgbtGreen + imagetemp[i+1][k+1].rgbtGreen)/4;
                image[i][k].rgbtBlue = (float) (imagetemp[i][k].rgbtBlue + imagetemp[i][k+1].rgbtBlue + imagetemp[i+1][k].rgbtBlue + imagetemp[i+1][k+1].rgbtBlue)/4;
            }

            else if ((i == 0) && (k == width-1))
            {
                image[i][k].rgbtRed = (float) (imagetemp[i][k-1].rgbtRed + imagetemp[i][k].rgbtRed + imagetemp[i+1][k-1].rgbtRed + imagetemp[i+1][k].rgbtRed)/4;
                image[i][k].rgbtGreen = (float) (imagetemp[i][k-1].rgbtGreen + imagetemp[i][k].rgbtGreen + imagetemp[i+1][k-1].rgbtGreen + imagetemp[i+1][k].rgbtGreen)/4;
                image[i][k].rgbtBlue = (float) (imagetemp[i][k-1].rgbtBlue + imagetemp[i][k].rgbtBlue + imagetemp[i+1][k-1].rgbtBlue + imagetemp[i+1][k].rgbtBlue)/4;
            }

            else if ((i == height-1) && (k == 0))
            {
                image[i][k].rgbtRed = (float) (imagetemp[i-1][k].rgbtRed + imagetemp[i][k].rgbtRed + imagetemp[i-1][k+1].rgbtRed + imagetemp[i][k+1].rgbtRed)/4;
                image[i][k].rgbtGreen = (float) (imagetemp[i-1][k].rgbtGreen + imagetemp[i][k].rgbtGreen + imagetemp[i-1][k+1].rgbtGreen + imagetemp[i][k+1].rgbtGreen)/4;
                image[i][k].rgbtBlue = (float) (imagetemp[i-1][k].rgbtBlue + imagetemp[i][k].rgbtBlue + imagetemp[i-1][k+1].rgbtBlue + imagetemp[i][k+1].rgbtBlue)/4;
            }
            else if ((i == height-1) && (k == width-1))
            {
                image[i][k].rgbtRed = (float) (imagetemp[i-1][k-1].rgbtRed + imagetemp[i-1][k].rgbtRed + imagetemp[i][k].rgbtRed + imagetemp[i][k-1].rgbtRed)/4;
                image[i][k].rgbtGreen = (float) (imagetemp[i-1][k-1].rgbtGreen + imagetemp[i-1][k].rgbtGreen + imagetemp[i][k].rgbtGreen + imagetemp[i][k-1].rgbtGreen)/4;
                image[i][k].rgbtBlue = (float) (imagetemp[i-1][k-1].rgbtBlue + imagetemp[i-1][k].rgbtBlue + imagetemp[i][k].rgbtBlue + imagetemp[i][k-1].rgbtBlue)/4;
            }
            // Case 2: edge pixels
            else if (i == 0 && k > 0 && k < width-1)
            {
                image[i][k].rgbtRed = (float) (imagetemp[i][k-1].rgbtRed + imagetemp[i][k].rgbtRed + imagetemp[i][k+1].rgbtRed + imagetemp[i+1][k-1].rgbtRed + imagetemp[i+1][k].rgbtRed + imagetemp[i+1][k+1].rgbtRed)/6;
                image[i][k].rgbtGreen = (float) (imagetemp[i][k-1].rgbtGreen + imagetemp[i][k].rgbtGreen + imagetemp[i][k+1].rgbtGreen + imagetemp[i+1][k-1].rgbtGreen + imagetemp[i+1][k].rgbtGreen + imagetemp[i+1][k+1].rgbtGreen)/6;
                image[i][k].rgbtBlue = (float) (imagetemp[i][k-1].rgbtBlue + imagetemp[i][k].rgbtBlue + imagetemp[i][k+1].rgbtBlue + imagetemp[i+1][k-1].rgbtBlue + imagetemp[i+1][k].rgbtBlue + imagetemp[i+1][k+1].rgbtBlue)/6;
            }
            else if (i == height-1 && k > 0 && k < width-1)
            {
                image[i][k].rgbtRed = (float) (imagetemp[i-1][k-1].rgbtRed + imagetemp[i-1][k].rgbtRed + imagetemp[i-1][k+1].rgbtRed + imagetemp[i][k-1].rgbtRed + imagetemp[i][k].rgbtRed + imagetemp[i][k+1].rgbtRed)/6;
                image[i][k].rgbtGreen = (float) (imagetemp[i-1][k-1].rgbtGreen + imagetemp[i-1][k].rgbtGreen + imagetemp[i-1][k+1].rgbtGreen + imagetemp[i][k-1].rgbtGreen + imagetemp[i][k].rgbtGreen + imagetemp[i][k+1].rgbtGreen)/6;
                image[i][k].rgbtBlue = (float) (imagetemp[i-1][k-1].rgbtBlue + imagetemp[i-1][k].rgbtBlue + imagetemp[i-1][k+1].rgbtBlue + imagetemp[i][k-1].rgbtBlue + imagetemp[i][k].rgbtBlue + imagetemp[i][k+1].rgbtBlue)/6;
            }
            if (k == 0 && i > 0 && i < height-1)
            {
                image[i][k].rgbtRed = (float) (imagetemp[i-1][k].rgbtRed + imagetemp[i-1][k+1].rgbtRed + imagetemp[i][k].rgbtRed + imagetemp[i][k+1].rgbtRed + imagetemp[i+1][k].rgbtRed + imagetemp[i+1][k+1].rgbtRed)/6;
                image[i][k].rgbtGreen = (float) (imagetemp[i-1][k].rgbtGreen + imagetemp[i-1][k+1].rgbtGreen + imagetemp[i][k].rgbtGreen + imagetemp[i][k+1].rgbtGreen + imagetemp[i+1][k].rgbtGreen + imagetemp[i+1][k+1].rgbtGreen)/6;
                image[i][k].rgbtBlue = (float) (imagetemp[i-1][k].rgbtBlue + imagetemp[i-1][k+1].rgbtBlue + imagetemp[i][k].rgbtBlue + imagetemp[i][k+1].rgbtBlue + imagetemp[i+1][k].rgbtBlue + imagetemp[i+1][k+1].rgbtBlue)/6;
            }
            else if (k == width-1 && i > 0 && i < height-1)
            {
                image[i][k].rgbtRed = (float) (imagetemp[i-1][k-1].rgbtRed + imagetemp[i-1][k].rgbtRed + imagetemp[i][k-1].rgbtRed + imagetemp[i][k].rgbtRed + imagetemp[i+1][k-1].rgbtRed + imagetemp[i+1][k].rgbtRed)/6;
                image[i][k].rgbtGreen = (float) (imagetemp[i-1][k-1].rgbtGreen + imagetemp[i-1][k].rgbtGreen  + imagetemp[i][k-1].rgbtGreen + imagetemp[i][k].rgbtGreen + imagetemp[i+1][k-1].rgbtGreen + imagetemp[i+1][k].rgbtGreen)/6;
                image[i][k].rgbtBlue = (float) (imagetemp[i-1][k-1].rgbtBlue + imagetemp[i-1][k].rgbtBlue + imagetemp[i][k-1].rgbtBlue + imagetemp[i][k].rgbtBlue + imagetemp[i+1][k-1].rgbtBlue + imagetemp[i+1][k].rgbtBlue)/6;
            }

            // Case 3: body pixels
            else if (i > 0 && i < height-1 && k > 0 && k < width-1)
            {
                image[i][k].rgbtRed = (float) (imagetemp[i-1][k-1].rgbtRed + imagetemp[i-1][k].rgbtRed + imagetemp[i-1][k+1].rgbtRed + imagetemp[i][k-1].rgbtRed + imagetemp[i][k].rgbtRed + imagetemp[i][k+1].rgbtRed + imagetemp[i+1][k-1].rgbtRed + imagetemp[i+1][k].rgbtRed + imagetemp[i+1][k+1].rgbtRed)/9;
                image[i][k].rgbtGreen = (float) (imagetemp[i-1][k-1].rgbtGreen + imagetemp[i-1][k].rgbtGreen + imagetemp[i-1][k+1].rgbtGreen + imagetemp[i][k-1].rgbtGreen + imagetemp[i][k].rgbtGreen + imagetemp[i][k+1].rgbtGreen + imagetemp[i+1][k-1].rgbtGreen + imagetemp[i+1][k].rgbtGreen + imagetemp[i+1][k+1].rgbtGreen)/9;
                image[i][k].rgbtBlue = (float) (imagetemp[i-1][k-1].rgbtBlue + imagetemp[i-1][k].rgbtBlue + imagetemp[i-1][k+1].rgbtBlue + imagetemp[i][k-1].rgbtBlue + imagetemp[i][k].rgbtBlue + imagetemp[i][k+1].rgbtBlue + imagetemp[i+1][k-1].rgbtBlue + imagetemp[i+1][k].rgbtBlue + imagetemp[i+1][k+1].rgbtBlue)/9;
            }
            // Round all RGB values to integers
                image[i][k].rgbtRed = (round(image[i][k].rgbtRed);
                image[i][k].rgbtGreen = (round(image[i][k].rgbtGreen);
                image[i][k].rgbtBlue = (round(image[i][k].rgbtBlue);
        }
    }
    free (imagetemp);
    return;
}
