//Mike Zeng
//016392881
//Program 5
//November 27, 2018
#include "BigInt.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

BigInt GoldRabbits(int);
int fact(int);

int main() {
	for (int n = 0; n <= 1000; n++) {
		cout << "\nThe GoldRabbit of (" << n << ") is " << GoldRabbits(n);
		if (n == 10)
			getchar();
	}
	getchar();
	for (int i = 0; i < 100; i++) {
		try {
			cout << "Fact(" << i << "):" << fact(i) << endl;
		}
		catch (...) {
			cout << "Fact(" << i << "): Overflow"<< endl;
		}
	}
	getchar();
}

BigInt GoldRabbits(int n) {
	static map<int, BigInt> farm;
	if (n == 0 || n == 1)
		return BigInt(1);
	if (farm.find(n) != farm.end())
		return farm[n];
	else
		return farm[n] = GoldRabbits(n - 1) + GoldRabbits(n - 2);
}

int fact(int n) {
	if (n < 2)
		return 1;
	else if (n > INT_MAX / fact(n-1))
		throw n;
	else
		return n * fact(n - 1);
}