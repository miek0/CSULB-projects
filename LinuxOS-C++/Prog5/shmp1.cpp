//Mike Zeng
//CECS 326-03
//Assignment 5
/* shmp1.cpp */

#include "registration.h"

using namespace std;

CLASS myclass = { "1001", "120119", "Operating Systems", 15 };

#define NCHILD	3
/*gives permission to the user and group that called sem_open of the same semaphore name to read and write the file
S_IRUSR | S_IWUSR allows the owner user to read and write file
S_IRGRP | S_IWGRP allows the shared group to read and write file
*/
#define sem_pshared (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

int	shm_init( void * );
void	wait_and_wrap_up( int [], void *, int );
void	rpterror( char *, char * );

/*
Parent process creates children process (3 of them) to execute shmc1.cpp until end condition is met. If the parent fails a fork call, the error is printed and the program is terminated. The parent process will wait while each child will run in the for loop to execute shmc1 until they are done, and then the control is passed back to the parent process. If a child fails to execute shmc1, an error is printed and the program terminates. After all children finished executing, the parent is done waiting and deletes the shared memory then exits.
*/
main(int argc, char *argv[])
{
	int 	child[NCHILD], i, shmid;
	void	*shm_ptr;
	char	ascshmid[10], pname[14];
	
	/*
	parent creates the semaphore
	sem_open creates a semaphore with a defined name
		name is defined in header file
		O_CREAT | O_EXCL creates a new unique semaphore
		pshared is defined for user or group processes to access it for reading or writing
		initial value of semaphore set to 1
	parent closes semaphore because the parent won't be using it, frees it up for other processes to use
	*/
	sem_t *sem = sem_open(sem_name, O_CREAT | O_EXCL, sem_pshared, 1);
	sem_close(sem);

	//creates the shared memory and saves id to shmid
	shmid = shm_init(shm_ptr);
	sprintf (ascshmid, "%d", shmid);

	//creates 3 child processes, each one executes the shmc1 file and accesses the same shared memory
	for (i = 0; i < NCHILD; i++) {
		child[i] = fork();
		switch (child[i]) {
		case -1:
			rpterror ("fork failure", pname);
			exit(1);
		case 0:
			sprintf (pname, "shmc%d", i+1);
			execl("shmc1", pname, ascshmid, (char *)0);
			perror ("execl failed");
			exit (2);
		}
	}
	
	//parent waits for children to finish running then deletes the shared memory
	wait_and_wrap_up (child, shm_ptr, shmid);	
	
	/*
	parent then unlinks the semaphore by name and then destroys it after all processes have used it.
	This runs after the parent has waited for all the children to finish executing.
	*/
	sem_unlink(sem_name);
}

/*
This function initializes a shared memory for processes to access in IPC. The shared memory these processes will access is based on the shmid which is pointed by the shm_ptr. The id is returned to the caller to let them know which/where the shared memory is for access.
*/
int shm_init(void *shm_ptr)
{
	//shared memory id
	int	shmid;

	/*
	A shared memory for System V is created here with shmget() and the int identifier is saved to shmid. In this case a new shared memory is created. The IPC key is created with ftok() with a general pathname and a char id of u. The size of the shared memory is the size of bytes the CLASS struct has. 0600|IPC_CREAT sets a bitwise or between the 2 parameters and sets the flag as such. 0600 allows access permissions for processes to use this shared memory and IPC_CREAT makes a new memory segmet for the shared memory to use.
	*/
	shmid = shmget(ftok(".",'u'), sizeof(CLASS), 0600 | IPC_CREAT);
	if (shmid == -1) {
		perror ("shmget failed");
		exit(3);
	}
	
	/*
	The shared memory pointer attaches System V shared memory segment to the assigned shared memory id shmid in shmat(). The address of the shm segment is the (void *) 0 parameter, allowing shmat to locate the address of the segment. The initial flag condition of the shm is set to 0 meaning the attached segment is allowed for read and write access. The returned address of the shm is saved to shm_ptr.
	*/
	shm_ptr = shmat(shmid, (void * ) 0, 0);
	if (shm_ptr == (void *) -1) {
		perror ("shmat failed");
		exit(4);
	}
	/*
	memccpy takes the byte size of the CLASS struct and copies it over from the source to the destination. The source of the memory area is the reference to the myclass CLASS object. The destination these bytes are sent to is pointed by the shm_ptr. 
	*/
	memcpy (shm_ptr, (void *) &myclass, sizeof(CLASS) );
	return (shmid);
}


/*
This function call (should be called by parent process) waits for all child processes to finish running and then detaches and deletes the shared memory used by the children. Passed as parameters are the array of child processes, the shared memory address, and the id of the shared memory. 
*/
void wait_and_wrap_up(int child[], void *shm_ptr, int shmid)
{
	int wait_rtn, w, ch_active = NCHILD;
	
	//waits for total children left running to hit 0, then proceeds to deleting the shared memory.
	while (ch_active > 0) {
		wait_rtn = wait( (int *)0 );
		for (w = 0; w < NCHILD; w++)
			if (child[w] == wait_rtn) {
				ch_active--;
				break;
			}
	}
	cout << "Parent removing shm." << endl;

	/*
	shmdt detaches the shared memory segment based on the address pointed by shm_ptr. The shmaddr must match the one in the shmat() call. Returns 0 upon success.
	*/
	shmdt (shm_ptr);
	/*
	shmctl performs control operations on the shared memory identified by the shmid. The command it executes is based on the cmd, in this case IPC_RMID, which removes the segment with the matching id. This destroys the shared memory that shmctl is pointed to.
	*/
	shmctl (shmid, IPC_RMID, (struct shmid_ds *) 0);
	
	//shm removed, now parent will begin to remove semaphore when this function ends
	printf("Parent removing semaphore.\n");
	exit (0);
}

/*
This method is only for the case of a fork() failure and a child process is unable to be created properly. Otherwise, it shouldn't be called.
*/
void rpterror(char *string, char *pname)
{
	char errline[50];

	sprintf (errline, "%s %s", string, pname);
	perror (errline);
}
