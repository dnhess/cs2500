//
// Created by Dillon Hess on 4/4/17.
//

#include "solutions.h"
#include <fstream>

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

//Bottom Up Approach

//TODO: This is not working
void bottomup(vector <Sensor> &s, const vector <intpts> &ip,
              vector <Sensor> &a, int sensornumber, int maxactive) {
	int temp_pos;
	int counter = 0;
	//cout <<"IP SIZE: "<<ip.size()<<endl;
	ofstream fallalive;
	for(int i = 0; i < ip.size(); i++)
	{
		temp_pos = ip[i].s1;
		if(s[temp_pos].active){}
		else
		{
		//	cout <<"Stuck in here?"<<endl;
			if(foundintcp(temp_pos, ip, s, i))
			{
				temp_pos = ip[i].s2;
				if(foundintcp(temp_pos, ip, s, i))
				{
					s[temp_pos].active = false;
				//	cout <<"GETS IN HERE"<<endl;
					temp_pos = ip[i].s1;
					s[temp_pos].active = true;
				} else{
					s[temp_pos].active = true;
					temp_pos = ip[i].s2;
					s[temp_pos].active = false;
				}
			}
			else
			{
				//cout <<"how about here?"<<endl;
				s[ip[i].s2].active = true;
				//cout <<"STATUS:"<<i<<","<<s[i].active<<endl;
				temp_pos = ip[i].s1;
				s[temp_pos].active = false;
			}

		}
		fallalive.open("../allalive.csv");
		fallalive <<"Round, Active"<<endl;
		//cout<<i<<","<< s[i].active<<endl;
	}
	for(int i = 0; i < sensornumber; i++) {
		if (s[i].active == true)
			counter++;
	}
	fallalive.close();
	if(counter >= maxactive)
		maxactive = counter;
	//cout <<"Number active:"<<counter<<endl;
	cout <<"MAXACTIVE: "<<maxactive<<endl;
}

bool foundintcp(int pos, const vector<intpts> &ip, const vector<Sensor> &s,
                int i) {
	int xdis1;
	int ydis1;
	int xdis2;
	int ydis2;
	//cout <<"Stuck?"<<endl;
	for(int j = 0; j < ip.size(); i++)
	{
		xdis1 = abs(s[pos].xpos - ip[j].x_1);
		ydis1 = abs(s[pos].ypos - ip[j].y_1);
		xdis2 = abs(s[pos].xpos - ip[j].x_2);
		ydis2 = abs(s[pos].ypos - ip[j].y_2);
		//cout <<"Stuck 2?"<<endl;
		if(((xdis1 == 5 && ydis1 == 5) || (xdis2 == 5 && ydis2 == 5))
		   && i != j && s[j].active)
		{
			return true;
		} else{
			return false;
		}
	}
}

void testbottomup(vector<Sensor> &s, const vector<intpts> &ip, int snum) {

	for(int i = 0; i < snum; i++)
	{
		if(s[i].active && s[i].energy > 0){

		}
	}
}







