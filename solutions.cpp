//
// Created by Dillon Hess on 4/4/17.
//

#include "solutions.h"

//Gets how many active sensors exists at the given round
float activesensors(const vector<Sensor> &s, int sensornumber) {
	float percent;
	float count = 0;
	for(int i = 0; i < sensornumber; i++)
	{
		if(s[i].active)
		{
			count++;
		}
	}
	percent = (count/static_cast<float>(sensornumber));
	return percent;
}

//Gets how many sensors are live at the given round
float alivesensors(const vector<Sensor> &s, int sensornumber) {
	float percent;
	float dead = 0;
	for(int i = 0; i < sensornumber; i++)
	{
		if(s[i].energy <= 0)
		{
			dead++;
		}
	}
	percent = (static_cast<float>(sensornumber)-dead)/static_cast<float>(sensornumber);
	return percent;
}

//Gets the residual energy at a given round (energy of non-active, alive
// sensors)
float resenergy(const vector<Sensor> &s, int sensornumber) {
	float total = 0;
	for(int i = 0; i < sensornumber; i++)
	{
		if(!s[i].active){
			total += s[i].energy;
		}
	}

	return total;
}

//Gets the coverage range of sensors at a given round
float percentcovg(const vector<Sensor> &s, int sensornumber) {
	float covered = 0;
	for(int i = 0; i < (sensornumber); i++) {
		int rnd = rand() % (50 * 50);
		int x = rnd % 50;
		int y = rnd / 50;
		for(int j = 0; j < sensornumber; j++)
		{
			int testx = abs(s[j].xpos - x);
			int testy = abs(s[j].ypos - y);
			//cout <<testx<<","<<testy<<endl;
			if(testx < 5 && testy < 5 && s[j].active)
			{
				covered++;
				j = sensornumber - 1;
			}
		}
	}
	return covered/sensornumber;
}


