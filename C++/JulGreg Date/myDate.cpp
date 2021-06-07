//Mike Zeng
//Program 2
//CECS 282-05
//October 4, 2018
#include "myDate.h"
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

//default myDate constructor. default date is May 11, 1959
myDate::myDate() {
	month = 5;
	day = 11;
	year = 1959;
}

//overload constructor; creates a valid date
myDate::myDate(int m, int d, int y) {
	int JD = Greg2Julian(m, d, y);
	int m1, d1, y1;
	Julian2Greg(JD, m1, d1, y1);
	if ((m1 == m) && (d1 == d) && (y1 = y)) {
		month = m;
		day = d;
		year = y;
	}
	else {
		month = 5;
		day = 11;
		year = 1959;
	}
}

//getters
int myDate::getMonth() {
	return month;
}
int myDate::getDay() {
	return day;
}
int myDate::getYear() {
	return year;
}

//displays the date
void myDate::display() {
	switch (month) {
		case 1:
			cout << "Janurary " << day << ", " << year;
			break;
		case 2:
			cout << "Feburary " << day << ", " << year;
			break;
		case 3:
			cout << "March " << day << ", " << year;
			break;
		case 4:
			cout << "April " << day << ", " << year;
			break;
		case 5:
			cout << "May " << day << ", " << year;
			break;
		case 6:
			cout << "June " << day << ", " << year;
			break;
		case 7:
			cout << "July " << day << ", " << year;
			break;
		case 8:
			cout << "August " << day << ", " << year;
			break;
		case 9:
			cout << "September " << day << ", " << year;
			break;
		case 10:
			cout << "October " << day << ", " << year;
			break;
		case 11:
			cout << "November " << day << ", " << year;
			break;
		case 12:
			cout << "December " << day << ", " << year;
			break;
	}
}

//increases current date by n number of days
void myDate::increaseDate(int n) {
	int JD = Greg2Julian(month, day, year);
	JD += n;
	Julian2Greg(JD, month, day, year);
}

//decrease current date by n number of days
void myDate::decreaseDate(int n) {
	int JD = Greg2Julian(month, day, year);
	JD -= n;
	Julian2Greg(JD, month, day, year);
}

//returns the number of days between current date and passed date d; positive int if in the future, negative in if in the past
int myDate::daysBetween(myDate d) {
	int thisJD = Greg2Julian(month, day, year);
	int thatJD = Greg2Julian(d.getMonth(), d.getDay(), d.getYear());
	int daysB = thatJD - thisJD;
	return daysB;
}

//returns the number of days since the current year began including the current date
int myDate::dayOfYear() {
	int thisJD = Greg2Julian(month, day, year);
	myDate temp(1, 1, year);
	int tempJD = Greg2Julian(temp.getMonth(), temp.getDay(), temp.getYear());
	int daysSince = thisJD - tempJD + 1; //+1 is for adding current date to the count
	return daysSince;
}

//returns the name of the day of the week
string myDate::dayName() {
	string days[7] = { "Monday","Tuesday", "Wednesday","Thursday","Friday","Saturday","Sunday" };
	int JD = Greg2Julian(month, day, year);
	return days[JD % 7];
}