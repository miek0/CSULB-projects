/*
Mike Zeng
CECS 326
Assignment 2
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
// declare my global message buffer
struct buf {
	long mtype; // required message type
	char greeting[50]; // message content
};

	/*
	child_proc_one takes in a qid as a parameter to find the message to receive from the message queue. It will msgrcv() it and prints out that the message is received and the message itself. Next the child_proc_one will create its own message, send that message back to the message queue, and prints out that the message is sent and will "exit" thus terminating child_proc_one, also printing out the status of the exit.
	*/
void child_proc_one(int qid) {
	buf msg;
	
	/*
	msgrcv takes a copy of the message from the message queue based on the qid and places it into the message buffer's message context (greeting[]) through the message pointer msgbuf. size is defined as the maximum size in bytes that the message buffer msg can hold. The mtype for this processor is initially at 113, meaning the first message in the Queue that matches 113 is received. The flag is set to 0 meaning the process is put on hold until the matching msgtyp is received. Because it will be on hold until mtype 113 has a message, this  allows child_proc_two to run first to put message of mtype 113 into the msgQ before child_proc_one's msgrcv is run. 
	*/
	
	int size = sizeof(msg)-sizeof(long);
	msgrcv(qid, (struct msgbuf *)&msg, size, 113, 0);
	cout << getpid() << ": gets message" << endl;
	cout << "message: " << msg.greeting << endl;
	strcat(msg.greeting, " and Adios.");
	cout << getpid() << ": sends reply" << endl;
	
	/*
	msgsnd appends a copy of the message pointed by msgbuf and stores it into the message queue by the passed qid. Like msgrcv, the parameters are similar and except the lack of the mtype as a parameter. The mtype is set to 114 prior to msgsnd, and it will be the msgtyp that will need to be matched by msgrcv to retreive the message from the queue. The byte size of the message is based on the int size. The flag is set to 0 which will make the process wait until the mtype of the message is matched in the queue to send the message. 
	*/
	
	msg.mtype = 114; // prepare message with type mtype = 114
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	cout << getpid() << ": now exits" << endl;
}

	/*
	child_proc_two works similar to child_proc_one with a few additions in that process two will first send a message that will never be read because the mtype of the message will not be found within the message queue. However, since child_proc_two' mtype comes before child_proc_one's mtype (12 < 113), child_proc_two will instead be running first. It will create a message into its own buffer, print that it will send it to msgQ and then msgsnds the message. Later, child_proc_two will receive the message with mtype 114 (it will not immediately print it after the msgsnd because child_proc_one has not sent the message with mtype 114 to the msgQ yet) through msgrcv and prints that it has received it. The message is printed and the process prints that it will exit. 
	*/

void child_proc_two(int qid) {
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	/*
	Since mtype 12 comes before child_proc_one's mtype 113, child_proc_two will actually run first, but nothing will be printed because there are no messages stored in mtype 12 of the msgQ. Thus, the next three lines essentially do nothing that is printable. 
	*/
	
	// sending a message that will never be read
	msg.mtype = 12;
	strcpy(msg.greeting, "Fake message");
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	
	/*
	msgrcv and msgsnd in child_proc_two works exactly the same way it does in child_proc_one. First a message is appended to child_proc_two's message buffer and prints out the the message is sent. The appended message is sent to msgQ with mtype 113 based on the qid. It will immediately call msgrcv after, but there is nothing there yet since child_proc_one had yet to put a message there, and remains on standby with msgflag set to 0. Once it recognizes that child_proc_one had placed the message mtype 114 into the msgQ, the flag will change and the msgrcv is finally executed. It prints that it receives the messagem prints the message, and prints that process two will be exitting. 
	*/
	
	// prepare my message to send
	strcpy(msg.greeting, "Hello there");
	cout << getpid() << ": sends greeting" << endl;
	msg.mtype = 113; // set message type mtype = 113
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	msgrcv(qid, (struct msgbuf *)&msg, size, 114, 0);
	cout << getpid() << ": gets reply" << endl;
	cout << "reply: " << msg.greeting << endl;
	cout << getpid() << ": now exits" << endl;
}

	/*
	In the main program, the msgQ is created alongside two child processes to test it. The child processes will take turns running to send and receive from the queue until both are done with their executions and finally both exits. child_proc_two executes first to send a message that will not print or be sent to the queue, then sends a second message that will be added to the queue. child_proc_one receives the message, prints it out, and sends back its own message to the msgQ and exits. This terminates child_proc_one. child_proc_two will take child_proc_one's sent message, print it, and exit. This terminates child_proc_two. Finally, the parent process will print its pid and exit as well. This will terminate and remove both the parent process and the msgQ. 
	*/

int main() {
	
	/*
	qid is set as the identifier int of the msgQ, taken through msgget. Here the msgget creates a new message queue with IPC_PRIVATE as the key parameter and IPC_EXCL|IPC_CREAT|0600 as its msgflg. IPC_PRIVATE generates a new key to this message queue, while IPC_EXCL|IPC_CREAT|0600 ensures that the key being created is unique by being a flag value as a way to check. The IPC_PRIVATE key parameter and IPC_EXCL|IPC_CREAT|0600 flag parameter thus creates the message queue used by the 2 processes. The result from calling msgget returns the int identifier.
	*/
	int qid = msgget(IPC_PRIVATE, IPC_EXCL|IPC_CREAT|0600);
	//spawning two child processes
	pid_t cpid = fork();
	if (cpid == 0) {
		child_proc_one(qid);
		exit(0);
	}
	cpid = fork();
	if (cpid == 0) {
		child_proc_two(qid);
		exit(0);
	}
	
	/*
	msgctl takes in the qid parameter to see what message queue to control. Once the qid is found, it will check what the cmd parameter is, in this case being IPC_RMID. IPC_RMID is a function that removes the message queue that msgctl calls it for. It can only be called to the owner of the msgQ, which is why it is used for the process parent. The pointer value is set to NULL since the command in this msgctl is IPC_RMID. At the end of the loop, the msgQ is removed, and the parent will be exitted and terminated.
	*/
	while(wait(NULL) != -1); // waiting for both children to terminate
		msgctl(qid, IPC_RMID, NULL);
		cout << "parent proc: " << getpid()
		<< " now exits" << endl;
	exit(0);
}