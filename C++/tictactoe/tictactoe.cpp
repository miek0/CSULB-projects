#include <iostream>
#include <string>
using namespace std;

void initializeGameBoard(int *);
void displayGameBoard(int *);
void makeMove(int *, int);
//bool checkWinner();
bool checkTie();
void instructions();
int cellState(int *, int, int);
int turnCounter = 1;
int player = 1;

int main()
{
	bool notTie = true;
	int *gameBoard = new int[9];
	instructions();
	initializeGameBoard(gameBoard);
	displayGameBoard(gameBoard);
	cout << "Player 1 will go first!" << endl;
	while (notTie) {
		if (player == 1)
			makeMove(gameBoard, 1);
		else if (player == 2) 
			makeMove(gameBoard, 2);

		checkTie();
		if (checkTie) {
			cout << "Cat Game!";
			notTie = false;
		}
		else notTie;
	}
}

int cellState(int* gameBoard, int row, int col) {
	if (row == 0) {
		switch (col) {
		case 0:
			return gameBoard[0];
			break;
		case 1:
			return gameBoard[1];
			break;
		case 2:
			return gameBoard[2];
			break;
		}
	}
	else if (row == 1) {
		switch (col) {
		case 0:
			return gameBoard[3];
			break;
		case 1:
			return gameBoard[4];
			break;
		case 2:
			return gameBoard[5];
			break;
		}
	}
	else if (row == 2) {
		switch (col) {
		case 0:
			return gameBoard[6];
			break;
		case 1:
			return gameBoard[7];
			break;
		case 2:
			return gameBoard[8];
			break;
		}
	}
}

void initializeGameBoard(int * gameBoard) {
	for (int i = 0; i < 9; i++)
		*(gameBoard + i) = 0;
}

void displayGameBoard(int * gameBoard) {
	char temp1, temp2, temp3;
	cout << "\n\n\tTic Tac Toe\n\n";

	cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
	cout << endl;

	cout << "     |     |     " << endl;

	for (int i = 0; i < 9; i += 3) {
		switch (gameBoard[i]) { //temp1
		case 0:
			temp1 = ' ';
			break;
		case 1:
			temp1 = 'X';
			break;
		case 2:
			temp1 = 'O';
			break;
		}
		switch (gameBoard[i+1]) { //temp2
		case 0:
			temp2 = ' ';
			break;
		case 1:
			temp2 = 'X';
			break;
		case 2:
			temp2 = 'O';
			break;
		}
		switch (gameBoard[i+2]) { //temp3
		case 0:
			temp3 = ' ';
			break;
		case 1:
			temp3 = 'X';
			break;
		case 2:
			temp3 = 'O';
			break;
		}
		if (i < 6) {
			cout << "  " << temp1 << "  |  " << temp2 << "  |  " << temp3 << endl;

			cout << "_____|_____|_____" << endl;
			cout << "     |     |     " << endl;
		}
		else {
			cout << "  " << temp1 << "  |  " << temp2 << "  |  " << temp3 << endl;
		}
	}
	cout << "     |     |     " << endl << endl;
}

void makeMove(int *gameBoard, int player) {
	int userInputRow;
	int userInputColumn;
	bool notTie = true;

	cout << "Turn: " << turnCounter << endl;
	while (notTie) {
		cout << "It is player "<< player <<"'s turn." << endl;
		cout << "Enter a Row #: " << endl;
		cin >> userInputRow;
		while (userInputRow < 0 || userInputRow > 2) {
			cout << "Invalid Row #, please try again" << endl;
			cout << "Enter a Row #: " << endl;
			cin >> userInputRow;
		}
		cout << "Enter a Column #: " << endl;
		cin >> userInputColumn;
		while (userInputColumn < 0 || userInputColumn > 2) {
			cout << "Invalid Column #, please try again" << endl;
			cout << "Enter a Column #: " << endl;
			cin >> userInputColumn;
		}
		while (cellState(gameBoard, userInputRow, userInputColumn) != 0) {					 //pick another cell
			cout << "Cell taken. Pick another cell.\n";
			cout << "Enter a Row #: " << endl;
			cin >> userInputRow;
			while (userInputRow < 0 || userInputRow > 2) {
				cout << "Invalid Row #, please try again" << endl;
				cout << "Enter a Row #: " << endl;
				cin >> userInputRow;
			}
			cout << "Enter a Column #: " << endl;
			cin >> userInputColumn;
			while (userInputColumn < 0 || userInputColumn > 2) {
				cout << "Invalid Column #, please try again" << endl;
				cout << "Enter a Column #: " << endl;
				cin >> userInputColumn;
			}
		}
		if (userInputRow == 0) {	//ROW 1
			switch (userInputColumn) {
			case 0: gameBoard[0] = player; break;
			case 1: gameBoard[1] = player; break;
			case 2: gameBoard[2] = player; break;
			}
		}
		else if (userInputRow == 1) {	//ROW 2
			switch (userInputColumn) {
			case 0: gameBoard[3] = player; break;
			case 1: gameBoard[4] = player; break;
			case 2: gameBoard[5] = player; break;
			}
		}
		else if (userInputRow == 2) {	//ROW 3
			switch (userInputColumn) {
			case 0: gameBoard[6] = player; break;
			case 1: gameBoard[7] = player; break;
			case 2: gameBoard[8] = player; break;
			}
		}
		
		displayGameBoard(gameBoard);
		if (player == 1)
			player = 2;
		else if (player == 2)
			player = 1;
		turnCounter++;
		cout << "Turn: " << turnCounter << endl;
	}

}

//bool CheckWinner() {
//	
//}

bool checkTie() {
	if (turnCounter == 9) {
		cout << "Stalemate!";
		return true;
	}
	else return false;
}

void instructions() {
	cout << "\n\n\tTic Tac Toe\n\n";

	cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
	cout << endl;

	cout << "     |     |     " << endl;

	cout << "  " << "0,0" << "|" << " 0,1" << " |" << "0,2" << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << "1,0" << "|" << " 1,1" << " |" << "1,2" << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << "2,0" << "|" << " 2,1" << " |" << "2,2" << endl;
	cout << "     |     |     " << endl << endl;

	cout << "You will select a row and column  corresponding to each square" << endl << "each alternating turn per player until an outcome is decided." << endl;
}

