/*
Dora Ding
October 31, 2022

No Vowel Lab

1. The user needs to type in 2 command-line arguments (the last one needs to be the word that will has its vowels replaced)
    if the user does not input 2 command-line arguments
        Message: "Please enter 2 command-line arguments\n"
        return 1 to indicate an error

2. Create a function to replace vowels of the word: needs the word as the input, will return the replaced word (string replace(string word))
    for every character in the string
        if the character is vowel
            replace that character with the corresponding number (except for u — it stays unchange)
    return the new replaced word

3. Create a variable to store the replaced word and call the the replace function and; input as the argv[2] (the input word in the command-line argument)

4. Print the replaced word
    Message "%s", replaced word

*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//function to replace the vowels in the word with numbers
string replace(string word);

//needs extra command-line argument as the input in addition to ./no-vowels
int main(int argc, string argv[])
{
    //only 2 command-line arguments needed, so if there the number of command-line arguments does not equal to 2
    if (argc != 2)
    {
        printf("Please enter 2 command-line arguments\n"); //print message to tell the user there is an error
        return 1; //tell the program there is an error and stop the program
    }

    //variable for the replaced word (call the replace function with the input word in the command-line argument)
    string word = replace(argv[1]);
    printf("%s\n", word); //print the replaced word
}

//function to replace the vowels in the word with numbers
string replace(string word)
{
    //for every character in the word (count is the variable for the current index of the character in the word that the program trys to check for/execute replacement)
    for (int count = 0; count < strlen(word); count++)
    {
        //if the character is a vowel, replace the vowel with the corresponding digit (except for u)
        if (tolower(word[count]) == 97)
        {
            word[count] = '6';
        }
        else if (tolower(word[count]) == 101)
        {
            word[count] = '3';
        }
        else if (tolower(word[count]) == 105)
        {
            word[count] = '1';
        }
        else if (tolower(word[count]) == 111)
        {
            word[count] = '0';
        }
    }

    return word; //return the replaced word
}
