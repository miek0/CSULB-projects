//Mike Zeng
//CECS 282-05
//Prog 1 - Solitaire Prime
//Sept 20, 2018
#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <string>
using namespace std;

/*checks from a prime sum value during gameplay*/
bool isPrime(int x) {
	if (x < 2)
		return false;
	if (x == 2)
		return true;
	if (x % 2 == 0)
		return false;
	for (int i = 3; (i*i) <= x; i += 2) {
		if (x % i == 0) 
			return false;
	}
	return true;
}

/*main function for the game*/
void game(Deck d) {
	bool play = true;
	int piles = 0;
	int counter = 0;
	int sum = 0;
	Card hand[52];
	while (play) {
		hand[counter] = d.deal();
		sum += hand[counter].getValue();
		counter++;
		if (isPrime(sum) && (d.cardsLeft() != 0)) { //checks if prime for each pile in hand
			for (int i = 0; i < counter; i++) {
				hand[i].showCard();
				cout << ", ";
			}
			cout << "Prime:" << sum << "\n";
			piles++;
			counter = 0;
			sum = 0;
		}
		if (d.cardsLeft() == 0) { //final pile
			if (isPrime(sum)) { //winner condition
				for (int j = 0; j < counter; j++) {
					hand[j].showCard();
					cout << ", ";
				}
				piles++;
				cout << "Prime:" << sum << "\n";
				cout << endl;
				cout << "Winner in " << piles << " piles! \n\n";
				play = false;
			}
			else { //loser condition
				for (int j = 0; j < counter; j++) {
					hand[j].showCard();
					cout << ", ";
				}
				cout << "Not a prime. Lost \n\n";
				play = false;
			}
		}
	}
}

int main()
{
	int choice;
	Deck myDeck;
	bool keepPlaying = true;

	cout << "Welcome to Solitaire Prime! \n";

	while (keepPlaying) {
		cout << " 1) New Deck \n 2) Display Deck \n 3) Shuffle Deck \n 4) Play Solitaire Prime \n 5) Exit \n\n";
		cin >> choice;
		switch (choice) {
			case 1:
				myDeck.refreshDeck();
				cout << "Created a new deck. \n\n";
				break;
			case 2:
				cout << "Your deck: \n";
				myDeck.showDeck();
				cout << endl;
				break;
			case 3:
				myDeck.shuffle();
				cout << "The deck has been shuffled.\n\n";
				break;
			case 4:
				cout << "Playing Solitaire Prime!!! \n\n";
				game(myDeck);
				break;
			case 5:
				keepPlaying = false;
				break;
		}
	}
}