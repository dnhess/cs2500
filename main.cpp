#include <iostream>
#include <vector>
#include "sensor.h"
using namespace std;
int main() {
	//Code Idea
	/*
	 * The idea of the code is to first generate a grid system that stores 1s
	 * and 0s. The 1s will represent the actual sensor coordinates and the 0s
	 * will represent the empty space (Note: The radius of coverage has not
	 * been shown yet)
	 *
	 * To find a sensor the program will loop through the entire grid system
	 * looking for the 1s. Once it finds a 1 it will check to see if there
	 * are any 1s in a radius of 5
	 */
	srand(time(NULL));
	int sensornumber;
	int RADIUS = 5;
	vector <Sensor> sensor;
	//vector <Sensor> intersections;
	cin >> sensornumber;

	//Randomly add the sensors to random positions
	for (int i = 0; i <= sensornumber; i++) {
		int rnd = rand() % (50 * 50);
		int x = rnd % 50;
		int y = rnd / 50;
		sensor.push_back(Sensor(x,y,300));
	}

	//TODO: Remove sample output
	for(int i = 0; i < sensornumber; i++) {
		cout << "--------------------ITERATION: "
				"" << i << "--------------------" << endl;
		cout << sensor[i];
	}

/*
	//Testing basic math

	cout <<"Value of energy of sensor 1"<<endl;
	cout <<sensor[1].energy<<endl;
	cout <<"taking half of it"<<endl;
	sensor[1].energy = sensor[1].energy/2; //Need to do this to get changes
	// to stick
	cout <<sensor[1].energy<<endl;
*/
}

