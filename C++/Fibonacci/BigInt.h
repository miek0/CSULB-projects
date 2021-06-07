//Mike Zeng
//016392881
//Program 5
//November 27, 2018
#ifndef BIG_INT
#define BIG_INT
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInt {
private:
	vector<int> digits;
public:
	//constructors
	BigInt();
	BigInt(int);
	BigInt(string);

	//operator overloadings
	BigInt operator+(BigInt B);

	/*---unused---*/
	BigInt operator++(int);
	BigInt operator-(BigInt B);
	BigInt operator-(int);

	bool operator<(const BigInt &) const;
	bool operator<=(BigInt);
	bool operator==(int);
	bool operator==(BigInt);
	/*---unused---*/

	friend ostream & operator<<(ostream &, const BigInt &);
};
#endif