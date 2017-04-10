//
// Created by Dillon Hess on 4/4/17.
//

#include "solutions.h"
#include <fstream>

//Gets how many active sensors exists at the given round
float activesensors(const vector<Sensor> &s, int sensornumber) {
	float percent;
	float count = 0;
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i].active)
		{
			count++;
		}
	}
	percent = count / static_cast<float>(sensornumber);
	return percent;
}

//Gets how many sensors are live at the given round
float alivesensors(const vector<Sensor> &s, int sensornumber) {
	float percent;
	float dead = 0;
	for(int i = 0; i < s.size(); i++)
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
		if(!s[i].active && s[i].energy > 0){
			total += s[i].energy;
		}
	}

	return total;
}

//Gets the coverage range of sensors at a given round
float percentcovg(const vector<Sensor> &s, int sensornumber) {
	float covered = 0;
	int counter = 0;
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i].active && s[i].energy > 0){
			counter++;
		}

	}
	for(int i = 0; i < s.size(); i++) {
		int rnd = rand() % (50 * 50);
		int x = rnd % 50;
		int y = rnd / 50;
		for(int j = 0; j < s.size(); j++)
		{
			int testx = abs(s[j].xpos - x);
			int testy = abs(s[j].ypos - y);
			if(testx < 5 && testy < 5 && s[j].active)
			{
				covered++;
				j = s.size() - 1;
			}
		}
	}
	//cout <<"COVERED: "<<covered<<endl;
//	cout <<"SIZE: "<<s.size()<<endl;
	return covered/counter;
}

//Bottom Up Approach
//void bottomup(vector <Sensor> &s, const vector <intpts> &ip,
//              vector <Sensor> &a, int sensornumber, int maxactive) {
//	int temp_pos;
//	int counter = 0;
//	//cout <<"IP SIZE: "<<ip.size()<<endl;
//	ofstream fallalive;
//	for(int i = 0; i < ip.size(); i++)
//	{
//		temp_pos = ip[i].s1;
//		if(s[temp_pos].active){}
//		else
//		{
//		//	cout <<"Stuck in here?"<<endl;
//			if(foundintcp(temp_pos, ip, s, i))
//			{
//				temp_pos = ip[i].s2;
//				if(foundintcp(temp_pos, ip, s, i))
//				{
//					s[temp_pos].active = false;
//				//	cout <<"GETS IN HERE"<<endl;
//					temp_pos = ip[i].s1;
//					s[temp_pos].active = true;
//				} else{
//					s[temp_pos].active = true;
//					temp_pos = ip[i].s2;
//					s[temp_pos].active = false;
//				}
//			}
//			else
//			{
//				//cout <<"how about here?"<<endl;
//				s[ip[i].s1].active = true;
//				temp_pos = ip[i].s2;
//				s[temp_pos].active = false;
//			}
//
//		}
//		fallalive.open("../allalive.csv");
//		fallalive <<"Round, Active"<<endl;
//		//cout<<i<<","<< s[i].active<<endl;
//		if(s[i].active == true)
//			counter++;
//	}
//	fallalive.close();
//	if(counter >= maxactive)
//		maxactive = counter;
//	//cout <<"Number active:"<<counter<<endl;
//	cout <<"MAXACTIVE: "<<maxactive<<endl;
//}

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
		return ((xdis1 == 5 && ydis1 == 5) || (xdis2 == 5 && ydis2 == 5))
		       && i != j && s[j].active;
	}
}


//Bottom Up
void testbottomup(vector<Sensor> &s, const vector<intpts> &ip, vector<Sensor> &a)
{
	int tmp1;
	int tmp2;
	for (int i = 0; i < s.size(); i++) {
		bool contains = true;
		if (s[i].active && s[i].energy > 0) {
			if(a.size() != 0) {
				for (int j = 0; j < s.size(); j++) {
					if (s[i].xpos == a[j].xpos && s[i].ypos == a[j].ypos) {
						contains = false;
						j = s.size() - 1;
					}
				}
			}
			if (contains) {
				for (int j = 0; j < ip.size(); j++)
				{
					tmp1 = ip[j].s1;
					tmp2 = ip[j].s2;
					if (s[tmp1] == s[i] || s[tmp2] == s[i])
					{
						a.push_back(s[i]);
						j = ip.size() - 1;
						cout << "ACTIVE SIZE: " << a.size() << endl;
						}
				}
			}
		}
	}
}


//Top-Down

void testtopdown(vector<Sensor> &s, vector<Sensor> &a, int time) {
	float coverage;
	//cout <<"Gets here"<<endl;
	if(time == 0) {
		for (int i = 0; i < s.size(); i++) {
			a.push_back(s[i]);
		}
	}
	else {
		int rnd = rand() % (50 * 50);
		int pos = rnd % 50;
		float temp_covg = percentcovg(a, time);
		a[pos].active = false;
		coverage = percentcovg(a, time);
		if ((coverage < temp_covg) && a[pos].energy > 0)
			a[pos].active = true;
	}
}






