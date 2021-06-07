//Mike Zeng
//Program 4
//CECS 282-05
//November 1, 2018
#ifndef UP_DATE
#define UP_DATE
#include <string>
#include <iostream>
using namespace std;

class upDate {
	private: 
		int * dptr;
		static int dateCount;
	public:
		upDate();						//default
		upDate(int m, int d, int y);	//parameter
		upDate(int JD);					//Julian Date
		upDate(upDate const &D);		//copy
		~upDate();						//destructor
		void setDate(int m, int d, int y);
		int getMonth();
		int getDay();
		int getYear();
		string getMonthName();
		static int getDateCount();
		int julian();

		/*overloaded operators*/
		upDate operator+(int n);
		upDate operator+=(int n);
		upDate operator++(int dummy);
		upDate operator++();
		upDate operator-(int n);
		upDate operator-=(int n);
		upDate operator--(int dummy);
		upDate operator--();
		upDate operator=(upDate const &D);

		/*friendship functions*/
		friend upDate operator+(int n, upDate D);
		friend upDate operator-(int, upDate D);
		friend int operator-(upDate D1, upDate D2);
		friend bool operator==(upDate D1, upDate D2);
		friend bool operator<(upDate D1, upDate D2);
		friend bool operator>(upDate D1, upDate D2);
		friend ostream& operator<<(ostream & out,const upDate & D);
};
#endif