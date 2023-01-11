/*
Dora Ding
January 9th, 2023

Day 32 File program challenge
*/

#include <stdio.h>
int main() {
        FILE * fp; //declare
        char c;
        char buff[255]; // create a buffer for reading the file

        printf("File Handling\n");
        //open a file for writing (deleted and rewrite the file, or if the file does not exist, create a blank)
        fp = fopen("demo.txt", "w");
        //writing operation
        while ((c = getchar()) != '\t')
        {
            fputc(c, fp);
        }
        //close file
        fclose(fp);

        printf("Data Entered:\n");
        //reading
        fp = fopen("demo.txt", "r");
        while ((c = getc(fp)) != EOF) //getc, get one character a time, EOF = end of file
        {
            printf("%c", c);
        }
        fclose(fp);
        printf("\n");


        printf("Adding to the File\n");
        //open a file for writing (add in the file)
        fp = fopen("demo.txt", "a");
        //writing operation
        while ((c = getchar()) != '\t')
        {
            fputc(c, fp);
        }
        //close file
        fclose(fp);

         printf("Data Entered After Appending:\n");
        //reading
        fp = fopen("demo.txt", "r");
        while ((c = getc(fp)) != EOF) //getc, get one character a time, EOF = end of file
        {
            printf("%c", c);
        }
        fclose(fp);
        printf("\n");

        //read one line of the file at the time
        fp = fopen("demo.txt", "r");
        int counter = 1; //counter for the number of lines
        //while the End-of-File is not reached
        while (fgets(buff, 255, fp) != NULL) //fgets: reads a line from the file and stores it into the string pointed to by buff (stops when either (n-1) characters are read, the newline character is read or the end of file is reached)
        {
            //print the line
            printf("%i : %s\n", counter, buff);
            //increase the counter
            counter++;
        }
        //close the file
        fclose(fp);
        printf("\n");

        return 0;
    }
