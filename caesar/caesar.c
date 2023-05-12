#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    //if no input display error
    if (argc != 2)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
    //argv 1 must only coontain digits
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage ./caesar key\n");
            return 1;
        }

    }
    //connverts argv into an int not a digit string
    int k = atol(argv[1]);
    //gets the text to b ciphered 
    string plaintext  = get_string("plaintetx: ");

    printf("ciphertext: ");

    int cyphertext;

    for (int j = 0; j < strlen(plaintext); j++)
    {
        if (isupper(plaintext[j]))
        {
            printf("%c", (plaintext[j] - 65 + k) % 26 + 65);
        }
        else if (islower(plaintext[j]))
        {
            printf("%c", (plaintext[j] - 97 + k) % 26 + 97);
        }
        else
        {
            printf("%c", plaintext[j]);
        }
    }
    printf("\n");
}