//Mike Zeng
//Program 3
//CECS 282-05
//October 18, 2018
#include "myDate.h"
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

struct Student
{
	char name[20];
	int ID;
	char grade;
	myDate bDay;
	string homeTown;
};

void displayClass(Student * sa);
void displaySortedClass(Student * sa[]);
void populate(Student * sa);
void sortByName(Student * sa[]);
void sortByID(Student * sa[]);
void sortByGrade(Student * sa[]);
void sortByBday(Student * sa[]);
void sortByHomeTown(Student * sa[]);

int main()
{
	//original list
	Student myClass[10];
	populate(myClass);

	//different sorted lists
	Student * classNames[10];
	Student * classIDs[10];
	Student * classGrades[10];
	Student * classBDays[10];
	Student * classHomeTowns[10];

	//point each pointer array to original list
	for (int i = 0; i < 10; i++) {
		classNames[i] = &myClass[i];
		classIDs[i] = &myClass[i];
		classGrades[i] = &myClass[i];
		classBDays[i] = &myClass[i];
		classHomeTowns[i] = &myClass[i];
	}

	/*menu*/
	bool run = true;
	while (run) {
		cout << "\n 0) Display original list \n 1) Display list sorted by Name \n 2) Display list sorted by ID \n 3) Display list sorted by Grade \n 4) Display list sorted by Birthday \n 5) Display list sorted by Home Town \n 6) Exit \n\n";
		int userInput;
		cin >> userInput;
		switch (userInput) {
			case 0:
				displayClass(myClass);
				break;
			case 1:
				sortByName(classNames);
				displaySortedClass(classNames);
				break;
			case 2:
				sortByID(classIDs);
				displaySortedClass(classIDs);
				break;
			case 3:
				sortByGrade(classGrades);
				displaySortedClass(classGrades);
				break;
			case 4:
				sortByBday(classBDays);
				displaySortedClass(classBDays);
				break;
			case 5:
				sortByHomeTown(classHomeTowns);
				displaySortedClass(classHomeTowns);
				break;
			case 6:
				run = false;
				break;
		}
	}
	getchar();
	return 0;
};

void displayClass(Student * sa) {
	cout << setw(20) << left << "Name " << setw(20) << left << "Student ID " << setw(10) << left << "Grade " << setw(20) << left << "Birthday " << setw(20) << left << "Home Town";
	cout << endl << endl;
	for (int i = 0; i < 10; i++) {
		cout << setw(20) << left << (sa + i)->name << setw(20) << left << (sa + i)->ID << setw(10) << left << (sa + i)->grade << setw(20) << left << (sa + i)->bDay.printDate() << setw(20) << left << (sa + i)->homeTown << endl;
	}
	cout << endl;
}

void displaySortedClass(Student * sa[]) {
	cout << setw(20) << left << "Name " << setw(20) << left << "Student ID " << setw(10) << left << "Grade " << setw(20) << left << "Birthday " << setw(20) << left << "Home Town";
	cout << endl << endl;
	for (int i = 0; i < 10; i++) {
		cout << setw(20) << left << sa[i]->name << setw(20) << left << sa[i]->ID << setw(10) << left << sa[i]->grade << setw(20) << left << sa[i]->bDay.printDate() << setw(20) << left << sa[i]->homeTown << endl;
	}
	cout << endl;
}

void populate(Student * sa) {
	char names[10][20] = { "Genghis Khan", "Freddie Mercury", "Neil Degrasse Tyson" , "Paul McCartney", "Zhuge Liang", "Donald Trump", "John Cena", "Kim Jong Un","Vladmir Putin", "Bill Nye" };
	char grades[] = { 'A','B','C','D','F' };
	string ht[] = { "Deluun Boldog, Mongolia", "Stone Town, Tanzania", "Manhattan, NYC", "Liverpool, U.K.", "Yinan, Shandong", "New York City, NY", "West Newbury, MA", "Pyongyang, N.Kor", "St. Petersburg, RU","Washington D.C., USA" };

	srand((unsigned int)time(0));
	for (int i = 0; i < 10; i++) {
		/*filling names*/
		strcpy_s((sa + i)->name, names[i]);

		/*filling id*/
		int randID = (rand() % (9999 + 1 - 1000) + 1000);
		(sa + i)->ID = randID;

		/*filling grades*/
		(sa + i)->grade = grades[rand() % (sizeof(grades) / sizeof(grades[0]))];

		/*filling birthdays*/
		myDate temp(1, 1, 1995);
		int min = (sa + i)->bDay.daysBetween(temp);
		myDate end(12, 31, 2000);
		int max = (sa + i)->bDay.daysBetween(end);
		int x = rand() % (max - min);
		temp.increaseDate(x);
		(sa + i)->bDay = temp;

		/*filling hometown*/
		(sa + i)->homeTown = ht[i];
	}
}

void sortByName(Student * sa[]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < (10 - i - 1); j++) {
			if (strcmp(sa[j]->name, sa[j + 1]->name) > 0) 
				swap(sa[j], sa[j + 1]);

		}
	}
}

void sortByID(Student * sa[]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < (10 - i - 1); j++) {
			if ((sa[j]->ID) > (sa[j + 1]->ID)) 
				swap(sa[j], sa[j + 1]);
		}
	}
}

void sortByGrade(Student * sa[]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < (10 - i - 1); j++) {
			if ((sa[j]->grade) > (sa[j + 1]->grade))
				swap(sa[j], sa[j + 1]);
		}
	}
}

void sortByBday(Student * sa[]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < (10 - i - 1); j++) {
			if ((sa[j]->bDay.daysBetween(sa[j + 1]->bDay)) < 1)
				swap(sa[j], sa[j + 1]);
		}
	}
}

void sortByHomeTown(Student * sa[]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < (10 - i - 1); j++) {
			if ((sa[j]->homeTown).compare(sa[j + 1]->homeTown) > 0) 
				swap(sa[j], sa[j + 1]);
		}
	}
}

void swap(Student * s1, Student * s2) {
	Student * temp = s1;
	s1 = s2;
	s2 = temp;
}