//Mike Zeng
//CECS 326-03
//Assignment 4

/*	
 *	Class struct that tracks the number of seats remaining in the class. The 3 char attributes are set in shmp1 during CLASS object initiation but were never used or printed in the console.
 */

struct CLASS {
	char class_number[6];	//set to 1001 
	char date[7];			//set to 120119
	char title[50];			//set to Operating Systems
	int seats_left;			//initially 15 seats available
};
