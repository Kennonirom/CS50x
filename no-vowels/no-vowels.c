// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string replace(string input);

//input word in the command line argument
int main(int argc, string argv[])
{
    //if no input display error
    if(argc != 2)
    {
        printf("error");
        return 1;
    }
    string word = argv[1];

    string result = replace(word);

    printf("%s\n", result);
}
 //replace a with 6 , e with 3 , o with 0, i with 1 and u does not change
string replace(string input)
{
    string output = input;

    for (int i = 0 ; i < strlen(input) ; i++)
    {
        char c = tolower(input[i]);

        switch (c)
        {
            case 'a':
                output[i] = '6';
                break;

            case 'e':
                output[i] = '3';
                break;

            case 'i':
                output[i] = '1';
                break;

            case 'o':
                output[i] = '0';
                break;

            default:
                output[i] = input[i];
                break;

        }

    }
    return output;

}