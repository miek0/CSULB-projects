#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

string sushi = "WWIII";

int randomizeSushi(int);

int main()
{
	const int NUM_SIMULATIONS = 10;
	const int NUM_TRIALS = 1000000;
	float PAB = 0.0;
	int eventA, eventB, numSushi, pickSushi;
	char firstSushi;

	srand(time(NULL));
	int count = 0;

	while (count < NUM_SIMULATIONS) {	//loop 1
		eventA = 0;
		eventB = 0;

		int trials = 0;
		while (trials < NUM_TRIALS) {	//loop 2
			sushi = "WWIII";
			numSushi = sushi.size();
			firstSushi = ' ';
			randomizeSushi(numSushi);
			pickSushi = rand() % numSushi;
			if (sushi[pickSushi] == 'W') {	//decision but not loop
				firstSushi = 'W';
				eventA++;
			}
			while (pickSushi < numSushi - 1) {	//loop 3
				sushi[pickSushi] = sushi[pickSushi + 1];
				pickSushi++;
			}
			numSushi--;
			pickSushi = rand() % numSushi;
			if (sushi[pickSushi] == 'W' && firstSushi == 'W') {	//decision but not loop
				eventB++;
				trials++;
			}
			trials++;
		}
		cout << "Trials#\t" << count + 1 << "\tA = " << eventA << "\tB = " << eventB << "\tP(A and B) :" << (100.0*eventB / NUM_TRIALS) << "\%\n";
		PAB += (100.0*eventB / NUM_TRIALS);
		count++;
	}

	//end loop 1
	cout << "On average, P(A and B) = " << PAB / NUM_SIMULATIONS << "\%\n";
	return 0;
}

int randomizeSushi(int numSushi) {
	int n = 0;
	while (n < numSushi) {
		int r = rand() % numSushi;
		char temp = sushi[n];
		sushi[n] = sushi[r];
		sushi[r] = temp;

		n++;
	}
	return n;
}
