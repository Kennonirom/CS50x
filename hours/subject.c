#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int grades[], int subjects);

int main(void)
{
    int subjects = get_int("How many subjects? ");
    int grades[subjects];

    for (int i = 0; i < subjects; i++)
    {
        grades[i] = get_int("Subject %i grade: ", i);
    }


    printf("%.1f average\n", calc_hours(grades, subjects));
}

// TODO: complete the calc_hours function
float calc_hours(int grades[], int subjects)
{
    //calculate average
    int sum = 0;

        for (int i = 0; i < subjects; i++)
       {
        sum += grades[i];
       }
        return sum/ (float) subjects;
    // calculate total


}