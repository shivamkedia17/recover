#include "helpers.h"
#include <stdio.h>
#include <math.h>

int set(float x);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Finding average of Red, Green and Blue values
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0f;
            //Assigning the same value to Red, Green and Blue
            image[i][j].rgbtRed = set(average);
            image[i][j].rgbtGreen = set(average);
            image[i][j].rgbtBlue = set(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        int Red;
        int Green;
        int Blue;
    }
    COPY;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            COPY original;
            original.Red = original.Green = original.Blue = 0;
            original.Red = image[i][j].rgbtRed;
            original.Green = image[i][j].rgbtGreen;
            original.Blue = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = set(0.393 * original.Red + 0.769 * original.Green + 0.189 * original.Blue);
            image[i][j].rgbtGreen = set(0.349 * original.Red + 0.686 * original.Green + 0.168 * original.Blue);
            image[i][j].rgbtBlue = set(0.272 * original.Red + 0.534 * original.Green + 0.131 * original.Blue);
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
                start_i = i;
                end_i = i + 1;
            }
            else if (i == height - 1)
            {
                start_i = i - 1;
                end_i = i;
            }
            else
            {
                start_i = i - 1;
                end_i = i + 1;
            }
            if (j == 0)
            {
                start_j = j;
                end_j = j + 1;
            }
            else if (j == width - 1)
            {
                start_j = j - 1;
                end_j = j;
            }
            else
            {
                start_j = j - 1;
                end_j = j + 1;
            }
            /*if ((i==height-1 &&(j%100==0 || j == 0)) || (i == 0 &&(j==0 || j % 100 == 0)) || (j==width-1 && (i==0 || i % 100 == 0)) || (i % 100 == 0 && j % 100 == 0))
            {
                printf("Pixel: %i,%i\n", i, j);
                printf("\n");
            }*/
            for (int k = start_i; k <= end_i; k++)
            {
                for (int l = start_j; l <= end_j; l++)
                {
                    /*if ((i==height-1 &&(j%100==0 || j == 0)) || (i == 0 &&(j==0 || j % 100 == 0)) || (j==width-1 && (i==0 || i % 100 == 0)) || (i % 100 == 0 && j % 100 == 0))
                    {
                        printf("%i %i %i\n", sum.red, sum.green, sum.blue);
                        printf("Count: %i, k:%i l:%i\n", count, k, l);
                    }*/
                    count++;
                    sum.red += image[k][l].rgbtRed;
                    sum.green += image[k][l].rgbtGreen;
                    sum.blue += image[k][l].rgbtBlue;

                    /*if ((i==height-1 &&(j%100==0 || j == 0)) || (i == 0 &&(j==0 || j % 100 == 0)) || (j==width-1 && (i==0 || i % 100 == 0)) || (i % 100 == 0 && j % 100 == 0))
                    {
                        printf("%hhu %hhu %hhu\n", image[k][l].rgbtRed, image[k][l].rgbtGreen, image[k][l].rgbtBlue);
                        printf("%i %i %i\n", sum.red, sum.green, sum.blue);
                        printf("Count: %i\n", count);
                        printf("\n");
                    }*/
                }
            }
            image[i][j].rgbtRed = set((float)sum.red / count);
            image[i][j].rgbtGreen = set((float)sum.green / count);
            image[i][j].rgbtBlue = set((float)sum.blue / count);
            sum.red = sum.blue = sum.green = 0;
            count = 0;
            /*
            if ((i==height-1 &&(j%100==0 || j == 0)) || (i == 0 &&(j==0 || j % 100 == 0)) || (j==width-1 && (i==0 || i % 100 == 0)) || (i % 100 == 0 && j % 100 == 0))
            {
                printf("%hhu %hhu %hhu\n", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
                printf("\n");
            }
            */
        }
    }
    return;
}

int set(float x)
{
    if (x > 255)
    {
        return 255;
    }
    else
    {
        return (int)round(x);
    }
}
