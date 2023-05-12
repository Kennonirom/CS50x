// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    //asks input from the user

    do
    {
        n = get_int("Number of elements: ")
    }
    // prompts the user to input a positive num
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    //prints the max value
    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    //stores the max value
    int max_value = array[0];

    //a loop for the number of arrays
    for(int i = 0; i < n ; i++)
    {\
        //a condition wherein it will compare the stured max value
        //to the current array value
        if(max_value < array[i])
        {
            //changes the curretn max value
            //to a greater one
            max_value = array[i];
        }
    }
    //returns the new max value
    return max_value;
}
