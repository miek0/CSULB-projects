/*
Mike Zeng
CECS 282-05
Prog 6 - Inheritance/Virtual Functions
December 11, 2018
*/
#ifndef LUGGAGE
#define LUGGAGE
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

const double PI = 3.141592653589793238463;

class luggage {
	protected:
		string type;
		static int lugCount;
	public:
		luggage() {}
		virtual ~luggage() {lugCount --;}
		static int getLugCount() { return lugCount; }
		virtual double volume() { return 0.0; }
		string getType() { return type; }
};

int luggage::lugCount = 0;

class cube:public luggage {
	private:
		double sides;
	public:
		cube(double s) { 
			type = "cube";
			sides = s;
			lugCount++;
		}
		double volume() { return pow(sides, 3); }
};

class box :public luggage {
	private:
		double width,height,length;
	public:
		box(double w, double h, double l) {
			type = "box";
			width = w;
			height = h;
			length = l;
			lugCount++;
		}
		double volume() { return width*height*length; }
};

class sphere :public luggage {
	private:
		double radius;
	public:
		sphere(double r) {
			type = "sphere";
			radius = r;
			lugCount++;
		}
		double volume() { return PI * pow(radius, 3)*(4.0 / 3.0); }
};

class pyramid :public luggage {
	private:
		double baseSide, height;
	public:
		pyramid(double b, double h) {
			type = "pyramid";
			baseSide = b;
			height = h;
			lugCount++;
		}
		double volume() { return (1.0/3.0)* pow(baseSide,2) * height; }
};

class cylinder :public luggage {
	private:
		double radius, length;
	public:
		cylinder(double r, double l) {
			type = "cylinder";
			radius = r;
			length = l;
			lugCount++;
		}
		double volume() { return length*(PI*pow(radius,2)); }
};

class octahedron :public luggage {
	private:
		double sides;
	public:
		octahedron(double s) {
			type = "octahedron";
			sides = s;
			lugCount++;
		}
		double volume() { return sqrt(2) * (pow(sides,3)/3.0); }
};

class dodecahedron :public luggage {
	private:
		double sides;
	public:
		dodecahedron(double s) {
			type = "dodecahedron";
			sides = s;
			lugCount++;
		}
		double volume() { return ((15+7*sqrt(5))/4) * pow(sides,3); }
};

class torus :public luggage {
	private:
		double r1, r2;
	public:
		torus(double in, double out) {
			type = "torus";
			r1 = in;
			r2 = out;
			lugCount++;
		}
		double volume() { return 2 * pow(PI,2) * pow(r1,2) * r2; }
};
#endif