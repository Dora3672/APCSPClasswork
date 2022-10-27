/*
Dora Ding
October 26, 2022

This is the password lab.
    Check that a password has at least one lowercase letter, uppercase letter, number and symbol

1. ask the user for the password (get_string)
Message: "Enter your password: "

2. create a function to check whether the input character is within the specific ASCII index (boolean function)
    needs the character, the starting and the ending index
    if the character is within the range
        return true

3. create a function to check whether the input password is valid or not (boolean function)
    needs the string password as the input
    using the check function (created in step 2) and check whether the character is within the uppercase letter range, lowercase letter range, number range and symbol range
        if the character is in one of the range
            that type is included in the password
    if all the types are included
        return true

4. call the function in step 3 to check whether the password is valid or not
    if yes
        "Your password is valid!\n" (printf)
    if no
        "Your password needs at least one uppercase letter, lowercase letter, number and symbol\n" (printf)
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//the boolean function to check whether the password is valid or not; needs the string as the input
bool valid(string password);
//the boolean function to find whether the character is within the specific ASCII range or not (check what type of character it is); needs the character and the start and ending number of ASCII index
bool check(char character, int min, int max);

int main(void)
{
    string password = get_string("Enter your password: "); //variable for the input password

    //check whether the password is valid or not with the valid function
    if (valid(password) == true)
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

//the boolean function to check whether the password is valid or not; needs the string as the input
bool valid(string password)
{
    bool u = false; //variable for whether there is at least one uppercase letter
    bool l = false; //variable for whether there is at least one lowercase letter
    bool n = false; //variable for whether there is at least one number
    bool s = false; //variable for whether there is at least one symbol
    for (int count = 0; count < strlen(password); count++)
    {
        //if the character is a specific type, that type turns true (meaning it is included); call the check function
        if (check(password[count], 33, 47) == true || check(password[count], 58, 64) == true || check(password[count], 91, 96)
            || check(password[count], 123, 126) == true)
        {
            s = true;
        }
        else if (check(password[count], 48, 57) == true)
        {
            n = true;
        }
        else if (check(password[count], 97, 122) == true)
        {
            l = true;
        }
        else if (check(password[count], 65, 90) == true)
        {
            u = true;
        }
    }

    //check whether the password has all the requirement
    if (u == true && l == true && n == true && s == true)
    {
        return true;
    }
    else
    {
        return false;
    }

}

//the boolean function to find whether the character is within the specific ASCII range or not (check what type of character it is); needs the character and the start and ending number of ASCII index
bool check(char character, int min, int max)
{
    //if the character is within that range, it is that type of character
    if (character <= max && character >= min)
    {
        return true;
    }
    else
    {
        return false;
    }
}
