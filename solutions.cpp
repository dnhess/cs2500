//
// Created by Dillon Hess on 4/4/17.
//

#include "solutions.h"
#include "math.h"
#include <fstream>

//Gets how many active sensors exists at the given round
float activesensors(const vector<Sensor> &s, int sensornumber) {
	float percent;
	float count = 0;
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i].active && s[i].energy > 0)
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
	float percent;
	int distance = 0;
	for(int i = 0; i < sensornumber; i++) {
		int rnd = rand() % (50 * 50);
		int x = rnd % 50;
		int y = rnd / 50;
		for(int j = 0; j < s.size(); j++)
		{
			distance = abs((int) sqrt(((s[j].xpos - x) * (s[j].xpos - x)) + ((s[j].ypos - y) * (s[j].ypos - y))));
			if(distance <= 5 && s[j].active && s[j].energy > 0)
			{
				covered++;
				//j = s.size() - 1;
			}
		}
	}
	percent = covered/sensornumber;
	if(percent > 1)
		percent = 1;
	return percent;
}

bool foundintcp(int pos, const vector<intpts> &ip, const vector<Sensor> &s,
                int i) {
	int xdis1;
	int ydis1;
	int xdis2;
	int ydis2;
	for(int j = 0; j < ip.size(); i++)
	{
		xdis1 = abs(s[pos].xpos - ip[j].x_1);
		ydis1 = abs(s[pos].ypos - ip[j].y_1);
		xdis2 = abs(s[pos].xpos - ip[j].x_2);
		ydis2 = abs(s[pos].ypos - ip[j].y_2);
		return ((xdis1 == 5 && ydis1 == 5) || (xdis2 == 5 && ydis2 == 5))
		       && i != j && s[j].active;
	}
}


//Bottom Up
void testbottomup(vector<Sensor> &s, const vector<intpts> &ip, vector<Sensor> &a)
{
	int tmp1;
	int tmp2;
	float distance;
	for (int i = 0; i < s.size(); i++) {
		bool contains = true;
		if (s[i].active) {
				for (int j = 0; j < a.size(); j++) {
					distance = abs((int) sqrt(((a[j].xpos - s[i].xpos) *
							(a[j].xpos - s[i].xpos)) + ((a[j].ypos - s[i].ypos)
					                                    * (a[j].ypos - s[i].ypos)
					)));
					if ((s[i].xpos == a[j].xpos && s[i].ypos == a[j].ypos) ||
							distance <= 10 && !a[j].active) {
						contains = false;
						j = a.size() - 1;
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
						}
				}
			}
		}
	}
}


//Top-Down

void testtopdown(vector<Sensor> &s, vector<Sensor> &a, int time) {
	float coverage;
	int count;
	if(time == 0) {
		for (int i = 0; i < s.size(); i++) {
			a.push_back(s[i]);
		}
	}
	else {
		while(count != s.size())
		{
			int rnd = rand() % (50 * 50);
			int pos = rnd % 50;
			float temp_covg = percentcovg(a, s.size());
			a[pos].active = false;
			coverage = percentcovg(a, s.size());
			if ((coverage < temp_covg) && a[pos].energy > 0) {
				a[pos].active = true;
				count++;
			}
			if(coverage >= temp_covg) {
				count = s.size();
			}
		}
	}
}

void greedy(vector<Sensor> &s, vector<Sensor> &a, vector<intpts> &ip,  vector
		<test> &tba, int &currentpos) {
	int temp1;
	int temp2;
	bool skip = false;
	int counter = 0;
	if(currentpos == 0) {
		for (int i = 0; i < ip.size(); i++) {
			temp1 = countintpts(ip[i].s1, i, tba, ip, s, 2);
			temp2 = countintpts(ip[i].s2, i, tba, ip, s, 2);
			if (temp1 > 0)
				tba.push_back(test(ip[i].s1, temp1));
			if (temp2 > 0)
				tba.push_back(test(ip[i].s2, temp2));
		}
		for(int i = 0; i < s.size(); i++)
		{
			for(int j = 0; j < tba.size(); j++)
			{
				if(tba[j].pos == i){
					counter++;
					skip = true;
				}
			}
			if(skip == false) {
				tba.push_back(test(i, 0));
				skip = false;
			}
		}
	}
	sort(tba.begin(), tba.end());
	activation(a, currentpos, tba, s);
}

int countintpts(int pos, int loc, vector<test> &tba, vector<intpts> &ip, vector<Sensor> &s, int counter ) {
	for (int i = 0; i < tba.size(); i++) {
		if (tba[i].pos == ip[pos].s1) {
			return 0;
		}
		if(tba[i].pos == ip[pos].s2)
		{
			return 0;
		}
	}
	for (int i = loc + 1; i < ip.size(); i++) {
		if ((ip[i].s1 == pos || ip[i].s2 == pos) && (ip[loc].s1 != ip[i].s2 && (ip[loc].s2 != ip[i].s1))) {
			counter++;
		}
	}
	return counter;
}

void activation(vector<Sensor> &a, int &currentpos, vector<test> & tba,
                vector<Sensor> &s) {
	cout <<"COUNT: "<<currentpos<<"SIZE: "<<tba.size()<<endl;
	cout <<"COVERAGE: "<<percentcovg(a, s.size())<<endl;
	if( tba.size() == currentpos) {
		return;
	}
	if((percentcovg(a, s.size()) < .98 || currentpos == 0))
	{
		a.push_back(s[tba[currentpos].pos]);
		currentpos++;
		activation(a, currentpos, tba, s);
	}
}




