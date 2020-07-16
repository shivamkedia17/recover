#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Finding average of Red, Green and Blue values
            BYTE average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            //Assigning the same value to Red, Green and Blue
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    //Creating a copy of the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    //Copying every pixel from copy to the position where the pixel is to be relfected into the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = copy[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][width - j - 1].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        int red;
        int green;
        int blue;
    }
    SUM;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            SUM sum;
            sum.red = sum.blue = sum.green = 0;
            int count = 0;
            int start_i, end_i, start_j, end_j;
            //TODO;
            if (i == 0)
            {
                start_i = 0;
                end_i = 1;
            }
            else if (i == height - 1)
            {
                start_i = height - 2;
                end_i = height - 1;
            }
            else
            {
                start_i = i - 1;
                end_i = i + 1;
            }
            if (j == 0)
            {
                start_j = 0;
                end_j = 1;
            }
            else if (j == width - 1)
            {
                start_j = width - 2;
                end_j = width - 1;
            }
            else
            {
                start_j = j - 1;
                end_j = j + 1;
            }

            for (int k = start_i; k <= end_i; k++)
            {
                for (int l = start_j; l <= end_j; l++)
                {
                    sum.red += image[k][l].rgbtRed;
                    sum.green += image[k][l].rgbtGreen;
                    sum.blue += image[k][l].rgbtBlue;
                    count++;
                }
            }
            image[i][j].rgbtRed = sum.red / count;
            image[i][j].rgbtGreen = sum.green / count;
            image[i][j].rgbtBlue = sum.blue / count;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

