/*
Mike Zeng
CECS 282-05
Prog 6 - Inheritance/Virtual Functions
December 11, 2018
*/
#include "Luggage.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

void displayStorage(vector<luggage *>);

int main() {
	int choice;
	bool running = true;
	vector<luggage*> storage; //storage container
	
	cout << "Shipping Container \n\n";
	while (running) {
		cout << "1) Add luggage to storage container \n2) Remove luggage from storage container \n3) Show all luggage \n4) Quit \n\n";
		cin >> choice;
		switch (choice) {
			case 1:
				int lugType;
				cout << "Choose a luggage to add: \n1) Box \n2) Sphere \n3) Cube \n4) Pyramid \n5) Cylinder \n6) Octahedron \n7) Dodecahedron \n8) Torus \n\n";
				cin >> lugType;
				switch (lugType) {
					int w, h, l, r, s, b;	//luggage parameters
					case 1:
						cout << "Input the parameters for this box. \nWidth: " << endl;
						cin >> w;
						cout << "Height: " << endl;
						cin >> h;
						cout << "Length: " << endl;
						cin >> l;
						storage.push_back(new box(w, h, l));
						cout << "Your box has been added to the storage container.\n\n";
						break;
					case 2:
						cout << "Input the parameter for this sphere. \nRadius: " << endl;
						cin >> r;
						storage.push_back(new sphere(r));
						cout << "Your sphere has been added to the storage container.\n\n";
						break;
					case 3:
						cout << "Input the parameter for this cube. \nSide length: " << endl;
						cin >> s;
						storage.push_back(new cube(s));
						cout << "Your cube has been added to the storage container.\n\n";
						break;
					case 4:
						cout << "Input the parameters for this pyramid. \nBase edge: " << endl;
						cin >> b;
						cout << "Height: " << endl;
						cin >> h;
						storage.push_back(new pyramid(b, h));
						cout << "Your pyramid has been added to the storage container.\n\n";
						break;
					case 5:
						cout << "Input the parameters for this cylinder. \nRadius: " << endl;
						cin >> r;
						cout << "Length: " << endl;
						cin >> l;
						storage.push_back(new cylinder(r, l));
						cout << "Your cylinder has been added to the storage container.\n\n";
						break;
					case 6:
						cout << "Input the parameters for this ocathedron. \nBase edge: " << endl;
						cin >> s;
						storage.push_back(new octahedron(s));
						cout << "Your octahedron has been added to the storage container.\n\n";
						break;
					case 7:
						cout << "Input the parameters for this dodecahedron. \nBase edge: " << endl;
						cin >> s;
						storage.push_back(new dodecahedron(s));
						cout << "Your dodecahedron has been added to the storage container.\n\n";
						break;
					case 8:
						int r1, r2;
						cout << "Input the parameters for this torus. \nInner radius: " << endl;
						cin >> r1;
						cout << "Outer radius: " << endl;
						cin >> r2;
						storage.push_back(new torus(r1,r2));
						cout << "Your torus has been added to the storage container.\n\n";
						break;
				}
				break;
			case 2:
				int removeLug;
				luggage* del;
				cout << "Choose a luggage to remove (luggage number): \n";
				for (int j = 0; j < storage.size(); j++) 
					cout << (j+1) << ") Luggage type: " << setw(15) << left << (storage[j])->getType() << "	Volume: " << setprecision(2) << fixed << (storage[j])->volume() << endl;
				cin >> removeLug;
				while (removeLug > storage.size() || removeLug == 0) {
					cout << "\nPlease pick a number within the storage container. \n";
					for (int j = 0; j < storage.size(); j++)
						cout << (j + 1) << ") Luggage type: " << setw(15) << left << (storage[j])->getType() << "	Volume: " << setprecision(2) << fixed << (storage[j])->volume() << endl;
					cin >> removeLug;
				}
				del = *(storage.begin() + (removeLug-1));
				storage.erase(storage.begin() + (removeLug-1));
				delete (del);
				cout << "\nThe luggage is removed. \n\n";
				break;
			case 3:
				cout << "Displaying all luggage in storage: \n\n";
				displayStorage(storage);
				break;
			case 4:
				running = false;
				break;
		}
	}
 }

void displayStorage(vector<luggage *> stor) { 
	vector<luggage *>::iterator it;
	double totalVolume = 0.0;
	for (it = stor.begin(); it != stor.end(); it++) {
		cout << "Luggage type: " << setw(15) << left << (*it)->getType() << "	Volume: " << setprecision(2) << fixed << (*it)->volume() << endl;
		totalVolume += (*it)->volume();
	}
	cout << "\nTotal luggage items: " << luggage::getLugCount() << "	Total volume: " << totalVolume << "\n\n";
}