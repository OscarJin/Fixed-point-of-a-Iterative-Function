#include "pch.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#define NUM 32769
using namespace std;

const double MAX = 32768;

struct Turning_Point
{
	double x;
	double y = 0;
	bool status = false;
};
Turning_Point a[NUM];

long long gcd(long long x, long long y);

void init();

void Find_Turning_Point();

double transy(double y);

void Print_Answer();

int main()
{
	init();

	Find_Turning_Point();

	Print_Answer();

	return 0;
}

long long gcd(long long x, long long y)
{
	return (y == 0) ? x : gcd(y, x%y);
}

void init(void)
{
	for (int i = 0; i < NUM; i++)
	{
		a[i].x = i;
	}
	a[0].y = 0.5;
	a[0].status = true;
	a[(int)MAX / 2].y = 1;
	a[(int)MAX / 2].status = true;
	a[(int)MAX].y = 0;
	a[(int)MAX].status = true;
}

void Find_Turning_Point()
{
	for (int t = 1; t < 15; t++)
	{
		int temp1 = 0;
		int temp2 = 0;
		for (int j = 0; j < NUM; j++)
		{
			if (a[j].status == true)
			{
				if (j > 0)
				{
					temp2 = j;
					if (a[temp1].y + a[temp2].y == 1)
					{
						a[(temp1 + temp2) / 2].status = true;
						a[(temp1 + temp2) / 2].y = 1;
					}
					a[temp1].y = transy(a[temp1].y);
					temp1 = temp2;
				}
			}
		}
		a[(int)MAX].y = transy(a[(int)MAX].y);
	}
}

double transy(double y)
{
	if (y == 0)
		return 0.5;
	else if (y == 0.5)
		return 1;
	else if (y == 1)
		return 0;
}

void Print_Answer()
{
	int temp1 = 0;
	int temp2 = 0;
	int sum2 = 0;
	for (int i = 0; i < NUM; i++)
	{
		if (a[i].status == true)
		{
			if (i > 0)
			{
				temp2 = i;
				if ((a[temp1].y < a[temp1].x / MAX) && (a[temp2].y > a[temp2].x / MAX)
					|| (a[temp1].y > a[temp1].x / MAX) && (a[temp2].y < a[temp2].x / MAX)
					|| (a[temp1].x / MAX == a[temp1].y))
				{
					sum2++;
					double x1 = a[temp1].x;
					double y1 = a[temp1].y;
					double x2 = a[temp2].x;
					double y2 = a[temp2].y;
					long long fenzi = (abs(x1 - MAX * y1) * abs(x2 - x1)) + x1 * (abs(x1 - MAX * y1) + abs(x2 - MAX * y2));
					long long fenmu = MAX * (abs(x1 - MAX * y1) + abs(x2 - MAX * y2));
					long long c = gcd(fenzi, fenmu);
					cout << sum2 << ": \t" << fenzi / c << " / " << fenmu / c << endl;
				}
				temp1 = temp2;
			}

		}
	}
	cout << sum2 + 1 << ": \t" << "1 / 1" << endl << endl;
	cout << sum2 + 1 << "    In All!!!" << endl;
}
