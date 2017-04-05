//
// Created by Dillon Hess on 3/23/17.
//

#include "sensor.h"
using namespace std;
//Outputting Sensor info
ostream& operator <<(ostream& outs, const Sensor& sensor) {
	outs << sensor.xpos <<"," << sensor.ypos <<","<< sensor.energy << endl;
	return outs;
}
//Comparison of sensors
bool operator==(const Sensor &s1, const Sensor &s2) {
	return((s1.xpos * s2.ypos) == (s2.xpos * s1.ypos));
}
//Subtraction of sensors
Sensor Sensor ::operator-(Sensor t) {
	Sensor tmp;
	tmp.xpos = xpos - t.xpos;
	tmp.ypos = ypos - t.ypos;
	tmp.energy = t.energy;
	tmp.active = t.active;
	return tmp;
}

/*bool Sensor::halfleft(const vector<Sensor> &s, int sensornumber)
{
	int count = 0;
	for(int i = 0; i < sensornumber; i++)
	{
		if(s[i].alive == true)
		{
			count++;
		}
	}
	return count >= (sensornumber / 2);
}*/