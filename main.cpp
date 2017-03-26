#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
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
	int distance;
	int count = 0;
	bool contains;
	vector <Sensor> sensor;  //Initial Sensors that are generated
	vector <Sensor> withinRADIUS; //Sensors that are within a 5 distance
	vector <Sensor> alwaysALIVE; //Sensors that will always be active
	cin >> sensornumber;

	//Randomly add the sensors to random positions
	for (int i = 0; i <= sensornumber; i++) {
		int rnd = rand() % (50 * 50);
		int x = rnd % 50;
		int y = rnd / 50;
		sensor.push_back(Sensor(x,y,300));
	}


	//Testing to find if sensors are in distance < RADIUS
	for (int i = 0; i <= sensornumber; i++){
		for (int j = 0; j <= sensornumber; j++) {
			distance = sqrt(((sensor[i].xpos - sensor[j].xpos) *
			                 (sensor[i].xpos - sensor[j].xpos)) +
			                ((sensor[i].ypos - sensor[j].ypos) *
			                 (sensor[i].ypos - sensor[j].ypos)));
			if(distance <= RADIUS && distance != 0) {
				if(find(withinRADIUS.begin(), withinRADIUS.end(), sensor[j])
				   != withinRADIUS.end()){}
				else
				{
					//TODO: Remove sample output
					withinRADIUS.push_back(sensor[j]);
					count++;
					cout << "INTERSECTION AT POINTS: " << endl;
					cout <<sensor[i];
					cout <<sensor[j];
					cout <<"with a distance of: "<<distance<<endl;
					cout <<"count: "<<count<<endl;
				}
			}
		}
	}

	//Puts ones that have nothing close to it into always alive vector
	for(int i = 0; i < sensornumber; i++)
	{
		if(find(withinRADIUS.begin(), withinRADIUS.end(), sensor[i])
		 != withinRADIUS.end()){}
		else{
			alwaysALIVE.push_back(sensor[i]);
		}
	}


	//TODO: Remove sample output
	for(int i = 0; i < sensornumber; i++) {
		cout << "--------------------ITERATION: "
				"" << i << "--------------------" << endl;
		cout << sensor[i];
	}
	cout << "*****IN RADIUS*****" << endl;
	for(int i = 0; i < withinRADIUS.size(); i++) {
		cout << withinRADIUS[i];
		cout <<"COUNT: "<<i<<endl;
	}

	//Always alive
	cout <<"-----ALWAYS ALIVE-----"<<endl;
	for(int i = 0; i < alwaysALIVE.size(); i++){
		cout <<alwaysALIVE[i];
		cout <<"COUNT: "<<i<<endl;
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

