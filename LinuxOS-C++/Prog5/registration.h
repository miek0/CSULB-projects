//Mike Zeng
//CECS 326-03
//Assignment 5

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <memory.h>
#include <semaphore.h>

#define sem_name "/shmsem"	//common semaphore named used between the processes

/*
I moved all included libraries to the shared header file including the defined semaphore name. This allows these to be used universally by any file that includes the registration.h file.
Most headers are IPC libraries for the shared memory used. 
The semaphore used for this is POSIX named semaphores.
*/

/*
*******SHM and SEMAPHORE HEADERS*****************
<sys/ipc> and <sys/shm> allows for processes to have IPC and a shared memory to access files between each other during the IPC. 
<sys/wait> simulates the waiting of processes between executions
<semaphore.h> gives access to POSIX semaphores (named and unnamed)
<sys/types> enables different data types to be used, for example sem_t to create a semaphore variable
<sys/stat> enables the read, write, search, and execute by owner, users, or group
<fcntl> enables files to be manipulated
*/

/*	
 *	Class struct that tracks the number of seats remaining in the class. The 3 char attributes are set in shmp1 during CLASS object initiation but were never used or printed in the console.
 */

struct CLASS {
	char class_number[6];	//set to 1001 
	char date[7];			//set to 120119
	char title[50];			//set to Operating Systems
	int seats_left;			//initially 15 seats available
};