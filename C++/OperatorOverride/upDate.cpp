//Mike Zeng
//Program 4
//CECS 282-05
//November 1, 2018
#include "upDate.h"
#include <string>
#include <iostream>
using namespace std;

/*-----conversion functions-----*/
//pass in int m,d,y and return a Julian date
int Greg2Julian(int month, int day, int year) {
	int JD = day - 32075 + 1461 * (year + 4800 + (month - 14) / 12)
		/ 4 + 367 * (month - 2 - (month - 14) / 12 * 12)
		/ 12 - 3 * ((year + 4900 + (month - 14) / 12) / 100) / 4;
	return JD;
}

//pass in int m,d,y and Julian date to return Gregorian date
void Julian2Greg(int JD, int & month, int & day, int & year) {
	int i, j, k, l, n;
	l = JD + 68569;
	n = 4 * l / 146097;
	l = l - (146097 * n + 3) / 4;
	i = 4000 * (l + 1) / 1461001;
	l = l - 1461 * i / 4 + 31;
	j = 80 * l / 2447;
	k = l - 2447 * j / 80;
	l = j / 11;
	j = j + 2 - 12 * l;
	i = 100 * (n - 49) + i + l;

	month = j;
	day = k;
	year = i;
}
/*------------------------------*/

/*static counter*/
int upDate::dateCount = 0;

/*constructors in order: default, parameter, Julian, copy*/
upDate::upDate() {
	dptr = new int[3];
	*(dptr + 0) = 5;
	*(dptr + 1) = 11;
	*(dptr + 2) = 1959;

	dateCount++;
}

upDate::upDate(int m, int d, int y) {
	dptr = new int[3];
	int JD = Greg2Julian(m, d, y);
	int m1, d1, y1;
	Julian2Greg(JD, m1, d1, y1);
	if ((m1 == m) && (d1 == d) && (y1 = y)) {
		*(dptr + 0) = m;
		*(dptr + 1) = d;
		*(dptr + 2) = y;
	}
	else {
		*(dptr + 0) = 5;
		*(dptr + 1) = 11;
		*(dptr + 2) = 1959;
	}

	dateCount++;
}

upDate::upDate(int JD) {
	dptr = new int[3];
	int m1, d1, y1;
	Julian2Greg(JD, m1, d1, y1);
	*(dptr + 0) = m1;
	*(dptr + 1) = d1;
	*(dptr + 2) = y1;

	dateCount++;
}

upDate::upDate(const upDate &D) {
	dptr = new int[3];
	*(dptr + 0) = D.dptr[0];
	*(dptr + 1) = D.dptr[1];
	*(dptr + 2) = D.dptr[2];

	dateCount++;
}

/*destructor*/
upDate::~upDate() { 
	delete[] dptr;
	dateCount--; 
}

void upDate::setDate(int m, int d, int y) {
	*(dptr + 0) = m;
	*(dptr + 1) = d;
	*(dptr + 2) = y;
}

/*getters*/
int upDate::getMonth() {return *(dptr + 0);}
int upDate::getDay() {return *(dptr + 1);}
int upDate::getYear() {return *(dptr + 2);}
string upDate::getMonthName(){
	int month = *(dptr + 0);
	switch (month) {
		case 1:
			return "Janurary";
			break;
		case 2:
			return "Feburary";
			break;
		case 3:
			return "March";
			break;
		case 4:
			return "April";
			break;
		case 5:
			return "May";
			break;
		case 6:
			return "June";
			break;
		case 7:
			return "July";
			break;
		case 8:
			return "August";
			break;
		case 9:
			return "September";
			break;
		case 10:
			return "October";
			break;
		case 11:
			return "November";
			break;
		case 12:
			return "December";
			break;
		default:
			return "Not a proper month";
			break;
	}
}
int upDate::getDateCount() { return dateCount; }
int upDate::julian() {
	int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
	return JD;
}
/*overloaded operators*/

/*addition*/
upDate upDate::operator+(int n) {
		upDate temp(*this);
		int JD = Greg2Julian(temp.dptr[0], temp.dptr[1], temp.dptr[2]);
		JD += n;
		Julian2Greg(JD, temp.dptr[0], temp.dptr[1], temp.dptr[2]);
		return temp;
}

upDate upDate::operator+=(int n) {
	int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
	JD += n;
	Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
	return *this;
}

upDate upDate::operator++(int dummy) {
	int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
	JD++;
	Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
	return *this;
}

upDate upDate::operator++() {
	int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
	JD++;
	Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
	return *this;
}

upDate operator+(int n, upDate D) { return D + n; } //friendship add function

/*subtraction*/
upDate upDate::operator-(int n) {
	upDate temp(*this);
	int JD = Greg2Julian(temp.dptr[0], temp.dptr[1], temp.dptr[2]);
	JD -= n;
	Julian2Greg(JD, temp.dptr[0], temp.dptr[1], temp.dptr[2]);
	return temp;
}

upDate upDate::operator-=(int n) {
	int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
	JD -= n;
	Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
	return *this;
}

upDate upDate::operator--(int dummy) {
	int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
	JD--;
	Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
	return *this;
}

upDate upDate::operator--() {
	int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
	JD--;
	Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
	return *this;
}

upDate operator-(int n, upDate D) { return D - n; } //friendship subtraction function

/*assignment*/
upDate upDate::operator=(upDate const &D) {
	if (&D != this){
		dptr[0] = D.dptr[0];
		dptr[1] = D.dptr[1];
		dptr[2] = D.dptr[2];
	}
	return *this;
}

/*days between 2 upDates*/
int operator-(upDate D1, upDate D2) {
	int JD1 = Greg2Julian(D1.getMonth(), D1.getDay(), D1.getYear());
	int JD2 = Greg2Julian(D2.getMonth(), D2.getDay(), D2.getYear());
	int x = JD1 - JD2;
	return x;
}

/*comparisons*/
bool operator==(upDate D1, upDate D2) {
	if (D1.julian() == D2.julian())
		return true;
	return false;
}

bool operator<(upDate D1, upDate D2) {
	if (D1.julian() < D2.julian())
		return true;
	return false;
}

bool operator>(upDate D1, upDate D2) {
	if (D1.julian() > D2.julian())
		return true;
	return false;
}

/*cout*/
ostream& operator<<(ostream& out,const upDate& D) {
	out << D.dptr[0] << '/' << D.dptr[1] << '/' << D.dptr[2];
	return out;
}