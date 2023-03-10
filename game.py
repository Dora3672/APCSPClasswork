# Dora Ding
# Word game

# for the clear terminal function
import os
import cs50 as cs
# for random number
import random
# for date
import datetime

# print menu and ask for option in the menu
def menu():
    # empty terminal
    os.system('clear')
    # print menu
    print(
        '''
  XXXXXXXXXXXXXXXXX

        Menu
   1) Instructions
   2) Animals
   3) Food
   4) Score Board
   5) Exit

  XXXXXXXXXXXXXXXXX
        '''
    )
    # ask for which option from the menu
    # make sure the opiton is valid
    while True:
        option = cs.get_int("Option: ")
        # check if the input of option is valid or not
        # if no, reprompt the user to input a option
        if option > 0 and option < 6:
            break
    # return the user option
    return option

# split the score from the line and return that score
def get_score(line):
    return int(line.split("\t")[0])

# for updating the score
def scoreBoard(name, score, date):
    # the new line that will appear in scoreboard
    printline = str(score) + "\t" + name + "\t" + date.strftime('%m/%d/%Y') + "\n"

    # read the score baord
    file = open("score.txt", 'r') # the score board file
    lines = file.readlines() # read lines from the score board
    file.close()

    # add the new score to the score board list
    lines.append(printline)
    # sort the score board
    sortedlines = sorted(lines, key=get_score, reverse=True)

    # write the new score board
    file = open("score.txt", 'w')
    for line in sortedlines:
        file.write(line)
    file.close()

# letter input
def userInput():
    global guess
    # check if the guess is valid or not
    while True:
         try:
            guess = input(" Letter: ")
            # needs to be one single letter
            if guess.isalpha() and len(guess) == 1:
                guess = guess.lower()
                # need to be unique
                if guess not in correct and guess not in wrong:
                    break
                else:
                    print(" Another unique letter")
            else:
                print(" Only one letter")
         except ValueError:
             print(" Only one letter")

# running the options and return whether to continue or not
def run(option):
    # clear terminal
    os.system('clear')
    # if the user wants instructions
    if option == 1:
        print(
            '''
WELCOME!

In this game, you will first choose a category to guess the work from.
The categories are animals and food.
In menu, choose 2 or 3 to start a game with the category you wish.

While guessing, you will see the category you have chosen and the number of turns you are currently in on the top.
You will have a total of 10 guesses for each word.

You will input one letter for each round until either you guessed the word or have no more turns.
The letter you input needs to be different each turn.
If the word has a letter that appears more than one times, you will just need to input once.

If you guessed the word in 10 guesses, you will receive a score base on the length of the word and how many wrong guesses you have.
Then, you will be redirected to the menu.

To see the current top three in the score board, press 4. If the score are equal, the scores are sorted by date.
Then, you will be redirected to the menu.

If you want to exit the game, when you are in menu, press 5.

Hope you have a great game!
        '''
        )
        # prompt the user to go back to the menu
        input("Press return to go back to main menu")
        return False
    # when choose a category to play with
    elif option == 2 or option == 3:
        # ask for the name
        name = input("Name: ")
        print("\n")

        # current date
        date = datetime.datetime.now()

        category = option - 2 # varaible for the category number based on its index in the words 2D array
        # print category
        print("", words[category][0])

        # pick random word
        rand = random.randint(1, 6) # the index for the random word
        global word
        word = words[category][rand] # the random word that the user is guessing

        # initialize the input (showing the current guessed letters and underscores if the letters have not yet been guessed)
        inputs = '_' + ' _' * (len(word) - 1)

        # input from user
        global wrong # incorrect guesses
        wrong = ""
        global correct # correct guesses
        correct = ""
        right = 0 # number of correct letters guessed

        # game playing (total of 10 turns)
        for turn in range(10):
            # tell the user the current turn
            print("\n Turn:", (turn + 1), "/10")
            # print the current guess
            print("\n", inputs)

            # user input guess
            userInput()

            # check if in the word
            add = False # variable for whether to add the word or not
            for letter in range(len(word)):
                if guess == word[letter]:
                    inputs = inputs[:2 * letter] + guess + inputs[2 * letter + 1:]
                    add = True
                    right += 1

            # store the input guess (either as wrong/incorrect or correct )
            if add == True:
                correct = correct + guess
            else:
                 wrong = wrong + " " + guess

            # show the user previous wrong guesses
            print(" Not included:", wrong)
            print("\n")

            # if the user guessed the word correctly
            if right == len(word):
                print("\nAnswer:", word)
                # calculate score
                score = int(pow(len(word), 2) * 50 / ((len(wrong) + 1))) # score
                # extra congratulations for winning
                print("\n\nCongratulations! You win!")
                # tell the user the score
                print("\nScore: ", score, "\n")
                # add to the score board
                scoreBoard(name, score, date)
                break

        # if the user not guessed the word correctly
        if right != len(word):
            print("Answer:", word, "\n")
            print("Sorry, please try again!")

        # prompt the user to go back to the menu
        input("\nPress return to go back to main menu")
        return False
    # open score board and show the top 3
    elif option == 4:
        # print heading
        print("Score Board\n")

        # read the score baord
        file = open("score.txt", 'r')
        lines = file.readlines()
        file.close

        # if the number of people on the scoreboard is smaller than 3, print the number of scores on the scoreboard
        # print the first 3 on score board
        if len(lines) < 3:
            x = len(lines)
        else:
            x = 3
        for i in range(x):
            print(lines[i], end="")

        # prompt the user to go back to the menu
        input("\nPress return to go back to main menu")
        return False
    # if option == 5 (if the user want to quit the game)
    else:
        return True

# main
# lists of words for two categories
words = [['animals', 'ants', 'buffalo', 'camel', 'chicken', 'dolphin', 'penguin'],
          ['food', 'apple', 'peanut', 'chocolate', 'hamburger', 'marshmallow', 'onion']]

end = False # variable for if stop running or not
# game start
while end == False:
    # show menu and ask for option
    option = menu()
    # run the option
    end = run(option)
