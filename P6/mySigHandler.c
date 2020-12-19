///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Fall 2020, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        mySigHandler.c
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

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

int count = 0;
time_t cur_time;
/*
 * signal handler
 */
void handler_SIGALRM() {
    
    time(&cur_time);
    printf("PID: %d | CURRENT TIME: %s", getpid(), ctime(&cur_time));
    alarm(3);
}

/**
 * the SIGUSR1 handler
 */

void handler_SIGUSR1() {
    count++;
    printf("SIGUSR1 handled and counted!\n");
}

/**
 * sigInt handler
 */

void handler_SIGINT() {
    printf("SIGINT handled.\n");
    printf("SIGUSR1 was handled %d times. Exiting now.\n", count);
    exit(0);
}

/**
 * Main function displays result of this program
 * @return 0
 */
int main() {
    printf("Pid and time print every 3 seconds.\n");
    printf("Enter Ctrl-C to end the program.\n");

    struct sigaction act;  // setting up sig alarm
    if (memset(&act, 0, sizeof(act)) == 0) {
        printf("Error with memset.\n");
        exit(0);
    }
    act.sa_handler = handler_SIGALRM;
    // triggering the alarm
    if (alarm(3) != 0) {
        printf("Error with alarm.\n");
        exit(0);
    }
    if (sigaction(SIGALRM, &act, NULL) != 0) {  // sig alarm
        printf("Error binding SIGALRM handler.\n");
        exit(1);
    }

    struct sigaction act2;  // setting up user1 signal
    if (memset(&act2, 0, sizeof(act2)) == 0) {
        printf("Error with memset.\n");
        exit(0);
    }
    act2.sa_handler = handler_SIGUSR1;
    if (sigaction(SIGUSR1, &act2, NULL) != 0) {  // sigusr1
        printf("Error binding SIGUSR1 handler.\n");
        exit(1);
    }

    struct sigaction act3;  // setting up sigint signal
    if (memset(&act3, 0, sizeof(act3)) == 0) {
        printf("Error with memset\n");
        exit(0);
    }
    act3.sa_handler = handler_SIGINT;
    if (sigaction(SIGINT, &act3, NULL) != 0) {  // sigint
        printf("Error binding SIGINT handler.\n");
        exit(1);
    }

    while (1) {
    }
}
