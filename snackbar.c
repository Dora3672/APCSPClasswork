/*
Dora Ding
November 30, 2022

Snackbar lab

1. add the item to the menu (add_item function)
    manually add the items and their prices to the menu

2. print the menu (for loop)

3. ask the user to input the order
    while true
        Message: "Enter a food item: "
        if the user does not type anything
            break

4. create a function to get the price of the item (needs the item as the input and output its price)
    for every item in the menu
        if the item and the current item in the menu mathces (without case sensitivity)
            return the price of that item
        else
            Message "Invalid Item \n"
            return 0

5. call the function everytime after the user type in a item and add that price to the total

6. print the total
*/

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
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10 //global constant

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
    // add the items in the menu to the menu
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    // print out the menu (for every item in the menu, print the item and the price)
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i]. price);
    }
    printf("\n");

    float total = 0; // variable for the total price of the order

    // will always be recurring until it breaks
    while (true)
    {
        string item = get_string("Enter a food item: "); // variable for the item the customer ordered
        // if the customer does not enter an item, break the loop
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        // update the total cost of the order by calling the get_cost function to find the price of that item
        total += get_cost(item);
    }

    // print the total price
    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first for items to the menu array
void add_items(void)
{
    // manually declaring the items and its price in the menu list
    menu[0].item = "Burger";
    menu[0].price = 9.50;

    menu[1].item = "Vegan Burger";
    menu[1].price = 11.00;

    menu[2].item = "Hot Dog";
    menu[2].price = 5.00;

    menu[3].item = "Cheese Dog";
    menu[3].price = 7.00;

    menu[4].item = "Fries";
    menu[4].price = 5.00;

    menu[5].item = "Cheese Fries";
    menu[5].price = 6.00;

    menu[6].item = "Cold Pressed Juice";
    menu[6].price = 7.00;

    menu[7].item = "Cold Brew";
    menu[7].price = 3.00;

    menu[8].item = "Water";
    menu[8].price = 2.00;

    menu[9].item = "Soda";
    menu[9].price = 2.00;

}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    // for every item in the menu
    for (int count = 0; count < NUM_ITEMS; count++)
    {
        // if the item ordered and the current item in the menu matches (strcasecmp is not case sensitive)
        if (strcasecmp(item, menu[count].item) == 0)
        {
            // return the price of that item
            return menu[count].price;
        }
    }

    // if the item is not in the menu, tell the customer that the item is invalid
    printf("Invalid Item \n");
    // since the item is not in the menu, the price is 0
    return 0;
}
