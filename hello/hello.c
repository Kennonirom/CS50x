#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // asks user for name input
    string name = get_string("What's your name? ");

    // print hellom name
    printf("hello, %s\n", name);
}
