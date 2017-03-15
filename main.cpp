#include <iostream>
using namespace std;
int main() {
	//Code Idea
	/*
	 * The idea of the code is to first generate a grid system that stores 1s
	 * and 0s. The 1s will represent the actual sensor coordinates and the 0s
	 * will represent the empty space (Note: The radius of coverage has not
	 * been shown yet)
	 *
	 * To find a sensor the program will loop through the entire grid system
	 * looking for the 1s. Once it finds a 1 it will check to see if there
	 * are any 1s in a radius of 5
	 */

	short sensornumber;
	int R = 5;
	cin >> sensornumber;

	int grid[50][50];
	for(int a = 0; a < 50; a++)
	{
		for(int b = 0; b < 50; b++)
		{
			grid[a][b] = 0;
		}
	}
	for (int i = 0; i <=sensornumber; i++)
	{
		int rnd = rand() % (50*50);
		int x = rnd % 50;
		int y = rnd / 50;
		grid[x][y] = 1;
	}

	for(int c = 0; c < 50; c++)
	{
		for(int d = 0; d < 50; d++)
			cout <<"|"<<grid[c][d]<<"|";
		cout <<endl;
	}

}