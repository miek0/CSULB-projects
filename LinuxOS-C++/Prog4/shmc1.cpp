//Mike Zeng
//CECS 326-03
//Assignment 4
/* shmc1.cpp */

#include "registration.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <memory.h>
#include <semaphore.h>

using namespace std;

CLASS *class_ptr;
sem_t mutex;
void 	*memptr;
char	*pname;
int	shmid, ret;
void rpterror(char *), srand(), perror(), sleep();
void sell_seats();

/*
This function is the main execution for child processes to sell seats until there are no more seats left. If this file is executed on its own and not called by the child processes from shmp1.cpp, it will print out a Usage message. Otherwise the children will begin to "sell seats". If there is a memory pointer error from shmat, it will print out the error message and terminate this program.
*/
main(int argc, char* argv[])
{
	if (argc < 2) {
		fprintf (stderr, "Usage:, %s shmid\n", argv[0]);
		exit(1);
	}

	pname = argv[0];
	sscanf (argv[1], "%d", &shmid);
	sem_init(&mutex,0,1);
	/*
	Attaches a shared memory address to variable memptr. The address must match a shared memory segment with the id of shmid. shmat allows memptr to read and write to the memory segment with shmflag 0.
	*/
	memptr = shmat (shmid, (void *)0, 0);
	if (memptr == (char *)-1 ) {
		rpterror ("shmat failed");
		exit(2);
	}

	class_ptr = (struct CLASS *)memptr;

	sell_seats();

	/*
	Memory address memptr is detached from the shared memory segment it is allocated to. Returns 0 upon successful detach.
	*/
	ret = shmdt(memptr);
	exit(0);
	sem_destroy(&mutex);
}

/*
This function loops through the initiated child processes (3 in this case) and randomly selects one process to sell a seat. The processes are not ran in order. Each time a child sells a seat the overall seats left is decremented by 1 in the shared memory. Once all the seats are sold out from the shared memory, the child will print that no seats are left. After all children prints that no seats are left, the loop is ended, and the parent process takes over.
*/
void sell_seats() 
{
	int all_out = 0;
	
	srand ( (unsigned) getpid() );
	while ( !all_out) {   /* loop to sell all seats */
		sem_wait(&mutex);
		if (class_ptr->seats_left > 0) {
			sleep ( (unsigned)rand()%5 + 1);	
			class_ptr->seats_left--;
			sleep ( (unsigned)rand()%5 + 1);
			cout << pname << " SOLD SEAT -- " 
			     << class_ptr->seats_left << " left" << endl;
		}
		else {
			all_out++;
			cout << pname << " sees no seats left" << endl;	//all seats in shared memory runs out
		}
		sleep ( (unsigned)rand()%10 + 1); //sleep for random seconds or waits for next signal to execute before moving on to the next process
		sem_post(&mutex);
	}
}

/*
rpterror prints out an error message for the process that fails when shmat is called. The line of the error is printed in the terminal.
*/
void rpterror(char* string)
{
	char errline[50];

	sprintf (errline, "%s %s", string, pname);
	perror (errline);
}
