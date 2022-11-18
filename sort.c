/*
Dora Ding
Timing sorting algorithm

1. let the user to input the file that is going to be sorted in the command-line argument

2. print the usage if there is not 2 comman-line arguments
Message "Usage: ./selection file_name.txt\n"
  return 1

3. create functions for selection, insertion and merge sort and return the time needed for sorting with that algorithm (needs the filename containing the list for sorting)

4. call the functions in the main and store the time into variables

5. compare the time and find the minimum one (if/else if/else statement)

6. print the most effective sorting algorithm and its sorting time
Message: "The most effective sorting algorithm is [the type] sort for the file.\nSort time: %f seconds\n", time

*/

#include <cs50.h>
#include <stdio.h>
#include <time.h>       // for time()
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//function to find the selection sort sort time; needs the filename containing the list for sorting
double selection(string filename);
//function to find the insertion sort sort time; needs the filename containing the list for sorting
double insertion(string filename);
//main function to find the merge selection sort sort time; needs the filename containing the list for sorting
double mmerge(string filename);

//merge sub-functon to merge two arrays
void merge(int arr[], int p, int q, int r);
//merge sub-functon to divide array
void mergeSort(int arr[], int l, int r);

//needs to command-line arguments (need to declare the file that needs to be opened)
int main(int argc, string argv[])
{
    //if there is not 2 command-line arguments, tell the user the right usage
    if (argc != 2)
    {
        printf ("Usage: ./sort file_name.txt\n");
        //tell the program something went wrong
        return 1;
    }

    //calculate the sort time of each algorithm for the selected file by calling the corresponding function
    //variable for the sort time for selection sort
    double stime = selection(argv[1]);
    //variable for the sort time for insertion sort
    double itime = insertion(argv[1]);
    //variable for the sort time for merge sort
    double mtime = mmerge(argv[1]);

    //compare the three sort times and tell the user which sort algorithm is most effective out of the three
    if (stime < itime && stime < mtime)
    {
        printf("The most effective sorting algorithm is selection sort for the file.\nSort time: %f seconds\n", stime);
    }
    else if (itime < stime && itime < mtime)
    {
        printf("The most effective sorting algorithm is insertion sort for the file.\nSort time: %f seconds\n", itime);
    }
    else
    {
        printf("The most effective sorting algorithm is merge sort for the file.\nSort time: %f seconds\n", mtime);
    }
}

//function to find the selection sort sort time; needs the filename containing the list for sorting
double selection(string filename)
{

    // variables for the start and end time of the run algorithm
    clock_t starttime, endtime;

    // variable for calculating total time of execution
    double totaltime;

    // variable for the incrementing array index for counting the number of numbers in the array
    int i = 0;
    // variable for the total number of numbers in the array
    int n = 0;
    // variable for the smallest number in the remaining array
    int min;
    // variable for the current index in the array that the min is comparing to
    int j;
    // variable for the index of the minimum number
    int index;

    // declaring array to store data from file
    int arr[100000];


    // declaring file pointer
    FILE* fptr;

    // opening the integer file.
    fptr = fopen(filename, "r");


    // scanning integer from file to array
    while (fscanf(fptr, "%d", &arr[i]) == 1)
    {

        // for counting the number of elements
        n++;

        // for incrementing the array index
        i++;
    }

    // logic for selection sort....

    // calculating clock when sorting starts..
    starttime = clock();

    for (i = 0; i < n - 1; i++) {
        //checking for the min in the remaining array
        min = arr[i];
        for (j = i + 1; j < n; j++) {
            if (arr[j] < min) {
                min = arr[j];
                index = j;
            }
        }

        // swapping the smallest number with
        // the current arr[i]th value
        //variable for the placeholder of the number that is bigger but is located at a small index
        int temp = arr[i];
        arr[i] = min;
        arr[index] = temp;
    }
    // selection sort logic ends here

    // calculating clock when sorting  ends
    endtime = clock();

    totaltime = ((double)(endtime - starttime)) / CLOCKS_PER_SEC;

    //return the total time needed for the sort program to run
    return totaltime;
}

//function to find the insertion sort sort time; needs the filename containing the list for sorting
double insertion(string filename)
{
    // variables for the start and end time of the run algorithm
    clock_t starttime, endtime;

    // variable for calculating total time of execution
    double totaltime;

    // declaring array to store data from file
    int arr[100000];

    // declaring file pointer
    FILE* fptr;

    // opening the integer file.
    fptr = fopen(filename, "r");

    //variable for the size
    int size = 0;
    //variable for the incremeted array index
    int i = 0;

    // scanning integer from file to array
    while (fscanf(fptr, "%d", &arr[i]) == 1)
    {

        // for counting the number of elements
        size++;

        // for incrementing the array index
        i++;
    }

    // logic for insertion sort....

    // calculating clock when sorting starts..
    starttime = clock();

    for (int step = 1; step < size; step++)
    {
        // variable for the current number that is comparing
        int key = arr[step];
        //variable for the index smaller than the current number (the index of the number to the left of current number)
        int j = step - 1;

        // Compare key with each element on the left of it until an element smaller than is found
        while (key < arr[j] && j >= 0)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
    // insertion sort logic ends here

    // calculating clock when sorting  ends
    endtime = clock();

    totaltime = ((double)(endtime - starttime)) / CLOCKS_PER_SEC;

    //return the total time needed for the sort program to run
    return totaltime;
}

//merge sort main function
//function to find the merge sort sort time; needs the filename containing the list for sorting
double mmerge(string filename)
{
    // variables for the start and end time of the run algorithm
    clock_t starttime, endtime;

    // variable for calculating total time of execution
    double totaltime;

    // declaring array to store data from file
    int arr[100000];

    // declaring file pointer
    FILE* fptr;

    // opening the integer file.
    fptr = fopen(filename, "r");

    //variable for the size
    int size = 0;
    //variable for the incremeted array index
    int i = 0;

    // scanning integer from file to array
    while (fscanf(fptr, "%d", &arr[i]) == 1)
    {

        // for counting the number of elements
        size++;

        // for incrementing the array index
        i++;
    }


    // logic for merge sort....

    // calculating clock when sorting starts..
    starttime = clock();

    mergeSort(arr, 0, size - 1);
    // merge sort logic ends here

    // calculating clock when sorting  ends
    endtime = clock();

    totaltime = ((double)(endtime - starttime)) / CLOCKS_PER_SEC;

    //return the total time needed for the sort program to run
    return totaltime;
}


// Merge sort sub-functions

// Merge two subarrays L and M into arr
void merge(int arr[], int p, int q, int r)
{

    // Create L ← A[p..q] and M ← A[q+1..r]
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1], M[n2];

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[p + i];
    }
    for (int j = 0; j < n2; j++)
    {
        M[j] = arr[q + 1 + j];
    }

    // Maintain current index of sub-arrays and main array
    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while (i < n1 && j < n2)
    {
        if (L[i] <= M[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = M[j];
        j++;
        k++;
    }
    }

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // m is the point where the array is divided into two subarrays
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted subarrays
        merge(arr, l, m, r);
    }
}
