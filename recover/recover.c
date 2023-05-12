#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check argument count is 2
    if (argc != 2)
    {
        printf("usage: ./recover IMAGE\n");
        return 1;
    }
    //open file for reading
    FILE *input_file = fopen(argv[1], "r");

    //check that input file is valid
    //if the inputed file cannot be found it will  read it as NULL
    //returns error
    if (input_file == NULL)
    {
        printf("could not open file");
        return 2;
    }

    //stores block of 512 bytes in an array
    //512 is the size of the jpg
    unsigned  char buffer[512];

    //track number of generated images
    int count_image = 0;

    //file pointer for recovered images
    FILE *output_file = NULL;

    //char filename[8]
    char *filename = malloc(8 * sizeof(char));

    // read the blocks of 512 bytes
    //a loop that reads the lost jpg
    while (fread(buffer, sizeof(char), 512, input_file))
    {
        //a condition if jpg is found
        if (buffer[0] == 0xff && buffer[1] ==  0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0))
        {
            //write the jpeg file names
            sprintf(filename, "%03i.jpg", count_image);

            // open output_file for writing
            output_file = fopen(filename, "w");

            //count number of images found
            count_image++;
        }
        //a codition for writing the file format
        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(char), 512, output_file);
        }
    }
    //frees up space
    free(filename);
    //closes teh files to avoid memory leaks
    fclose(output_file);
    fclose(input_file);

    return 0;

}