// Dora Ding

// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10 //number of cities

typedef struct
{
    string city;
    int temp;
}
avg_temp; //struct name

avg_temp temps[NUM_CITIES]; //the array of cities and their average high temperature

void sort_cities(void);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort_cities(void)
{
    // variable for the max number
    int max;
    // variable for the index of the max number
    int index;

    // for every city
    for (int i = 0; i < NUM_CITIES; i++)
    {
        // assume the current city is the city with the max temperature
        max = temps[i].temp;
        index = i;
        // checking for the max in the remaining array
        for (int j = i + 1; j < NUM_CITIES; j++)
        {
            // if the temperature of this city is bigger than max, update the max and the index
            if (temps[j].temp > max)
            {
                max = temps[j].temp;
                index = j;
            }
        }

        // swapping the city with the max temperature with the current city
        // variable for the current city
        avg_temp place = temps[i];
        temps[i] = temps[index];
        temps[index] = place;
    }
}
