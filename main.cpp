#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "sensor.h"
#include "intpts.h"
using namespace std;
void getintpts(int i_x1, int i_y1, int r_x2, int r_y2, int d);
int RADIUS = 5;
vector <intpts> interpts; //The location of the intersection
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
	int distance;
	int count = 0;
	vector <Sensor> sensor;  //Initial Sensors that are generated
	vector <Sensor> withinRADIUS; //Sensors that are within a 5 distance
	vector <Sensor> active; //Sensors that will always be active
	//vector <intpts> interpts; //The location of the intersection
	//                       points
	cin >> sensornumber;

	//Randomly add the sensors to random positions
	for (int i = 0; i <= sensornumber; i++) {
		int rnd = rand() % (50 * 50);
		int x = rnd % 50;
		int y = rnd / 50;
		sensor.push_back(Sensor(x,y,300,true));
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
				   != withinRADIUS.end()){} //If coordinate location is already in the vector it will not add it again.
				else
				{
					//TODO: Remove sample output
					withinRADIUS.push_back(sensor[j]);
					getintpts(sensor[i].xpos, sensor[i].ypos, sensor[j].xpos,
					          sensor[j].ypos, distance);
					cout << "Points that cause Intersection: " << endl;
					cout <<sensor[i];
					cout <<sensor[j];
					cout <<"with a distance of: "<<distance<<endl;
					cout <<"count: "<<count<<endl;
					cout <<"INTERSECTION LOCATIONS: "<<endl;
					cout << interpts[count];
					count++;
				}
			}
		}
	}

	//Puts ones that have nothing close to it into the alive vector
	for(int i = 0; i < sensornumber; i++)
	{
		if(find(withinRADIUS.begin(), withinRADIUS.end(), sensor[i])
		 != withinRADIUS.end()){}
		else{
			active.push_back(sensor[i]);
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
	for(int i = 0; i < active.size(); i++){
		cout <<active[i];
		cout <<"COUNT: "<<i<<endl;
	}

	return 0;
}
//TODO: Make sure the math is correct
void getintpts(int i_x0, int i_y0, int i_x1, int i_y1, int d)
{
	int a, b, h, x3, y3, x4, y4, x2, y2;
	x2 = i_x0+d;
	y2 = i_y0 + d;
	a = ((d*d)/(2*d));
	b = a;
	h = sqrt((RADIUS * RADIUS) - (a*a));

	x3 = x2 + (((h*(i_y1 - i_y0)))/d);
	x4 = x2 - (((h*(i_y1 - i_y0)))/d);
	y3 = y2 + (((h*(i_x1 - i_x0)))/d);
	y4 = y2 - (((h*(i_x1 - i_x0)))/d);

	interpts.push_back(intpts(x3,y3,x4,y4));
}

