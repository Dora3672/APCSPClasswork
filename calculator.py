import cs50 as cs
import pandas as pd
import numpy as np
# for the clear terminal function
import os
# for date
import datetime
# for numerical transformation
from sklearn.preprocessing import LabelEncoder
# for spiting training and testing sets of data
from sklearn.model_selection import train_test_split
# for models
from sklearn.pipeline import make_pipeline
# for the metrics evaluating the performance of models
from sklearn.metrics import mean_absolute_error
# for grid search for the best performing parameters for each model
from sklearn.model_selection import GridSearchCV
# models
from sklearn.linear_model import LinearRegression
from sklearn import linear_model
from sklearn.linear_model import Lasso
from sklearn.ensemble import RandomForestRegressor
from sklearn.tree import DecisionTreeRegressor
from sklearn.svm import SVR


# print menu and ask for option in the menu
def menu():
    # empty terminal
    os.system('clear')
    # print menu
    print(
        '''
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

                   Menu
   1) Instructions
   2) BMI Calculator
   3) Brain Stroke Possibility Calculator
   4) BMI Record
   5) Brain Stroke Possibility Record
   6) Exit

XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        '''
    )
    # ask for which option from the menu
    # make sure the opiton is valid
    while True:
        option = cs.get_int("Option: ")
        # check if the input of option is valid or not
        # if no, reprompt the user to input a option
        if option > 0 and option < 7:
            break
    # return the user option
    return option

# load data, clean data, find the best performing model (least mae)
def best():
    # clear terminal
    os.system('clear')
    # inform the user to wait to find the best modelw
    print('Loading calculator...')

    # load data
    file = open("brain_stroke.csv", 'r') # open the data file
    dataRaw = pd.read_csv(file) # read data file
    file.close()

    # clean data
    global data # varaible for all the desired data
    # only want data of adults who have known information for each characteristic
    data = dataRaw[(dataRaw['age'] >= 18) & (dataRaw['smoking_status'] != 'unknown')]
    # only want gender, age, hypertension, heart_disease, avg_glucose_level, bmi, smoking_status and stroke
    data = data.drop(['ever_married', 'work_type', 'Residence_type'], axis=1)

    # numerically transformation
    # gender
    le = LabelEncoder()
    le.fit(data['gender'])
    genderN = le.transform(data['gender'])
    '''
    0 = Female
    1 = Male
    '''
    # smoking status
    le = LabelEncoder()
    le.fit(data['smoking_status'])
    smokingN = le.transform(data['smoking_status'])
    '''
    0 = formerly smoked
    1 = never smoked
    2 = smokes
    '''

    # update the data sets with transformed numerical values
    data['gender'] = genderN
    data['smoking_status'] = smokingN

    # define X and Y
    x = data.drop('stroke', axis = 1)
    y = data.drop(['gender', 'age', 'hypertension', 'heart_disease', 'avg_glucose_level', 'bmi', 'smoking_status'], axis = 1)

    # split into training and testing sets
    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=10)

    # for storing the best mae and its parameters for each model
    best = {'linear regression':{}, 'ridge regression':{}, 'lasso regression':{}, 'random forest regressor':{}, 'decision tree regressor':{}, 'support vector regressor':{}}


    # finding the best performing parameters for each model

    # linear regression
    # initialization
    lr = LinearRegression()
    # grid for grid search for the best parameter
    param_grid = {'fit_intercept': [True, False],
                  'n_jobs': [1, 2, 4],
                  'positive': [True, False],}
    # training
    grid = GridSearchCV(lr, param_grid, cv=5, scoring='neg_mean_absolute_error')
    # prediction
    grid.fit(x_train, y_train)
    # store the best performing parameters
    best['linear regression'] = [grid.best_params_, mean_absolute_error(y_test, grid.predict(x_test))]

    # ridge regression
    # initialization
    rr = linear_model.Ridge()
    # grid for grid search for the best parameter
    param_grid = {'alpha': [0.001, 0.01, 0.1, 1, 10, 100],
                  'fit_intercept': [True, False],
                  'max_iter': [100, 500, 1000],
                  'positive': [True, False],
                  'tol': [0.001, 0.005, 0.01]}
    # training
    grid = GridSearchCV(rr, param_grid, cv=5, scoring='neg_mean_absolute_error')
    grid.fit(x_train, np.ravel(y_train))
    # store the best performing parameters
    best['ridge regression'] = [grid.best_params_, mean_absolute_error(y_test, grid.predict(x_test))]

    # lasso regression
    # initialization
    lasso = Lasso()
    # grid for grid search for the best parameter
    param_grid = {'alpha': [0.001, 0.01, 0.1, 1, 10, 100],
                  'fit_intercept': [True, False],
                  'max_iter': [1000, 5000],
                  'positive': [True, False],
                  'precompute': [True, False],
                  'random_state': [42],
                  'selection': ['cyclic', 'random'],
                  'tol': [0.001, 0.01],
                  'warm_start': [True, False]}
    # training
    grid = GridSearchCV(lasso, param_grid, cv=5, scoring='neg_mean_absolute_error')
    grid.fit(x_train, np.ravel(y_train))
    # store the best performing parameters
    best['lasso regression'] = [grid.best_params_, mean_absolute_error(y_test, grid.predict(x_test))]

    # random forest regressor
    # initialization
    rf = RandomForestRegressor()
    # grid for grid search for the best parameter
    param_grid = {'n_estimators': [50, 100, 150],
                  'max_depth': [2, 3, 4]}
    # training
    grid = GridSearchCV(rf, param_grid, cv=5, scoring='neg_mean_absolute_error', n_jobs=-1)
    grid.fit(x_train, np.ravel(y_train))
    # store the best performing parameters
    best['random forest regressor'] = [grid.best_params_, mean_absolute_error(y_test, grid.predict(x_test))]

    # decision tree regressor
    # initialization
    dt = DecisionTreeRegressor()
    # grid for grid search for the best parameter
    param_grid = {'max_depth': [3, 5, 7],
                  'min_samples_split': [2, 3, 4],
                  'min_samples_leaf': [1, 2, 3],
                  'max_leaf_nodes': [5, 10, 15]}
    # training
    grid = GridSearchCV(dt, param_grid, cv=5, scoring='neg_mean_absolute_error', n_jobs=-1)
    grid.fit(x_train, np.ravel(y_train))
    # store the best performing parameters
    best['decision tree regressor'] = [grid.best_params_, mean_absolute_error(y_test, grid.predict(x_test))]

    # support vectore regressor
    # initialization
    sv = SVR()
    # grid for grid search for the best parameter
    param_grid = {'C': [0.1, 1, 10, 100],
                  'epsilon': [0.01, 0.1, 1, 10]}
    # training
    grid = GridSearchCV(sv, param_grid, cv=5, scoring='neg_mean_absolute_error', n_jobs=-1)
    grid.fit(x_train, np.ravel(y_train))
    # store the best performing parameters
    best['support vector regressor'] = [grid.best_params_, mean_absolute_error(y_test, grid.predict(x_test))]

    # find the model with the least mae
    # sort the dictionary base on the model's mae
    best = dict(sorted(best.items(), key=lambda x: x[1][1]))

    global model # best model type
    # create a model for the one with lowest mae
    if next(iter(best.keys())) == 'linear regression':
        model = LinearRegression(**best['linear regression'][0])
    elif next(iter(best.keys())) == 'ridge regression':
        model = linear_model.Ridge(**best['ridge regression'][0])
    elif next(iter(best.keys())) == 'lasso regression':
        model = Lasso(**best['lasso regression'][0])
    elif next(iter(best.keys())) == 'random forest regressor':
        model = RandomForestRegressor(**best['random forest regressor'][0])
    elif next(iter(best.keys())) == 'decision tree regressor':
        model = DecisionTreeRegressor(**best['decision tree regressor'][0])
    else:
        model = SVR(**best['support vector regressor'][0])

    # clear terminal
    os.system('clear')

# running the options and return whether to continue or not
def run(option):
    # clear terminal
    os.system('clear')

    # if the user wants instructions
    if option == 1:
        print(
            '''
Welcome!

This calculator can help you calculate your BMI and your possibility of getting a brain stroke.
ATTENTION: This calculator can only calculate for adults.

If you choose option 2, you will receive your BMI after inputing your weight and height with the typeo f unit you want.
Please use the same unit type.
You can also see whether you are underweight, normal or overweight.
You can choose to store your BMI or not.

If you choose option 3, you will receive a possibility of you getting a brain stroke after inputing some of your personal health related information.
You will also be able to see how you can decrease your possibility of gettng a brain stroke.
You can choose to store this calculated possibility or not.
Note: You will also see your BMI.

If you choose option 4, you will see a record of your BMI.

If you choose option 5, you will see a record of your brain stroke possibilities.

After each option, you will be redirected back to the menu.

If you want to exit the calculator, press 6.

Hope you have a great time with the calculator and have a great day!

            '''
            )

        # prompt the user to go back to the menu
        input("Press return to go back to main menu")
        return False
    # if the user wants to calculate bmi only
    elif option == 2:
        # find the bmi
        bmi = calculateBMI()
        # print the bmi
        print(bmi)

        store = '' # whether to store the bmi or not
        # the input needs to be either 'y' for yes or 'n' for no
        while store.lower() != 'y' or store.lower() != 'n':
            # ask user
            store = cs.get_string("Do you want to store your bmi? (y/n) ")

        # if the user want to store
        if store.lower() == 'y':
            # ask for name
            name = cs.get_string("Name: ")
            # date
            date = datetime.datetime.now()
            # the new line that will appear in record
            printline = bmi + "\t" + name + "\t" + date.strftime('%m/%d/%Y') + "\n"

            # add the bmi to the record
            # open bmiRecord.txt
            with open("bmiRecord.txt", "a") as file:
                # add the new line
                file.write(printline)

        # prompt the user to go back to the menu
        input("Press return to go back to main menu")
        return False
    # if the user wants to calculate the brain stroke possibility
    if option == 3:
        bmi = calculateBMI() # bmi of the user

        hy = '' # temporary hypertension
        # the input needs to be either 'y' for yes or 'n' for no
        while hy.lower() != 'y' or hy.lower() != 'n':
            # ask user
            hy = cs.get_string("Do you have hypertension (y/n): ")
        # convert to nummber
        if hy.lower() == 'y':
            hypertension = 1
        else:
            hypertension = 0

        # prompt the user to go back to the menu
        input("Press return to go back to main menu")
        return False

# calculate BMI
def calculateBMI():
    im = '' # whether the user uses metric units or imperial units
    # can only be i for imperial or m for metric and only be 1 letter
    while im.lower() != 'i' or im.lower() != 'm':
        im = cs.get_string('Will you enter values with metric units (cm & kg) or imperial units (ftl & bs)? (m/i): ')

    height = 0 # the user's height
    # metric units
    if im.lower() == 'm':
        # ensure the height is positive integer
        while height <= 0:
            height = cs.get_int("Height(cm): ")
            # convert to meters
        height = height / 100
    # imperial units
    else:
        print("Please separate feet and inch with a space")
        h = '' # height in imperial units
        # checking the height is entered correctly
        while True:
            # need to have both ft and in
            while len(h.split()) != 2 and:
                h = cs.get_string("Height(ft in): ")
            terms = h.split() # split ft and in
            # ensure valid height input
            if terms[0] > 0 and terms[1] >= 0:
                break
        # conver to meters
        height = round((terms[0] / 3.281) + (terms[1] / 39.37 ), 2)

    weight = 0 # the user's weight
    # ensure the weight is positive integer
    while weight <= 0:
        # metric units
        if im.lower() == 'm':
            weight = cs.get_int("Weight(kg): ")
        # imperial units
        else:
            weight = cs.get_int("Weight(lbs): ")
            # convert to kg
            weight = round(weight / 2.205, 2)

    # calculate the bmi
    bmi  = weight / pow(height, 2)
    return bmi






# main function
once = False # whether it is the first run of the models or not
end = False # whether the user want to exit the program or not

# running the options
while end == False:
    # print menu and ask for a menu option
    option = menu() # the menu option the user chosen

    # if first time chooses to predict brain stroke possibility
    if option == 3 and once == False:
        # load data, clean data, find the best performing model (least mae)
        best()
        once = True

    # run the option
    end = run(option)
