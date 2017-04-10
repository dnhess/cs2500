//
// Created by Dillon Hess on 4/4/17.
//

#ifndef CS2500_SOLUTIONS_H
#define CS2500_SOLUTIONS_H

#include <iostream>
#include "sensor.h"
#include "intpts.h"
#include "test.h"
#include <vector>
using namespace std;

//Sensor ss;
//class intpts;
float activesensors(const vector<Sensor> &s, int sensornumber);
float alivesensors(const vector<Sensor> &s, int sensornumber);
float resenergy(const vector<Sensor> &s, int sensornumber);
float percentcovg(const vector<Sensor> &s, int sensornumber);

//Bottom Up Approach
void bottomup(vector<Sensor> &s, const vector<intpts> &ip, vector<Sensor> &a, int
sensornumber, int called);

void testbottomup(vector <Sensor> &s, const vector <intpts> &ip, vector<Sensor> &a);

void testtopdown(vector<Sensor> &s, vector<Sensor> &a, int time);

bool foundintcp(int pos, const vector<intpts> &ip, const vector<Sensor> &s, int i);

void greedy(vector<Sensor> &s, vector<Sensor> &a, vector <intpts> &ip, vector
		<test> &tba, int &currentpos);

int countintpts(int pos, int loc, vector<test> &tba, vector<intpts> &ip,
                vector<Sensor> &s, int counter);

void activation(vector<Sensor> &a, int &currentpos, vector<test> & tba,
                vector<Sensor> &s);

//void insert(vector<test> &tba, int value );
#endif //CS2500_SOLUTIONS_H
