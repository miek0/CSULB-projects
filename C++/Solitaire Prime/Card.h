//Mike Zeng
//CECS 282-05
//Prog 1 - Solitaire Prime
//Sept 20, 2018
#ifndef CARD_H
#define CARD_H

class Card
{
	private:
		bool faceUp = true;
		char rank;
		char suit;
	public:
		Card();
		Card(char r, char s);
		void flip();
		void setCard(char r, char s);
		void showCard();
		int getValue();
};
#endif