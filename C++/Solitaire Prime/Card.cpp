//Mike Zeng
//CECS 282-05
//Prog 1 - Solitaire Prime
//Sept 20, 2018
#include "Card.h"
#include <iostream>
using namespace std;

Card::Card(){
	suit = 'z';
	rank = 'z';
	faceUp;
};

Card::Card(char r, char s) {
	rank = r;
	suit = s;
	faceUp;
};

void Card::setCard(char r, char s) {
	rank = r;
	suit = s;
}

void Card::flip()
{
	faceUp = !faceUp;
}

int Card::getValue()
{
	if (rank == 'A') //Ace has a value of 1
		return 1;
	else if ((rank == 'T')||(rank == 'J')||(rank == 'Q')||(rank == 'K')) //10, J, Q, K all have value of 10
		return 10;
	else //returns value of every other card, empty cards have a value of 74
		return rank - '0';
}

void Card::showCard()
{
	if (faceUp) {
		cout << '<' << rank << suit << '>';
	}
	else {
		cout << '<' << 'x' << 'x' << '>';
	}
}