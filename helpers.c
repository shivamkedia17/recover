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
        float red;
        float green;
        float blue;
    }
    SUM;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            SUM sum;
            sum.red = sum.blue = sum.green = 0;
            float count = 0;
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
            if ((i==height-1 &&(j%100==0 || j == 0)) || (i == 0 &&(j==0 || j % 100 == 0)) || (j==width-1 && (i==0 || i % 100 == 0)) || (i % 100 == 0 && j % 100 == 0))
            {
                printf("Pixel: %i,%i\n", i, j);
                printf("\n");
            }
            for (int k = start_i; k <= end_i; k++)
            {
                for (int l = start_j; l <= end_j; l++)
                {
                    if ((i==height-1 &&(j%100==0 || j == 0)) || (i == 0 &&(j==0 || j % 100 == 0)) || (j==width-1 && (i==0 || i % 100 == 0)) || (i % 100 == 0 && j % 100 == 0))
                    {
                        printf("%f %f %f\n", sum.red, sum.green, sum.blue);
                        printf("Count: %f\n", count);
                    }
                    sum.red += image[k][l].rgbtRed;
                    sum.green += image[k][l].rgbtGreen;
                    sum.blue += image[k][l].rgbtBlue;
                    count++;
                    if ((i==height-1 &&(j%100==0 || j == 0)) || (i == 0 &&(j==0 || j % 100 == 0)) || (j==width-1 && (i==0 || i % 100 == 0)) || (i % 100 == 0 && j % 100 == 0))
                    {
                        printf("%hhu %hhu %hhu\n", image[k][l].rgbtRed, image[k][l].rgbtGreen, image[k][l].rgbtBlue);
                        printf("%f %f %f\n", sum.red, sum.green, sum.blue);
                        printf("Count: %f\n", count);
                        printf("\n");
                    }
                }
            }
            image[i][j].rgbtRed = set(sum.red / count);
            image[i][j].rgbtGreen = set(sum.green / count);
            image[i][j].rgbtBlue = set(sum.blue / count);
            if ((i==height-1 &&(j%100==0 || j == 0)) || (i == 0 &&(j==0 || j % 100 == 0)) || (j==width-1 && (i==0 || i % 100 == 0)) || (i % 100 == 0 && j % 100 == 0))
            {
                printf("%hhu %hhu %hhu\n", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
                printf("\n");
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
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
