/*
Dora Ding
January 13, 2023

File Practice
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{

    // This pointer will hold the
    // base address of the block created
    int* ptr; //pointer
    int n; //number of blocks
    int i;

    // Get the number of elements for the array
    printf("Enter number of elements:");
    scanf("%d",&n);
    printf("Entered number of elements: %d\n", n);

    // Dynamically allocate memory using malloc()
    ptr = (int*)malloc(n * sizeof(int));

    // Check if the memory has been successfully
    // allocated by malloc or not
    if (ptr == NULL) //NULL means not allocated, memory is not avalible, not enought, etc.
    {
        printf("Memory not allocated.\n");
        exit(0); //get out, finsh the progarm
    }
    else
    {

        // Memory has been successfully allocated
        printf("Memory successfully allocated using malloc.\n");

        // Get the elements of the array
        for (i = 0; i < n; ++i)
        {
            ptr[i] = i + 1;
        }

        // Print the elements of the array
        printf("The elements of the array are: ");
        for (i = 0; i < n; ++i)
        {
            printf("%d, ", ptr[i]);
        }
        printf("\n");
    }

    float* p; //pointer
    // Dynamically allocate memory using calloc()
    p = (float*)calloc(n, sizeof(float));
    // Check if the memory has been successfully
    if (p == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else
    {
        // Memory has been successfully allocated
        printf("Memory successfully allocated using calloc.\n");

        // Get the elements of the array
        for (i = 0; i < n; ++i)
        {
            p[i] = i * 1.25;
        }

        // Print the elements of the array
        printf("The elements of the array are: ");
        for (i = 0; i < n; ++i)
        {
            printf("%f, ", p[i]);
        }
        printf("\n");
    }

    //free the memory
    free(ptr);

    //resize the number of blocks
    n++;

    //dynamically re-allocate memory using realloc() for the other pointer
    p = realloc(p, n * sizeof(float));
    // Check if the memory has been successfully
    if (p == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else
    {
        //the already allocated blocks will not change (stay) and add on (memory might not be consecutive)

        // Memory has been successfully re-allocated
        printf("Memory successfully allocated using realloc with one more block.\n");

        // Print the elements of the array
        printf("The elements of the array are: ");
        for (i = 0; i < n; ++i)
        {
            printf("%f, ", p[i]);
        }
        printf("\n");
    }

    //free the memory
    free(p);

    return 0;
}
