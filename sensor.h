//
// Created by Dillon Hess on 3/23/17.
//

#ifndef CS2500_SENSOR_H
#define CS2500_SENSOR_H

#include <iostream>

using namespace std;
class Sensor
{
public:
	int xpos;
	int ypos;
	int energy;
	Sensor() {}
	Sensor(int x, int y, int e) : xpos(x), ypos(y), energy(e) {}
	//Allows for us to see the sensor information
	friend ostream& operator <<(ostream& outs, const Sensor& sensor);
	//Allows for comparison of sensors
	friend bool operator==(const Sensor &s1, const Sensor &s2);
	//Allows for subtraction of two sensors (Could be useful later)
	Sensor operator-(Sensor);

};
#endif //CS2500_SENSOR_H
