#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    //width is 8
    //a loop similar to the demo mario
    for (int row = 0; row < width; row++)
    {
        for (int column = 0; column < height; column++)
        {   //a condition taht checks whether the pixel is black
            if (image[column][row].rgbtBlue == 0 && image[column][row].rgbtGreen == 0 && image[column][row].rgbtRed == 0)
            {
                //if is black change the pixel to this color
                image[column][row].rgbtBlue = 48;
                image[column][row].rgbtGreen = 219;
                image[column][row].rgbtRed = 13;
            }
        }
    }
}

