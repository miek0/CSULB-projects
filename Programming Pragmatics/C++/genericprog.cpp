/*
* Mike Zeng
* CECS 424-05
* Assignment 3
*/
#include <iostream>
#include <string.h>
#include <algorithm>	//generic sorting algorithm
#include <vector>		//for data structures
#include <utility>		//to make pairs
using namespace std;

//data structures
vector<double> numbers = { 645.32, 37.40, 76.30, 5.40, -34.23, 1.11, -34.94, 23.37, 635.46, -876.22, 467.73, 62.26 };
vector<pair<string, int>> people = { make_pair("Hal",20), make_pair("Susann", 31), make_pair("Dwight" , 19),
									 make_pair("Kassandra" , 21), make_pair("Lawrence", 25), make_pair("Cindy" , 22), 
									 make_pair("Cory" , 27), make_pair("Mac" , 19), make_pair("Romana" , 27), 
									 make_pair("Doretha" , 32), make_pair("Danna" , 20), make_pair("Zara" , 23), 
									 make_pair("Rosalyn" , 26), make_pair("Risa" , 24), make_pair("Benny" , 28), 
									 make_pair("Juan" , 33), make_pair("Natalie" , 25) };
template <class T>				//for generic safety with single element vector
void display_num(vector<T> v) {
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
}

template <class T1, class T2>	//for generic safety with two element vector
void display_people(vector<pair<T1,T2>> v) {
	for (int i = 0; i < v.size(); i++)
		cout << v[i].first << "," << v[i].second << " ";
}

bool compare(const pair<string, int>& i, const pair<string, int>& j){	//compares the second element of a pair in descending order
	return i.second > j.second;
}

int main(){
	//display and order list of numbers
	cout << "List of numbers: \n";
	display_num(numbers);
	sort(numbers.begin(), numbers.end());	//generic sort the numbers
	cout << "\nOrdered numbers: \n";
	display_num(numbers);
	//display and order list of people
	cout << "\n\nList of people: \n";
	display_people(people);
	sort(people.begin(), people.end());		//generic sort people by element.first (alphabetically)
	vector<pair<string, int>> sorted_people = people;	//stored as a sorted vector
	cout << "\nOrdered people alphabetically by name: \n";
	display_people(sorted_people);
	sort(sorted_people.begin(), sorted_people.end(), compare);	//sorts in descending order, but keeps alphabetical order
	cout << "\nOrdered people descending by age: \n";
	display_people(sorted_people);
	cout << endl;
	
	return 0;
}
