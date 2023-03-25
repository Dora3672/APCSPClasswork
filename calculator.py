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
    # inform the user to wait to find the best model
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

#########################
    time = datetime.datetime.now()
    print(time)

    # finding the best performing parameters for each model

    # linear regression
    # initialization
    lr = LinearRegression()
    # grid for grid search for the best parameter
    param_grid = {'fit_intercept': [True, False],
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
                  'max_iter': [100, 500, 1000]}
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
                  'random_state': [42],}
    # training
    grid = GridSearchCV(lasso, param_grid, cv=5, scoring='neg_mean_absolute_error')
    grid.fit(x_train, np.ravel(y_train))
    # store the best performing parameters
    best['lasso regression'] = [grid.best_params_, mean_absolute_error(y_test, grid.predict(x_test))]

    # random forest regressor
    # initialization
    rf = RandomForestRegressor()
    # grid for grid search for the best parameter
    param_grid = {'n_estimators': [10, 50, 100],
                  'max_depth': [10, 20],
                  'min_samples_split': [2, 3, 5],
                  'min_samples_leaf': [1, 2, 4]}
    # training
    grid = GridSearchCV(rf, param_grid, cv=5, scoring='neg_mean_absolute_error', n_jobs=-1)
    grid.fit(x_train, np.ravel(y_train))
    # store the best performing parameters
    best['random forest regressor'] = [grid.best_params_, mean_absolute_error(y_test, grid.predict(x_test))]

    # decision tree regressor
    # initialization
    dt = DecisionTreeRegressor()
    # grid for grid search for the best parameter
    param_grid = {'max_depth': [3, 4, 5, 6, 7],
                  'min_samples_split': [2, 3, 4],
                  'min_samples_leaf': [1, 2, 3]}
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
                  'gamma': [0.1, 1, 10, 100],
                  'kernel': ['linear', 'rbf', 'poly'],
                  'epsilon': [0.01, 0.1, 1, 10]}
    # training
    grid = GridSearchCV(sv, param_grid, cv=5, scoring='neg_mean_absolute_error', n_jobs=-1)
    grid.fit(x_train, np.ravel(y_train))
    # store the best performing parameters
    best['support vector regressor'] = [grid.best_params_, mean_absolute_error(y_test, grid.predict(x_test))]


    print(best)
#######################
    time = datetime.datetime.now()
    print(time)

    # best model type
    global model
    # parameters for the best performing model
    global bestpara

    return 0



# main function
once = False # whether it is the first run of the models or not

# print menu and ask for a menu option
option = menu() # the menu option the user chosen

# if first time chooses to predict brain stroke possibility
if option == 3 and once == False:
    # load data, clean data, find the best performing model (least mae)
    best()
    once = True
