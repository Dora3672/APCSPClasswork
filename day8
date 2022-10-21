/*
Dora Ding
09/20/2022

This is Day 8 Classwork.

1)Write a  Program to calculate the sum of first n natural numbers given by the user
 (Example: n=5    sum=1+2+3+4+5)  Pseudocode first
2) Can you write the same with a different kind of loop?
3) if you want to make sure the n is positive and no greater than a 2 bytes number what would you do?


First, prompt the user to enter a positive integer (use do...while loop for a number >0 and <2^16; use get_int)
Message: "Please enter a positive integer: "

Declare a sum variable

Then, add the sum of all natural numbers of the first n numbers (n is the number entered by the user) 
(use while loop to add n to the sum and minus 1 from n after each iteration, breaks when n=0)
OR
For loop counter=1 and <=num
    sum+=counter

Print the sum of the numbers.
Message: "The sum is %d\n", sum


*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n; // This is the variable for user input

    do
    {
        n = get_int("Please enter a positive integer: ");
    }
    while (n<=0 || n>361);

    int sum1=0; //This is the variable for the sum of all natural integers before the number the user inputted for the for loop

    for(int counter=1; counter<=n; counter++)
    {
        sum1+=counter;
    }

    printf("The sum is %i.\n", sum1);

    int sum=0; // This is the variable for the sum of all natural integers before the number the user inputted for the while loop

    while (n>0)
    {
        sum=sum+n;
        n--;
    }

    printf("The sum is %d.\n", sum);

}
