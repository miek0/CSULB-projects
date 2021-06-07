//Mike Zeng
//Program 2
//CECS 282-05
//October 4, 2018
#ifndef MYDATE_H
#define MYDATE_H
#include <string>
using namespace std;

class myDate {
	private:
		int month, day, year;
	public:
		myDate();
		myDate(int m, int d, int y);
		void display();
		void increaseDate(int n);
		void decreaseDate(int n);
		int daysBetween(myDate d);
		int getMonth();
		int getDay();
		int getYear();
		int dayOfYear();
		string dayName();
		string printDate();
//		int Greg2Julian(int a, int b, int c);
//		void Julian2Greg(int d, int&a, int&b, int&c);
};
#endif