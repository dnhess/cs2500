//
// Created by Dillon Hess on 3/26/17.
//

#ifndef CS2500_INTPTS_H
#define CS2500_INTPTS_H

#include <iostream>
using namespace std;
class intpts {
public:
	int x_1;
	int y_1;
	int x_2;
	int y_2;
	int s1;
	int s2;
	intpts() {}
	intpts(int x1, int y1, int x2, int y2, int sen1pos, int sen2pos) :	x_1(x1), y_1
			(y1), x_2(x2), y_2(y2), s1(sen1pos), s2(sen2pos) {}
	friend ostream& operator <<(ostream& outs, const intpts& i);
};


#endif //CS2500_INTPTS_H
