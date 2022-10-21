/*
Dora Ding
Spetember 23, 2022

This is day 9 classwork.

You are eating out at a restaurant with a friend and want to split the bill evenly.
You may want to anticipate the amount you’ll owe before the bill arrives with tax added.
In this problem, you’ll complete a function to calculate the amount each of you owes based on the bill amount, the tax, and the tip.
Ask the user for the bill amount, the tax rate, and the tip rate!
Print the result as a bill.



Ask the user to enter the amount of bill before tax and tips, and if the entered bill is smaller than or equal to 0 dollar, reprompt the user to enter the bill amount
(do...while loop that breaks when the entered original bill is not smaller than or equal to 0)
Message: "Please enter the amount of the bill before tax and tips: "

Ask the user to enter the tax rate as a decimal, and if the entered tax rate is less than 0, reprompt the user to enter a tax rate
(do...while loop that breaks when the entered tax rate is not smaller than 0)
Message: "Please enter the tax rate as a decimal: "

Ask the user to enter the tip rate as a decimal, and if the entered tip rate is less than 0, reprompt the user to enter a tip rate
(do...while loop that breaks when the entered tip rate is not smaller than 0)
Message: "Please enter the tip rate as a decimal: "

Ask the user to enter the number of people, and if the entered number is less than 1, reprompt the user to enter the number of people
(do...while loop that breaks when the entered number is not smaller than 1)
Message: "Please enter the number of people splitting the bill: "

Create a function for calculating the amount of added money when given the rate and the original bill
float rate(float billamount, float rate)
billamount*rate
returns the calculated amount of added money

Calculate tax amount (float)
(call the function rate(original bill amount, tax rate))

Calculate tip amount (float)
(call the function rate(original bill amount, tip rate))

Calculate final bill (float)

Calculate the amount of bill per person (float)

Print the final bill
"\nBILL\nOriginal bill: $%.2f\nTax: $%.2f\nTips: $%.2f\nTOTAL: $%.2f\n\nPer Person: $%.2f\n\n", original bill, tax, tips, final bill, amount of bill per person

*/

#include <stdio.h>
#include <cs50.h>

float rate(float billamount, float rate); // function to find the amount base on rates

int main(void)
{
    float original; //This is the variable for the amount of bill before tax and tips
    do
    {
    original = get_float("Please enter the amount of the bill before tax and tips: $");
    }
    while (original<=0);

    float taxr; // This is the variable for tax rate
    do
    {
        taxr = get_float("Please enter the tax rate as a decimal: ");
    }
    while (taxr<0);

    float tipsr; // This is the variable for tip rate
    do
    {
        tipsr = get_float("Please enter the tip rate as a decimal: ");
    }
    while (tipsr<0);

    int num;// This is the variable for the number of people splitting the bill
    do
    {
        num = get_int("Please enter the number of people splitting the bill: ");
    }
    while (num<1);

    float tax = rate(original, taxr); // This is the variable for the amount of tax (call function to calculate tax)
    float tips = rate(original, tipsr); // This is the variable fo the amount of tips (call function to calculate tax)
    float bill = original+tax+tips; // This is the variable for the amount of bill after tax and tips
    float perperson = bill/num; // This is the variable for the amount of bill per person

    printf("\n\nBILL\n\nOriginal bill:  $%.2f\nTax:            $%.2f\nTips:           $%.2f\nTOTAL:          $%.2f\n\nPer Person:     $%.2f\n\n\n", original, tax, tips, bill, perperson);
}

// function to find the amount base on a given rate
float rate(float billamount, float rate)
{
    float amount = billamount*rate; // This is the variable for the amount calculated by the given rate
    return amount;
}
