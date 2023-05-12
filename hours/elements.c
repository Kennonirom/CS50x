#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int numb[], int elements);

int main(void)
{
    int elements = get_int("How many elements? ");
    int numb[elements];

    for (int i = 0; i < elements; i++)
    {
        numb[i] = get_int("element -%i: ", i);
    }


    printf("Elements in array are; %i \n", calc_hours(numb, elements));
}

// TODO: complete the calc_hours function
float calc_hours(int numb[], int elements)
{
    //calculate average
    int sum = 0;

        for (int i = 0; i < elements; i++)
       {
        sum += grades[i];
       }

    // calculate total


}