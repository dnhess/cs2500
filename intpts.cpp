//
// Created by Dillon Hess on 3/26/17.
//

#include "intpts.h"
ostream& operator <<(ostream& outs, const intpts& i) {
	outs << "x3: "<<i.x_1<<endl;
	outs << "y3: "<<i.y_1<<endl;
	outs << "x4: "<<i.x_2<<endl;
	outs << "y4: "<<i.y_2<<endl;
	outs <<" pos of sen 1"<< i.sen1<<endl;
	outs <<" pos of sen 2"<< i.sen2<<endl;
	return outs;
}