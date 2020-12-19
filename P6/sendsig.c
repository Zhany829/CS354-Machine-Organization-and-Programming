///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Fall 2020, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2013,2019-2020, Jim Skrentny, (skrentny@cs.wisc.edu)
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS354-Fall 2020, Deb Deppeler (deppeler@cs.wisc.edu) 
//
////////////////////////////////////////////////////////////////////////////////


#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Main function displays the result of the program
 * @param argc argument length of char array
 * @param argv argument char array
 * @return 0
 */
int main(int argc, char *argv[]) {
    //displays usage if argc not equal to 3
    if (argc != 3) {
        printf("Usage: <signal type> <pid>\n");
        exit(0);
    }
    if (strcmp(argv[1], "-i") == 0) {   //kill for SIGINT
        if (kill(atoi(argv[2]), SIGINT) == -1) {
            printf("Error for kill function.\n");
            exit(0);
        }
    } else if (strcmp(argv[1], "-u") == 0) {  //kill for SIGUSR1
        if (kill(atoi(argv[2]), SIGUSR1) == -1) {
            printf("Error for kill function.\n");
            exit(0);
        }
    } else {  // other cases
        printf("Invalid parameter\n");
        exit(0);
    }
    return 0;
}