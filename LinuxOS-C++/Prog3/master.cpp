/*
Mike Zeng
CECS 326
Assignment 3
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;

//message buffer used for the message queue
struct buf {
	long mtype; // required message type
	char mtext[50]; // message content
};

//made the buffer instance here to run it in main()
buf msg;

/*
This master program creates all the processes needed to run this assignment. Both children (sender and receiver) are generated here and accesses the same message queue throughout the program. The sender process executes first, then the receiver, then both children exits, and finally the message queue and then the parent are terminated. 
Input: none
Output: Child processes execute and exit, Message queue and parent terminated
Result: Sender and receiver access the message Queue to do IPC and then program ends
*/
int main() {
	//variables to hold children pids to print in the master process
	pid_t cpid1, cpid2;
	int qid = msgget(ftok("/Documents/hw/hw3",'a'), IPC_CREAT|0666);
   	cout << "Master, " << getpid() << " - Message queue ID: " << qid << endl;	
	/*
	Creates the first child process. This should be the sender. The sender process is executed by calling an exec function on its cpp file.
	*/
    pid_t cpid = fork();
	cpid1 = cpid;
	if (cpid == 0) {
        execlp("./sndClass", "./sndClass", (char*)NULL);
		exit(0);
	}
	/*
	Creates the second child process. This should be the receiver. The receiver process is executed through the exec call onto its cpp file.
	*/
	cpid = fork();
	cpid2 = cpid;
	if (cpid == 0) {
        execlp("./rcvClass", "./rcvClass", (char*)NULL);
		exit(0);
	}
	
	cout << "Master, " << getpid() << " - Sender Child PID: " << cpid1 << " | Receiver Child PID: " << cpid2 << endl;
	
	/*
	works the same as lab2. The parent process waits for both children to finish executing before the parent itself runs. First, the message queue is deleted by msgctl. Then it prints out that the queue has been deleted and prints that the parent with PID exits. The program is terminated when it gets to the exit() line.
	*/
	while(wait(NULL) != -1); // waiting for both children to terminate
		msgctl(qid, IPC_RMID, NULL); //removes message queue
		cout << "Master, " << getpid() << " -  Message queue removed." << endl <<"parent proc: " << getpid() << " now exits" << endl;
	exit(0);
}
