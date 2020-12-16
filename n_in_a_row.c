///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission for CS 354 Fall 2020, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        n_in_a_row.c
// This File:        n_in_a_row.c
// Other Files:      NONE
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
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
char *DELIM = ",";  // commas ',' are a common delimiter character for data strings
     
/* COMPLETED:       
 * Retrieves from the first line of the input file,
 * the size of the board (number of rows and columns).
 * 
 * fp: file pointer for input file
 * size: pointer to size
 */
void get_dimensions(FILE *fp, int *size) {      
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, fp) == -1) {
        printf("Error in reading the file.\n");
        exit(1);
    }

    char *token = NULL;
    token = strtok(line, DELIM);
    *size = atoi(token);
}       
 
   
  
/* TODO:
 * Returns 1 if and only if the board is in a valid state.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * size: number of rows and columns
 */
int n_in_a_row(int **board, int size) {
    //case 1: 
    if (size % 2 == 0)
      return 0;
    //case 2:
    int numOfOne = 0;
    int numOfTwo = 0;
    for(int i = 0; i < size; i++){
	for(int j = 0; j < size; j++){
        if (*(*(board+i)+j) == 1)
	   numOfOne += 1;
	else if (*(*(board+i)+j) == 2)
	   numOfTwo += 1;
	}
     }
    if(numOfOne != numOfTwo && numOfOne != numOfTwo + 1)
      return 0;
   //case 3 and 4 :
    int winCntForX = 0;
    int winCntForO = 0;
    int continNumForX = 0;
   int continNumForO = 0;
   int totalWin = 0;
   //check row
   for(int i = 0; i < size; i++){
       for(int j = 0; j < size; j++){
            if(*(*(board+i)+j) == 1){
                continNumForX += 1;
            }
            else if(*(*(board+i)+j)  == 2){
                continNumForO += 1;
            }
          }
          //chether whether there is a row of X or O
          if(continNumForX == size){
            winCntForX += 1;
          }
          else if(continNumForO == size){
            winCntForO += 1;
          }
        continNumForX = 0;//reset the number for counting continue times
        continNumForO = 0;//reset the number for counting continue times
    }
    if(winCntForX > 1 || winCntForO > 1 || winCntForX + winCntForO > 1){
        return 0;//if there are two rows of single mark, it is invalid
    }
    if(winCntForX == 1 || winCntForO == 1){//check whether there is a win in row
        totalWin += 1;
    }
    winCntForX = 0;
    winCntForO = 0;
 
    //check column
   for(int i = 0; i < size; i++){
       for(int j = 0; j < size; j++){
            if(*(*(board+j)+i) == 1){
                continNumForX += 1;
            }
            else if(*(*(board+j)+i) == 2){
                continNumForO += 1;
            }
          }
          //chether whether there this is a column of X or O
          if(continNumForX == size){
            winCntForX += 1;
          }
          else if(continNumForO == size){
            winCntForO += 1;
          }
          continNumForX = 0;//reset the number for counting continue times
          continNumForO = 0;//reset the number for counting continue times
    }
    if(winCntForX > 1 || winCntForO > 1 || winCntForX + winCntForO > 1){
        return 0;//if there are two columns of single mark, it is invalid
    }
    if(winCntForX == 1 || winCntForO == 2){//check whether there is a win in column
        totalWin += 1;
    }
    winCntForX = 0;
    winCntForO = 0;
        
    //check back diagonal
    for(int i = 0; i < size; i++){
        if(*(*(board+i)+i) == 1){
            continNumForX += 1;
        }
        else if(*(*(board+i)+i) == 2){
            continNumForO += 1;
        }
    }
      //chether whether there this is a diagonal of X or O
        if(continNumForX == size){
            winCntForX += 1;
        }
        else if(continNumForO == size){
            winCntForO += 1;
        }
        continNumForX = 0;//reset the number for counting continue times
        continNumForO = 0;//reset the number for counting continue times
    if(winCntForX == 1 || winCntForO == 1){//check whether there is a win in diagonal
        totalWin += 1;
    }
    winCntForX = 0;
    winCntForO = 0;
    
    //check forward diagonal
    for(int i = 0; i < size; i++){
        if(*(*(board+i)+(size - i - 1)) == 1){
            continNumForX += 1;
        }
        else if(*(*(board+i)+(size - i - 1)) == 2){
            continNumForO += 1;
        }
    }
    //chether whether there this is a diagonal of X or O
    if(continNumForX == size){
        winCntForX += 1;
    }
    else if(continNumForO == size){
        winCntForO += 1;
    }
    if(winCntForX == 1 || winCntForO == 1){//check whether there is a win in diagonal
        totalWin += 1;
    }
    //check whether the case for win is reasonable
    if(totalWin > 2){
        return 0;
    }
    
    return 1;   
}    
  
 
   
/* PARTIALLY COMPLETED:
 * This program prints Valid if the input file contains
 * a game board with either 1 or no winners; and where
 * there is at most 1 more X than O.
 * 
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {              
     
    //TODO: Check if number of command-line arguments is correct.
    if(argc != 2)
    {    
	    fprintf(stderr,"Usage: ./n_in_a_row <input_filename>");
	    exit(1);
    }
    //Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    //Declare local variables.
    int size;

    //TODO: Call get_dimensions to retrieve the board size.
    get_dimensions(fp,&size);
    //TODO: Dynamically allocate a 2D array of dimensions retrieved above.
    int **matrix;
    matrix = malloc(sizeof(int*)*size);
    for (int i = 0; i < size; i++)
    {	  
        *(matrix+i) = malloc(sizeof(int)*size);
    }
       
    //Read the file line by line.
    //Tokenize each line wrt the delimiter character to store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading the file.\n");
            exit(1);
        }

        token = strtok(line, DELIM);
        for (int j = 0; j < size; j++) {
            //TODO: Complete the line of code below
            //to initialize your 2D array.
            *(*(matrix + i) + j) = atoi(token);
            token = strtok(NULL, DELIM);
        }
    }

    //TODO: Call the function n_in_a_row and print the appropriate
    //output depending on the function's return value.
    int result = 0;
    result = n_in_a_row(matrix, size);
    if (result == 1)
    {
       printf("valid\n");
    }
    else if (result == 0)
    {
       printf("invalid\n");
    }       
    //TODO: Free all dynamically allocated memory.
    for (int i = 0; i < size; i++)
    {
	free(*(matrix + i));
	*(matrix + i) = NULL;
    }
    free(matrix);
    matrix = NULL;
    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    } 
     
    return 0;       
}       



                                        // FIN
