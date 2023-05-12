#include "helpers.h"
#include <math.h>

// Convert image to grayscale 
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //comb through each row
    for (int i = 0; i < height; i++)
    {
        //comb through each column
        for (int j = 0; j < width; j++)
        {
            //converts pixel to float
            float Red  = image[i][j].rgbtRed;
            float Green  = image[i][j].rgbtGreen;
            float Blue  = image[i][j].rgbtBlue;

            //finds the average of the sum of all RGB
            int average = round((Red + Green + Blue) / 3);
            //set every RGB to the average
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //comb through each row
    for (int i = 0; i < height; i++)
    {
        //comb through each column
        for (int j = 0; j < width; j++)
        {
            //converts pixels to float
            float originalRed  = image[i][j].rgbtRed;
            float originalGreen  = image[i][j].rgbtGreen;
            float originalBlue  = image[i][j].rgbtBlue;

            //find the updated Pixel value
            //sepia filter / algrithm
            int sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            //update the pixel value sepiarRed, sepiaBlue , and sepiaGreen to not exceed 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            //update pixel values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //comb through each row
    for (int i = 0; i < height; i++)
    {
        //comb through each column
        for (int j = 0; j < width / 2; j++)
        {
            //puts the pixel in a temp array/ memory
            RGBTRIPLE temp = image[i][j];
            //moves the org img to the other side / mirrored side
            image[i][j] = image[i][width - (j + 1)];
            //moves the temp value with the value we are replacing it with
            //which is the flipped one
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of teh image
    RGBTRIPLE temp[height][width];

    //comb through each row
    for (int i = 0; i < height; i++)
    {
        //comb through each column
        for (int j = 0; j < width; j++)
        {
            //copies the orginal pixel to the temporary one
            temp[i][j] = image[i][j];

        }
    }

    //comb through each row
    for (int i = 0; i < height; i++)
    {
        //comb through each column
        for (int j = 0; j < width; j++)
        {
            int totalRed, totalBlue, totalGreen;
            totalRed = totalBlue = totalGreen = 0;
            float counter = 0.00;

            //get neighboring pixel
            //x and y is represented by relative position
            for (int x = -1; x < 2; x++)
            {
                //the box thing neighboring pixel
                for (int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    //check if neighboring pixel is valid
                    //whther it is in the edge or not
                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        continue;
                    }

                    //get image value
                    //need total sum of all valid pixels
                    totalRed += image[currentX][currentY].rgbtRed;
                    totalGreen += image[currentX][currentY].rgbtGreen;
                    totalBlue += image[currentX][currentY].rgbtBlue;

                    counter++;
                }

                //Calculate the average of neighboring pixels
                //blur pixel
                temp[i][j].rgbtRed = round(totalRed / counter);
                temp[i][j].rgbtGreen = round(totalGreen / counter);
                temp[i][j].rgbtBlue = round(totalBlue / counter);
            }
        }
    }

    // copy new pixels into original image
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
