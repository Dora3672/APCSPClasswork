/*
Dora Ding
27 September 2022

This is day 10 assignment.

Prime numbers are defined as whole numbers greater than 1, whose only factors are 1 and itself.
So 3 is prime because its only factors are 1 and 3, while 4 is composite and not prime because it is the product of 2 × 2.
In this lab, you will write an algorithm to generate all prime numbers in a range specified by the user.

Hints
Modulo may come in handy, as it produces the remainder when dividing two integers.
By definition, 1 is not a prime number.
There is only one even prime number, 2.



Prompt the user to enter the lower bound (get_int)
Use do...while loop to make sure the lower bound is not a negative number
Message: "Please enter the lower bound: "

Prompt the user to enter the upper bound (get_int)
Use do...while loop to make sure the upper bound is bigger than the lower bound
Message: "Please enter the upper bound: "

Check every number in the list to see if the number is divisible by any number that is smaller than it (except for 1)
(for loop to repeat the checking procedure for every number in the range; for loop to repeat the dividing process for all number smaller than the number that is currently being checked)
(if statement: if the number is 0 or 1, the number is not prime; if the number is 2, the number is prime; else, do the checking process mentioned above)

If the number is a prime number, the number is print out.

Print out the total number of prime numbers.

*/

#include <stdio.h>
#include <cs50.h>

int main(void){

    int min; //this is the variable for the lower bound
    do{
        min=get_int("Please enter the lower bound: ");
    }
    while (min<0||min>2147483646);

    int max; //this is the variable for the upper bound
    do{
        max=get_int("Please enter the upper bound: ");
    }
    while (max<=min||max>2147483647);

    printf("\nPrime number(s) from %i to %i: \n", min, max); //printing the heading for the answers

    bool prime; //this is the variable for storing the result (whether the number is prime or not)
    int count; // this is the variable for keeping track of how many numbers are prime in the range

    //determining if each number in the range is prime or not
    for (int num=min; num<=max; num++) //num is the variable for the current number in the range that is being checked
    {
        if(num==0 || num==1) //determining when the number is 0 and 1, whether 0 and 1 are prime numbers or not (by definition, they are not)
        {
            prime=false;
        }

        else if (num==2) //determining when the number is 2, whether it is a prime number or not (it is prime)
        {
            prime=true;
        }

        else //determining whether other numbers are prime numbers or not
        {
            prime=true; //initializin the prime condition (assume every number is prime first since there are only conditions for determining that the number is not prime)

            //dividing all the numbers smaller than that number to see if it can be divided by numbers other than 1 or not
            for (int divisor=2; divisor<num; divisor++) //divisor is the variable for the current divisor of the number being checked
            {
                if(num%divisor==0) //if the number can be divided by another number other than 1 and the number itself, it is a composite number
                {
                    prime=false;
                }
            }
        }

        if (prime==true)
        {
            printf("%i\n", num); //print the number when the number is prime
            count=count+1; //total number of prime numbers increase by 1
        }
    }

    printf("\nTotal number of prime numbers: %i\n\n", count); //print the total number of prime numbers in the range

}
