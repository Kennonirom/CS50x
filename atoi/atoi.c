#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO

    int length = strlen(input);

    if(length == 1)
    {
        return input[0] - '0';
    }
    //to get the last digit of number in array
    char last_digit = input[length - 1];

    //converts the char into an int
    int converted_last_digit = last_digit - '0';

    //removes the last digit
    input[length-1] = '\0';

    // returns the numbers without the last digit
    return converted_last_digit + 10 * convert(input);

    return 1;

}