//Mike Zeng
//016392881
//Program 5
//November 27, 2018
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "BigInt.h"
using namespace std;

BigInt::BigInt() { digits.push_back(0); }

BigInt::BigInt(int n) {
	while (n != 0) {
		digits.push_back(n % 10);
		n /= 10;
	}
}
/*UNUSED*/
BigInt::BigInt(string s) {
	for (int i = s.length() - 1; i >= 0; i--)
		digits.push_back(s[i] - '0');
}

BigInt BigInt::operator+(BigInt B) {
	BigInt sum;
	sum.digits.pop_back();
	int temp, carry = 0;

	for (int i = 0; i < max((int)digits.size(), (int)B.digits.size()); i++) {
		if (i >= digits.size())
			temp = B.digits[i] + carry;
		else if(i >= B.digits.size())
			temp = digits[i] + carry;
		else
			temp = digits[i] + B.digits[i] + carry;
		carry = temp / 10;
		sum.digits.push_back(temp % 10);
	}

	if (carry != 0)
		sum.digits.push_back(carry);
	return sum;
}

ostream& operator<<(ostream& out, const BigInt & B) {
	/*for(int i=B.digits.size()-1;i>=0;i--)
		out << B.digits[i];*/
	vector<int>::reverse_iterator rit;
	for (auto rit = B.digits.rbegin(); rit != B.digits.rend(); rit++)
		out << *rit;
	return out;
}

/*-------------------UNUSED DUE TO PROGRAM ALTERATIONS-------------------------------*/
BigInt BigInt::operator++(int dummy) {
	return *this = *this + BigInt(1);
}
BigInt BigInt::operator-(int n) {
	return *this - BigInt(n);
}
BigInt BigInt::operator-(BigInt B) {
	BigInt ans;
	ans.digits.pop_back();
	int temp;
	int ddif=0;

	for (int i = 0; i < B.digits.size(); i++) {
		temp = digits[i] - B.digits[i] - ddif;
		ddif = 0;
		if (temp < 0) {
			temp += 10;
			ddif++;
		}
		ans.digits.push_back(temp);
	}
	if (digits.size() > B.digits.size()) {
		for (int i = B.digits.size(); i < digits.size(); i++) {
			temp = digits[i]- ddif;
			ddif = 0;
			if (temp < 0) {
				temp += 10;
				ddif++;
			}
			ans.digits.push_back(temp);
		}
	}
	return ans;
}
bool BigInt::operator<=(BigInt B) {return ((*this == B) || (*this < B));}
bool BigInt::operator==(int n) { return(*this == BigInt(n)); }
bool BigInt::operator==(BigInt B) {
	if (digits.size() != B.digits.size()) 
		return false;
	for (int i = 0; i < digits.size(); i++) {
		if (digits[i] != B.digits[i])
			return false;
	}
	return true;
}
bool BigInt::operator<(const BigInt & B) const {
	if (digits.size() < B.digits.size())
		return true;
	if (digits.size() > B.digits.size())
		return false;
	for(int i = digits.size() - 1;i>=0;i--){
		if (digits[i] < B.digits[i])
			return true;
		else
			return false;
	}
	return false;
}