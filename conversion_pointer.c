/*
Dora Ding
9 November 2022

Conversion Program

1. Ask the user for the number that needs to be converted (get_int; do while loop, the number needs to be a positive integer)
Message: "Please enter a number: "

2. Ask the user for the base the user wants to convert the number to (get_int, do while loop, the base needs to be 2, 8, or 16)
Message: "Please enter the base you want to convert the number to: "

3. Create a function to find the max power of the desired base the number can hold (int maxpower, needs the decimal number and the base of the converted number as inputs)
    calculate the number of times the number can be divided by the base (needs to update the number after each division) (while loop; while the base to the the current time power is less than or equal to the number)
    return the max power

4. Create a function for converting the number into another base (int *getArray, needs the decimal number and the base of the converted number as inputs)
    create a new array with a length of 32
    for each digit in the array (from 0 and to 31) place++
        num%base
        update the num by num/base
    return the converted number

5. Create a function to print the desirable array (void print, needs the converted number array, the base of the converted number and the length of the array as inputs)
    for every number in the array, index starts from length-1, index needs to be >= 0, index-- (prints backwards)
        print the digit with its corresponding hex digit (considering that hex digits include all digits)

6. Call the getArray function in the main to store it (with the input of the original number and the base) and print the array by calling the print function (with the converted number array, base and the maxpower)

7. Ask the user if they want to conver the same number into another base or not (get_char; do while loop, while the user says 'Y')
Message:"Do you want to do another conversion with the same number? (Y/N) "
    if 'Y',
    do step 2 and call the function in step 6

8. Ask the user if they want to convert another number or not (get_char; do while loop, while the user says 'Y')
Message:"Do you want to do another conversion with another number? (Y/N) "
    if 'Y',
    do steps 1 and 2, call the function in step 6, and do step 7

*/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int *getArray(int num, int type); //function to convert the number
int biggestpower(int num, int type); //function to find the maximum power the of the base the input number can fit (the length of the converted number)
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

            int *array; //variable for the converted number
            array = getArray(input, base); //convert the number with the desired base

            print(array, base, biggestpower(input, base)); //print the the converted number array (call the print function)

            printf("\n");
            another = get_char("Do you want to do another conversion with the same number? (Y/N) "); //ask whether the user wants to convert the number to another base or not
        }
        while (another == 'Y'); //convert to another base if the user wants to

        next = get_char("Do you want to do another conversion with another number? (Y/N) "); //ask whether the user wants to convert another number or not
        printf("\n");
    }
    while (next == 'Y'); //start again if the user wants to convert another number
}

//convert the number (needs the number that needs converting and the base the converted number needs to have)
int * getArray(int num, int type)
{
    static int array[32]; //create a new array for the converted number (max length = 32 digits)

    //convert the number, starting from the last place
    for (int place = 0; place < 32; place++) //place is the variable for the current digit the number is converting (backwards)
    {
        array[place] = num%type; //find the corresponding number for that place (by using modulus)
        num = num/type; //update the number
    }

    return array; //return the converted number array
}

//find the max power of the number (needs the number that needs converting and the base the converted number needs to have)
int biggestpower(int num, int type)
{
    int count = 0; //variable for the max power
    while (pow(type, count) <= num) //the max power is biggest power of that base the number can hold
    {
        count++; //update count
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
    // printing the number, for each digit in the array
    for(int digit = length - 1; digit >= 0; digit--) //loop is the variable for the current digit that is being printed (print backwards)
    {
        char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}; // hex is the hex conversion dictionary
        printf("%c", hex[arr[digit]]); //print the digit

    }
    printf("\n");
}
