//
// Created by Dillon Hess on 4/4/17.
//

#ifndef CS2500_SOLUTIONS_H
#define CS2500_SOLUTIONS_H

#include <iostream>
#include "sensor.h"
#include "intpts.h"
#include <vector>
using namespace std;

//Sensor ss;
//class intpts;
float activesensors(const vector<Sensor> &s, int sensornumber);
float alivesensors(const vector<Sensor> &s, int sensornumber);
float resenergy(const vector<Sensor> &s, int sensornumber);
float percentcovg(const vector<Sensor> &s, int sensornumber);
#endif //CS2500_SOLUTIONS_H
