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
creates the functionality of the receiver process. fetches a message from message queue based on the unique key of the queue and reads the message
Input: none
Output: Reads the fetched message
Result: string message is fetched from the queue placed by the sender, and is read
*/
int main(){
	int size = sizeof(msg)-sizeof(long);
	int qid = msgget(ftok("/Documents/hw/hw3",'a'), 0);
	/*
	The string message is retrieved from the msgQ here. It notifies the user the message is retreived and the prints out the content of the message. 
	*/
	msgrcv(qid, &msg, size, 114, 0);
	cout << "Receiver, " << getpid() << ", begins execution" << endl;
	cout << "Receiver, " << getpid() << " - ";
	printf("Message received: %s \n", msg.mtext);
    return 0;
}