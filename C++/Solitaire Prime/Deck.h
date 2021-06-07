//Mike Zeng
//CECS 282-05
//Prog 1 - Solitaire Prime
//Sept 20, 2018
#ifndef DECK_H
#define DECK_H
#include <iostream>
#include "Card.h"
class Deck
{
	private:
		Card storage[52];
		int top;
		char suits[4] = { 'S','H','D','C' };
		char ranks[13] = { 'A','2','3','4','5','6','7','8','9','T','J','Q','K' };
	public:
		Deck();
		void showDeck();
		void refreshDeck();
		void shuffle();
		int cardsLeft();
		Card deal();
};
#endif