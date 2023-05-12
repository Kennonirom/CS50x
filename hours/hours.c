#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    //asks the user for the number of arrays
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    //a loop that enable the user to input how many hours
    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        //asks the user if they want tthe total hours ot the average per week
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    // only accepts t and a as the input
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    //calculate average
    int sum = 0;
    if(output == 'A' )
    {
        //calculates the avrg
        for (int i = 0; i < weeks; i++)
       {
        sum += hours[i];
       }
        return sum/ (float) weeks;
    }

    else
    {
        //calculates the total
        for (int i = 0; i < weeks; i++)
       {
        sum += hours[i];
       }
        return sum;
    }


}