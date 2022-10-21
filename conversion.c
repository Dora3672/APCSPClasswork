/*
Dora Ding
19 October 2022

Conversion Program

1. Ask the user for the number that needs to be converted (get_int; do while loop, the number needs to be a positive integer)
Message: "Please enter a number: "

2. Ask the user for the base the user wants to convert the number to (get_int, do while loop, the base needs to be 2, 8, or 16)
Message: "Please enter the base you want to convert the number to: "

3. Create a function to find the max power of the desired base the number can hold (int findlength, needs the decimal number and the base of the converted number as inputs)
    calculate the number of times the number can be divided by the base (needs to update the number after each division) (while loop; while the base to the the current time power is less than or equal to the number)
    return the max power

4. Create a function to print the desirable array (void print, needs the array, the base of the converted number and the length of the array as inputs)
    for every number in the array, index starts from 0, index needs to be smaller than the length of the array, index++
        if the desired converted number is hex and the number is a two-digit number
            print the corresponding hex letter
        else if the printed digit is a number in the desirable base
            print the number in that index of the5432 array

5. Create a function for converting the number into another base (void getArray, needs the decimal number and the base of the converted number as inputs)
    calculate the length the array (call the findlength function)
    create a new array with that length
    for each place in the array, place starts from 0, place needs to smaller than the length of the array, place++
        num%base
        update the num by num/base
    print the array (call the print function)

6. Ask the user if they want to conver the same number into another base or not (get_char; do while loop, while the user says 'Y')
Message:"Do you want to do another conversion with the same number? (Y/N) "
    if 'Y',
    do step 2 and call the function in step 5

7. Ask the user if they want to convert another number or not (get_char; do while loop, while the user says 'Y')
Message:"Do you want to do another conversion with another number? (Y/N) "
    if 'Y',
    do steps 1 and 2, call the function in step 5, and do step 6

*/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

void getArray(int num, int type); //function to convert the number and also print (by calling the print function)
int findlength(int num, int type); //function to find the maximum power the of the base the input number can fit (the length of the converted number)
void print(int arr[], int type, int length); //function to print the array (the number)

int main(void)
{
    int input; //variable for the number the user input
    int base; //variable for the base the user input
    char another; //variable for whether the user wants to convert the same number into another base
    char next; //variable for whether the user wants to convert another number or not
    do{
        do
        {
            input = get_int("Please enter a decimal number: "); //ask the user for an input
        }
        while (input <= 0); //the input needs to be a positive integer

        do
        {
            do
            {
                base = get_int("Please enter the base you want to convert the number to: "); //ask the user for the base
            }
            while (base != 2 && base != 8 && base != 16); //the base needs to be 2, 8, or 16

            printf("\n%i convert to: \n", input); //print heading


            getArray(input, base); //convert and print the converted number with the desired base

            printf("\n"); //for aesthetic
            another = get_char("Do you want to do another conversion with the same number? (Y/N) "); //ask whether the user wants to convert the number to another base or not
        }
        while (another == 'Y'); //convert to another base if the user wants to

        printf("\n"); //for aesthetic
        next = get_char("Do you want to do another conversion with another number? (Y/N) "); //ask whether the user wants to convert another number or not
        printf("\n"); //for aesthetic
    }
    while (next == 'Y'); //start again if the user wants to convert another number
}

//convert the number (needs the number that needs converting and the base the converted number needs to have)
void getArray(int num, int type)
{
    int length = findlength(num, type); //find the length of the converted number (call the findlength function)
    int array[length]; //create a new array for the converted number

    //convert the number, starting from the last place
    for (int place = length-1; place >= 0; place--) //place is the variable for the current digit the number is printing
    {
        array[place] = num%type; //find the corresponding number for that place (by using modulus)
        num = num/type; //update the number
    }

    print(array, type, length); //print the array, the converted number (call the print function)
}

//find the max power of the number (needs the number that needs converting and the base the converted number needs to have)
int findlength(int num, int type)
{
    int count = 0; //variable for the max power
    while (pow(type, count) <= num) //the max power is biggest power of that base the number can hold
    {
        count++;
    }
    return count; //return the max power
}

//print the array (needs the array, the base the converted number have, and the length of the array)
void print(int arr[], int type, int length)
{
    //print heading
    if (type == 2){
        printf("Binary: ");
    }
    else if (type == 8)
    {
        printf("Octal: ");
    }
    else if (type == 16)
    {
        printf("Hex: ");
    }
    // printing the number, for each digit in the number, starting from the first one
    for(int digit = 0; digit < length; digit++) //loop is the variable for the current digit that is being printed
    {
        char hex[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'A', 'B', 'C', 'D', 'E', 'F'}; // hex is the hex conversion dictionary
        printf("%c", hex[arr[digit]]); //print the digit

    }
    printf("\n"); //for aesthetic
}
