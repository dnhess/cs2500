#include <math.h>
#include <algorithm>
#include "intpts.h"
#include "solutions.h"
#include <fstream>

//HERE
void getintpts(int i_x1, int i_y1, int r_x2, int r_y2, int d, int pos1, int
pos2);
int RADIUS = 5;
vector <intpts> interpts; //The location of the intersection


int main() {
	srand(time(NULL));
	int sensornumber;
	int distance;
	ofstream ftest;
	ofstream fallalive;
	ofstream fallactive;
	ofstream fresenergy;
	ofstream fperccov;
	int time = 0;
	int time1 = 0;
	//int count = 0;
	vector <Sensor> sensor;  //Initial Sensors that are generated
	vector <Sensor> withinRADIUS; //Sensors that are within a 5 distance
	vector <Sensor> active; //Sensors that will always be active

	cin >> sensornumber;

	//Randomly add the sensors to random positions
	for (int i = 0; i < sensornumber; i++) {
		int rnd = rand() % (50 * 50);
		int x = rnd % 50;
		int y = rnd / 50;
		sensor.push_back(Sensor(x,y,300,true)); //xpos, ypos, energy, alive
		// status
	}


	//Testing to find if sensors are in distance < RADIUS and finding
	// intersection points
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
					          sensor[j].ypos, distance, i, j);
					/*
					cout << "Points that cause Intersection: " << endl;
					cout <<sensor[i];
					cout <<sensor[j];
					cout <<"with a distance of: "<<distance<<endl;
					cout <<"count: "<<count<<endl;
					cout <<"INTERSECTION LOCATIONS: "<<endl;
					cout << interpts[count];
					count++;
					 */
				}
			}
		}
	}

	//Note: Probably not needed
	//Puts ones that have nothing close to it into the alive vector
//	for(int i = 0; i < sensornumber; i++) {
//		if(find(withinRADIUS.begin(), withinRADIUS.end(), sensor[i])
//		 != withinRADIUS.end()){}
//		else{
//			active.push_back(sensor[i]);
//		}
//	}


	//TODO: Remove sample output
	/*
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
*/

	//This generates an excel file
	//Note: This wipes the file every time it opens it again
	//NOTE: Will generate file 1 directory above current director
//	ftest.open("../test.csv");
//	ftest <<"xpos, ypos, energy"<<endl;
//	for(int i = 0; i < sensornumber; i++) {
//		ftest << sensor[i] << endl;
//	}
//	ftest.close();


//	cout<<"Size of active"<<active.size()<<endl;

	//NOTE: Will generate file 1 directory above current directory
	//======TESTS=====
	fallalive.open("../allalive.csv");
	fallalive <<"Round, Percent Alive"<<endl;
	fallactive.open("../allactive.csv");
	fallactive <<"Round, Percent Active"<<endl;
	fresenergy.open("../resenergy.csv");
	fresenergy <<"Round, Residual Energy"<<endl;
	fperccov.open("../perccov.csv");
	fperccov <<"Round, Percentage Covered"<<endl;
	do
	{
		//In theory the algorithm functions can be placed in here and be
		// forced every couple of rounds to adjust the sensors.
		//	bottomup(sensor, interpts, active, sensornumber, time1);

		//TODO: FIX THIS
		//testbottomup(sensor, interpts, active);
		//Works.... kind of
		testtopdown(sensor,active,time);
		//Reduces energy of active sensors by 1 each round


		//Problem in this?
		for(int i = 0; i < active.size(); i++)
		{
			if(active[i].active && active[i].energy > 0) {
				active[i].energy--;
				if (active[i].energy <= 0)
					active[i].active = false;
			for(int j = 0; j < sensor.size(); j++)
				if(sensor[j].xpos == active[i].xpos && sensor[j].ypos == active[i].ypos)
				{
					sensor[j].energy--;
					//cout <<"SENSOR AT:  "<<j<<endl;
					if(sensor[j].energy <= 0)
						sensor[j].active = false;
				}
			}
		}

		//Outputs the data
	//	cout <<alivesensors(active,sensornumber)<<endl;
		fallalive<<time<<","<< alivesensors(active,sensornumber)<<endl;
		fallactive<<time<<","<< activesensors(active,sensornumber)<<endl;
		fresenergy<<time<<","<< resenergy(active,sensornumber)<<endl;
		fperccov<<time<<","<<percentcovg(active,sensornumber)<<endl;
		time++;
	}while(time < 1000);
	//Closing files
	fallalive.close();
	fallactive.close();
	fresenergy.close();
	fperccov.close();

	return 0;
}

//Calculate the intersections caused by the sensors
void getintpts(int i_x0, int i_y0, int i_x1, int i_y1, int d, int pos1, int
pos2)
{
	int a, h, x3, y3, x4, y4, x2, y2;
	a = ((d*d)/(2*d));
	x2 = i_x0 + ((a*(i_x1-i_x0))/d);
	y2 = i_y0 + ((a*(i_y1-i_y0))/d);
	h = sqrt((RADIUS * RADIUS) - (a*a));

	x4 = x2 + (((h*(i_y1 - i_y0)))/d);
	x3 = x2 - (((h*(i_y1 - i_y0)))/d);
	y3 = y2 + (((h*(i_x1 - i_x0)))/d);
	y4 = y2 - (((h*(i_x1 - i_x0)))/d);

	interpts.push_back(intpts(x3,y3,x4,y4, pos1, pos2));
}