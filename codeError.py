# Dora Ding
# Code error

import os, random
os.system('clear')
''' This is a program to create a worg guessing game
all variables will be declared at the beginning of the program
Menu Function will create Menu'''
##Lists
HardestWords=["craziest", "Phenomenon", "Worcestershire","Sixth", "Mischievous","Draconian","Homogeneous","Laconic","Corroborate","Pragmatic"]
InterWords=["aggressive","futuristic","imagine","religion","produce","fraudulent","Japanese","diverse","entrepreneur","acknowledgement"]
EasyWords=["bananas", "grapes", "pharmacy", 'post office', 'apples', "cafeteria",
    "papaya", 'oranges', 'towers', 'mangos', 'kiwis','house' ]
#Variables
word=""
guess=""
#Function to select the word to guess
def selectWord(choice):
    global word        #it is global so the change will be accepted everywhere we use word
                        # global var do not need to be returned
    if '2' in choice:
        word=random.choice(EasyWords)
    elif '3' in choice:
        word=random.choice(InterWords)
    elif '4' in choice:
        word=random.choice(HardestWords)
    word=word.lower()


# print menu
def Menu():
    os.system('clear')
    print("####################################")
    print("#     Word Game for you            #")
    print("#       1 Instructions             #")
    print("#       2 Easy Words               #")
    print("#       3 Medium                   #")
    print("#       4 Difficult                #")
    print("#       5 Exit                     #")
    print("####################################")
    choice = input("Enter your choice ")
    os.system('clear')
    if '1' in choice:
        print("my instruction are not here but they will be soon :) !!!")
        input(" Press return to go back to main menu" )
        Menu()
    elif '5' in choice:
        print ("good Bye")
        exit()
    elif '3' in choice or '2' in choice or '4' in choice:
        selectWord(choice)
    else:
        print("Please enter a valid option")
        Menu()

#Function to control your user input
def getLetter():
    global guess
    check=True # whether to reprompt the user for another input or not
    while check:
        try:
            guess=input("\nenter a letter to guess the word ")
            if guess.isalpha() and len(guess)==1:
                guess=guess.lower()
                check=False
            else:
                print("only one letter please")
        except ValueError:
            print("only one letter please")

#Function to control the game( in the AP will be your main function to tal about it
def playing():
    turns=len(word)+2 # possible error turns
    guesses='' # correct guesses

    # while the game is running
    while (turns>0):
        # for every letter of the target word
        for letter in word:
            # if that letter is in the list of correct guesses, print that letter
            if letter in guesses:
                print(letter, end=" " )
            # or else print a place-holder for the letter, indicating that it is waiting to be guessed
            else:
                print ("_", end=" ")

        # ask the user for a input of letter
        getLetter()

        ### EDITED! (till line 127)
        # reset
        once = True # whether a correct letter is already inputed in the correct input list or not
        appear = False # whether the letter is correct or not

        # for every letter in the target word
        for letter in word:
            # if the input is guessed already
            if guess == letter:
                if once == True and guess in guesses:
                    print("You have used that letter before")
                # if the input guess is the letter and it is the first time the letter appears
                elif guess not in guesses:
                    # update the correctly guessed letter list
                    guesses += guess
                    once = False
                    appear = True
                    print("Good guess\n")
                # if the input guess is the letter and it is not the first occurance
                elif guess in guesses and once == False:
                    guesses += guess

        # if the input is not in the target word
        if not appear:
            # update chance
            turns -=1
            print("sorry guess again\n")

        # if the end of game and the word is right
        if len(guesses) == len(word):
            print("you guessed correctly. Your score is...")
            break
    # if incorrect
    if len(guesses) != len(word):
        # show the right answer
        print("Answer:", word, "\n")
        print("Sorry you did not guess correctly. Your score is ...")

    input("Press enter to countinue")
    # back to menu
    Menu()

### EDITED! (till line 144)
# while the game is playing
# need to repeat until end
first = True # whether it is the first run or not
while True:
    if first == True:
        first = False
        # print menu
        Menu()
    else:
        print(word)
        # start the game
        playing()
