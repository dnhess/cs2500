//
// Created by Dillon Hess on 4/4/17.
//

#include "solutions.h"

int activesensors(const vector<Sensor> &s, int sensornumber) {
	float percent;
	int count = 0;
	for(int i = 0; i < sensornumber; i++)
	{
		if(s[i].active)
		{
			count++;
		}
	}
	//cout <<"count value: "<<count<<endl;
	percent = count/sensornumber;
	return percent;
}
