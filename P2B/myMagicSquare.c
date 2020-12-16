///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Fall 2020, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        myMagicSquare.c
// This File:        myMagicSquare.c
// Other Files:      None
// Semester:         CS 354 Fall 2020
//
// Author:           Zhan Yu
// Email:            zyu293@wisc.edu
// CS Login:         zhany
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:         None
//                   
//
// Online sources:   None
//                  
//                   
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;      // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
    printf("Enter magic square's size (odd integer >=3)");
    int n;
    scanf("%d", &n);
    if (n % 2 == 0){
	    printf("Size must be odd.\n");
	    exit(1);
    } else if (n < 3){
	    printf("Size must be >= 3.\n");
	    exit(1);
    }
    return n;   
} 
   
/* TODO:
 * Makes a magic square of size n using the alternate 
 * Siamese magic square algorithm from assignment and 
 * returns a pointer to the completed MagicSquare struct.
 *
 * n the number of rows and columns
 */
MagicSquare *generateMagicSquare(int n) {
    int row = n/2, column = n-1;//the place to put 1
    MagicSquare* pptr = malloc(sizeof(MagicSquare));
    pptr -> magic_square = malloc(sizeof(int*)*n);;
    pptr -> size = n;
    for(int j = 0; j < n; j++){
        *(pptr -> magic_square + j) = malloc(sizeof(int)*n);
    }
    //fill the square with 0
    for(int k = 0; k < n; k++){
      for(int j = 0; j < n; j++){
        *(*(pptr -> magic_square + k)+j) = 0;
      }
    }
        
    *(*(pptr -> magic_square + row) + column) = 1; //place 1 to central row and last column
    for(int i = 2; i <= n*n; i++){
        if((*(*(pptr -> magic_square + (row+1)%n)+(column+1)%n))== 0){//check whether the down-right is empty
            *(*(pptr -> magic_square + (row+1)%n)+(column+1)%n) = i;
            row = (row+1)%n;
            column = (column+1)%n;
        }else{//place the next number to the left
            *(*(pptr -> magic_square + row)+column-1) = i;
            column -= 1;
        }
    }
    
    return pptr;    
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
    //Open the file and check if it opened successfully.
    FILE *fp;
    fp = fopen(filename, "w");
    
    if (fp == NULL) {
        printf("Can't open file for writing.\n");
        fclose(fp);
        exit(1);
    }
    int num = magic_square->size;
    fprintf(fp,"%d\n",num);
    for(int i = 0; i < num; i++){
        for(int j = 0; j < num; j++){
        fprintf(fp,"%d",*(*(magic_square->magic_square + i)+j));
        if(j/(num-1) == 0){
            fprintf(fp, "%s", ",");
	}else{
            fprintf(fp, "%s", "\n");
	}
        }
    }
    //Free dynamically allocated memory.
    for (int i = 0; i < num; i++)
    {
	free(*(magic_square->magic_square + i));
	*(magic_square->magic_square + i) = NULL;
    }
    free(magic_square->magic_square);
    magic_square->magic_square = NULL;
    
    free(magic_square);
    magic_square = NULL;
    if (fclose(fp) != 0) {//close the file
        printf("Error while closing the file.\n");
        exit(1);
    } 
   
}

/* TODO:
 * Generates a magic square of the user specified size and
 * output the quare to the output filename
 */
int main(int argc, char *argv[]) {
   
    // TODO: Check input arguments to get output filename
    //Check if number of command-line arguments is correct.
    if(argc != 2)
    {    
        fprintf(stderr,"Usage: ./myMagicSquare <output_filename>");
	  exit(1);
    }
    // TODO: Get magin square's size from user
    int num = getSize();
    // TODO: Generate the magic square
    MagicSquare* info = generateMagicSquare(num);
    // TODO: Output the magic square
    fileOutputMagicSquare(info,*(argv+1));
    //Free dynamically allocated memory.
    info = NULL;
    return 0;
} 


                                                         
//				myMagicSquare.c      


