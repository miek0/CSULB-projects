/*
* Peter Kim
* CECS 282-05
* Prog 5 - Standard Template Library
* Nov 28, 2017
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

class BigInt {
private:
	vector<int> num;
	void stripLeadingZero(BigInt &);

public:
	BigInt();
	BigInt(int);
	BigInt(string);
	BigInt operator++(int); //post-increment
	bool operator<=(BigInt);
	bool operator==(int);
	bool operator==(BigInt);
	BigInt operator-(BigInt);
	BigInt operator-(int);
	BigInt operator+(BigInt);
	bool operator<(const BigInt &) const;
	friend ostream & operator<<(ostream &, const BigInt &);
};

BigInt GoldRabbits(BigInt bigN) {
	static map<BigInt, BigInt> fiboMap;
	if (fiboMap.empty()) {
		fiboMap[BigInt(0)] = BigInt(1);
		fiboMap[BigInt(1)] = BigInt(1);
	}
	if (fiboMap.find(bigN) != fiboMap.end())
		return fiboMap[bigN];
	else
		return fiboMap[bigN] = GoldRabbits(bigN - 1) + GoldRabbits(bigN - 2);
}

int fact(int n) {
	if (n == 0)
		return 1;
	else if (n > 12)
		throw n;
	else
		return n*fact(n - 1);
}

int main()
{
	BigInt bigX(28675), bigY("46368"), bigResult;

	bigResult = bigX + bigY;
	cout << bigX << "+" << bigY << "=" << bigResult;
	getchar(); // pause

	for (BigInt n = 0; n <= 1000; n++)
	{
		cout << (n<950 ? "\n" : "\n\n") << "The GoldRabbit of (" << n << ") is "<<GoldRabbits(n); 
			if (n == 30) // pause at 30
				getchar();
	}

	getchar(); // pause after the GoldRabbits

	for (int i = 0; i<20; i++)
	{
		try {
			cout << "Fact(" << i << "):" << fact(i) << endl;
		}
		catch (...) {
			cout << "Fact(" << i << "):" << "Overflow" << endl;
		}
	}
	getchar();
}

BigInt::BigInt() {
	num.push_back(0);
}

BigInt::BigInt(int n) {
	if (n == 0)
		num.push_back(0);
	else {
		while (n != 0) {
			num.push_back(n % 10);
			n /= 10;
		}
	}
}

BigInt::BigInt(string s) {
	for (int i = s.length() - 1; i >= 0; i--) {
		num.push_back(s[i] - '0');
	}
	stripLeadingZero(*this);
}

void BigInt::stripLeadingZero(BigInt & b) {
	bool done = false;
	while (!b.num.empty() && !done) {
		if (b.num.back() == 0)
			b.num.pop_back();
		else
			done = true;
	}
	if (b.num.empty()) //if BigInt value is 0
		b.num.push_back(0);
}

BigInt BigInt::operator++(int n) {
	return *this = *this + BigInt(1);
}

bool BigInt::operator<=(BigInt b) {
	return 	((*this == b) || (*this < b));
}

bool BigInt::operator==(int n) {
	return (*this == BigInt(n));
}

bool BigInt::operator==(BigInt b) {
	if (num.size() != (b.num.size())) {
		return false;
	}
	int i = 0;
	while (i < num.size()) {
		if (num[i] != b.num[i])
			return false;
		i++;
	}
	return true;
}

BigInt BigInt::operator-(BigInt b) {
	BigInt dif;
	dif.num.pop_back();
	int temp;
	int borrow = 0;

	for (int i = 0; i < (int)b.num.size(); i++) {
		temp = num[i] - b.num[i] - borrow;
		borrow = 0;
		if (temp < 0) {
			temp += 10;
			borrow++;
		}
		dif.num.push_back(temp);
	}
	if (num.size() > b.num.size()) {
		for (int i = (int)b.num.size(); i < (int)num.size(); i++) {
			temp = num[i] - borrow;
			borrow = 0;
			if (temp < 0) {
				temp += 10;
				borrow++;
			}
			dif.num.push_back(temp);
		}
	}
	stripLeadingZero(dif);

	return dif;
}

BigInt BigInt::operator-(int n) {
	return *this - BigInt(n);
}

BigInt BigInt::operator+(BigInt b) {
	BigInt sum;
	sum.num.pop_back();
	int carry = 0;
	int temp;

	for (int i = 0; i < max((int)num.size(), (int)b.num.size()); i++) {
		if (i >= num.size() || i >= b.num.size()) {
			if (i >= num.size())
				temp = b.num[i] + carry;
			else
				temp = num[i] + carry;
		}
		else
			temp = num[i] + b.num[i] + carry;
		carry = temp / 10;
		sum.num.push_back(temp % 10);
	}

	if (carry != 0)
		sum.num.push_back(carry);
	stripLeadingZero(sum);
	return sum;
}

bool BigInt::operator<(const BigInt & b) const {
	if (num.size() < b.num.size())
		return true;
	else if (num.size() > b.num.size())
		return false;
	//case if both numbers are the same size
	int i = num.size() - 1;
	while (i >= 0) {
		if (num[i] < b.num[i])
			return true;
		else if (num[i] > b.num[i])
			return false;
		i--;
	}
	return false; //the numbers are the same
}

ostream & operator<<(ostream & out, const BigInt & b) {
	for (int i = b.num.size() - 1; i >= 0; i--)
		out << b.num[i];
	return out;
}