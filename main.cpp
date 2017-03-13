#include <iostream>
#include <ctime>
using namespace std;
int main() {
	short sensornumber;
	//int pointx[50];
	//int pointy[50];
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
		//pointx[x] = 1;
		//pointy[y] = 1;
		grid[x][y] = 1;
	}

	for(int c = 0; c < 50; c++)
	{
		for(int d = 0; d < 50; d++)
			cout <<"x: "<<c<<" y: "<<d<<"Grid Number: "<<grid[c][d]<<endl;
	}
}