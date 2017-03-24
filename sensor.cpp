//
// Created by Dillon Hess on 3/23/17.
//

#include "sensor.h"
using namespace std;

ostream& operator <<(ostream& outs, const Sensor& sensor)
{
	outs << "xpos: " << sensor.xpos<<endl;
	outs << "ypos: " << sensor.ypos<<endl;
	outs << "energy: " << sensor.energy<<endl;
	return outs;
}