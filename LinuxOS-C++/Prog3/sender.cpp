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
	long mtype; // required
	char mtext[50]; // message content
};

//made the buffer instance here to run it in main()
buf msg;

/*
creates the functionality of the sender process. it takes in a user input string to place into the message queue
Input: string type message
Output: none
Result: string message is put into message queue and user is notified
*/
int main(){
	int size = sizeof(msg)-sizeof(long);
	/*
	the qid is the message queue ID (should be the same for all 3 cpp files). The message queue is created through msgget with the unique key made by ftok to identify the file path the message queue is implementing IPC in. The files associated with the key will all have access to the same message queue.
	*/
	int qid = msgget(ftok("/Documents/hw/hw3",'a'), 0);
	msg.mtype = 114; // prepare message with mtype = 114
	/*
	This prompts the user to enter a message to put into the message queue when this cpp is executed. It will notify the user when the message has been sent. 
	*/
	cout << "Sender, " << getpid() << ", begins execution" << endl;
	cout << "Sender, " << getpid() << " - Write message: " << endl;
	fgets(msg.mtext, 50, stdin);
	msgsnd(qid, &msg, size, 0);	
	cout << "Sender, " << getpid() << " - Message sent." << endl;
    return 0;
}