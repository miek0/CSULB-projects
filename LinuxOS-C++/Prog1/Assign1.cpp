/*
*Mike Zeng
*CECS 326 - 03
*Assignment 1
*/
#include <iostream>
#include <deque>
#include <ctime>
using namespace std;

//MBT
struct MBT {
	int index = 0;
	bool memState[992] = { false };
};

//PCB
struct PCB {
	int PID;
	int tableSize;
	int* tablePointer;
};

void initiateProcess(MBT&);
void printSystemState(MBT&);
void terminateProcess(int, MBT&);
int exit();

deque<PCB> readyQueue;
int uID = 1;
/* 
*makes a process and puts it into the ready queue
input:generates a process of random memory size and saves it to the MBT
output:process added to ready queue
*/
void initiateProcess(MBT&mbt1) {
	srand(time(NULL));
	int mems = rand() % 241 + 10; //required memory blocks randomly generated
	cout << "Generating a PCB of " << mems << " memory blocks...\n\n";

	int currentBlock = mbt1.index;
	int totalBlocks = currentBlock + mems;
	PCB pcb1;
	pcb1.PID = uID; //unique PID
	pcb1.tableSize = mems;
	pcb1.tablePointer = new int[pcb1.tableSize];

	//searching throught MBT for free blocks
	for (int i = currentBlock; i < totalBlocks; i++) {
		//checks for sufficient free blocks first
		if (totalBlocks > 992 || (mbt1.memState[totalBlocks-1] == true)) {
			cout << "Insufficient free blocks. Returning to menu. \n";
			if (totalBlocks > 992) { //resets index if passes the MBT space limit
				mbt1.index = 0;
			}
			else {
				mbt1.index += totalBlocks; //moves to next available area if not
			}
			return;
		}
		//allocating blocks	for PCB	
		if (mbt1.memState[i] == false) {
			mbt1.memState[i] = true;
		}
	}
	//allocate MBT index to page table
	for (int j = 0; j < mems; j++) {
		pcb1.tablePointer[j] = (j + currentBlock);
	}
	
	mbt1.index += mems;
	readyQueue.push_back(pcb1);
}

/*
*prints out the current state of the MBT and the processes details in the queue
input:iterates through MBT and the ready queue 
output:queue processes and MBT state printed
*/
void printSystemState(MBT&mbt1) {
	//outputs processes in queue	
	PCB print;
	for (int i = 0; i < readyQueue.size();i++) {
		print = readyQueue[i];
		cout << "\nPID: " << print.PID << "\nNumber of blocks allocated: " << print.tableSize << "\nBlocks allocated: \n";
		for (int k = 0; k < print.tableSize; k++) {
			cout << print.tablePointer[k] << " ";
		}
		cout << "\n";
	}

	cout << "\n\nMBT State \n\n";

	//MBT state
	for (int j = 0; j < 992; j++) {
		cout << mbt1.memState[j] << " ";
	}
	cout << "\n\n";
}

/*
*deletes a process based on the PID thats selected
input:removes a process from ready queue
output:process is removed and the pointer is deleted
*/
void terminateProcess(int givenPID, MBT&mbt1) {
	PCB check;
	bool found = false;
	for (int i = 0; i < readyQueue.size(); i++) {
		check = readyQueue[i];
		if (check.PID == givenPID) { //if PID is found
			found = true;
			//deallocating memory blocks in MBT
			for (int i = (check.tablePointer[0]); i < (check.tablePointer[0] + check.tableSize); i++) {
				if (mbt1.memState[i] == true) {
					mbt1.memState[i] = false;	
				}
			}
			delete check.tablePointer;
			check.tablePointer = NULL;
			readyQueue.erase(readyQueue.begin()+i);
		}
	}

	if (!found) {
		cout << "PID not found in queue. \n";
	}
}

/*
*closes the program, and makes sure to delete all dynamic memory
input:confirmation to remove all processes in the ready queue
output:processes are deleted and program shuts down
*/
int exit() {
	int cont = 0;
	PCB out;
	//shows the PIDs in queue
	cout << "PIDs in Queue: \n";
	for(int i = 0;i<readyQueue.size();i++){ 
			out = readyQueue[i];
			cout << out.PID << "\n";
	}
	
	//if the queue is not empty, prompts user again
	if (!readyQueue.empty()) {
		char confirm = ' ';
		cout << "\nConfirm the exit?(y/n)\n";
		cin >> confirm;
		switch (confirm) {
			case 'y':
				for(int j = 0;j<readyQueue.size();j++){
					out = readyQueue[j];
					if (out.tablePointer != NULL) {
						delete[] out.tablePointer;
						out.tablePointer = NULL;
					}
					readyQueue.pop_front();
				}
				return cont = 0;
				break;
			case 'n':
				return cont = 1;
				break;
			default:
				return cont = 1;
				break;
		}
	}
	else {
		cout << "Queue is empty. Closing program...\n";
		return cont = 0;
	}
}
/*
*this is the main menu for the program. takes in user input to run
*/
int main() {
	MBT mbt1;

	int choice;
	bool keepRunning = true;

	while (keepRunning) {
		cout << "	Menu \n\n 1) Initiate a response \n 2) Print system state \n 3) Terminate process with a specific PID \n 4) Exit \n\n";
		cin >> choice;
		switch (choice) {
		case 1:
			initiateProcess(mbt1);
			uID++;
			break;
		case 2:
			printSystemState(mbt1);
			break;
		case 3:
			int remove;
			if (readyQueue.empty()) {
				cout << "Queue is empty.\n";
			}
			else {
				cout << "Enter a PID: \n";
				cin >> remove;
				terminateProcess(remove, mbt1);
			}
			break;
		case 4:
			int cont = exit();
			if (cont == 0) {
				keepRunning = false;
			}
			break;
		}
	}
	getchar();
	return 0;
}