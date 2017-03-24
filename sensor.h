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
	friend ostream& operator <<(ostream& outs, const Sensor& sensor);
};
#endif //CS2500_SENSOR_H
