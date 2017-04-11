//
// Created by Dillon Hess on 4/9/17.
//

#ifndef CS2500_TEST_H
#define CS2500_TEST_H


class test {
public:
	int pos;
	int count;
	test() {};
	test(int p, int c) : pos(p), count(c) {}

	bool operator < (const test& str) const
	{
		return (count < str.count);
	}
};


#endif //CS2500_TEST_H
