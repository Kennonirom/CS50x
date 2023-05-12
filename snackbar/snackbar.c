// Practice using structs
// Practice writing a linear search function

/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
// Adjust this value (10) number of items input below
#define NUM_ITEMS 10

// Menu itmes have item name and price
typedef struct
{
    string item;
    float price;
}
menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(void);

// Calculate total cost
float get_cost(string item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    //a loop for all the array
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        //prints all the items and prices in teh menu
        printf("%s: $%.2f\n", menu[i].item, menu[i]. price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        //asks input from teh user
        string item = get_string("Enter a food item: ");
        // acondition where in if the user has no input it will stop
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }
        // adds the all the rpices from the user input
        total += get_cost(item);
    }

    //prints the total sum
    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first for items to the menu array
void add_items(void)
{
    //array for the item and price
    menu[0].item = "Burger";
    menu[0].price = 9.5;

    menu[1].item = "Vegan Burger";
    menu[1].price = 11.0;

    menu[2].item = "Hot Dog";
    menu[2].price = 5.0;

    menu[3].item = "Cheese Dog";
    menu[3].price = 7.0;

    menu[4].item = "Fries";
    menu[4].price = 5.0;

    menu[5].item = "Cheese Fries";
    menu[5].price = 6.0;

    menu[6].item = "Cold Pressed Juice";
    menu[6].price = 7.0;

    menu[7].item = "Cold Brew";
    menu[7].price = 5.0;

    menu[8].item = "Water";
    menu[8].price = 2.0;

    menu[9].item = "Soda";
    menu[9].price = 2.0;
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    //a loop that will go through all the given array
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        //compares the input of the user with the array of .item
        if (strcasecmp(item, menu[i].item) == 0 )
        {
            //returns the price of that item
            return menu[i].price;
        }
    }
    return 0.0;
}
