//Mike Zeng
//CECS 282-05
//Prog 1 - Solitaire Prime
//Sept 20, 2018
#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/*constructor for Deck*/
Deck::Deck()
{
	top = 0;
	int k = 0;
	for (int i = 0; i < sizeof(suits); i++) { //makes the deck of 52 cards
		for (int j = 0; j < sizeof(ranks); j++) {
			storage[k].setCard(ranks[j], suits[i]);
			k++;
		}
	}
}

/*displays all the cards within a deck in a 4 rows by 13 column fashion*/
void Deck::showDeck() {
	int c = 0;
	for (int i = 0; i < 52; i++) {
		storage[i].showCard();
		cout << "\t";
		c++;
		if (c == 13) {
			cout << endl;
			c = 0;
		}
	}
}

/*shuffles the current deck in hand; reorganizes the order of each element in the deck array*/
void Deck::shuffle() {
	srand(time(0));
	for (int i = 0; i < 52; i++) {
		int index = rand() % 52;
		Card temp = storage[i];
		storage[i] = storage[index];
		storage[index] = temp;
	}
}

/*returns the card at the top of the deck, increments counter "top" by 1*/
Card Deck::deal() {
	Card dealtC = storage[top];
	top++;
	return dealtC;
}

/*counts remaining cards left based on top*/
int Deck::cardsLeft() {
	return 52 - top;
}

/*resets the order of current deck back to the original order*/
void Deck::refreshDeck() {
	int k = 0;
	for (int i = 0; i < sizeof(suits); i++) {
		for (int j = 0; j < sizeof(ranks); j++) {
			storage[k].setCard(ranks[j], suits[i]);
			k++;
		}
	}
}