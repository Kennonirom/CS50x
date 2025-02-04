// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number , symbol and atleast 6 characters long\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool checkLower = false;
    bool checkUpper = false;
    bool checkNumber = false;
    bool checkSymbol = false;
    bool checkLength = false;

    for(int i = 0; i < strlen(password); i++)
    {
       if(islower(password[i]))
       {
            checkLower = true;
       }
       if(isupper(password[i]))
       {
            checkUpper = true;
       }
       if(isdigit(password[i]))
       {
            checkNumber = true;
       }
       if(!isalnum(password[i]))
       {
            checkSymbol = true;
       }
       if(strlen(password) > 5)
       {
            checkLength = true;
       }
    }
    if(checkLower == true && checkUpper == true && checkNumber == true  && checkSymbol == true && checkLength == true)
    {
        return true;
    }

    return false;
}
