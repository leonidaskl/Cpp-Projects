#include "pch.h"
#include <iostream>  
#include <algorithm>  
#include <fstream>  

using namespace std;

#define BSIZE 1<<15  

char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

long readLong()
{
	long d = 0L, x = 0L;
	char c;

	while (1) {
		if (bpos >= bsize) {
			bpos = 0;
			if (feof(stdin)) return x;
			bsize = fread(buffer, 1, BSIZE, stdin);
		}
		c = buffer[bpos++];
		if (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); d = 1; }
		else if (d == 1) return x;
	}
	return -1;
}


class Particles {
public:
	long long v;
	long long t;
	long long x;
	float temp;
	long long index;
};


int main()
{


	ifstream infile("Text.txt");  

	int n, l, k;
	//infile >> n >> l >> k;

	n = readLong();
	l = readLong();
	k = readLong();

	Particles * a = new Particles[n];
	Particles * b = new Particles[n];

	for (int i = 0; i < n; i++) {
		//infile >> a[i].t >> a[i].v;

		a[i].t = readLong();
		a[i].v = readLong();

		a[i].index = i + 1;
		a[i].x = a[i].temp = 0 - (a[i].v * (double)a[i].t);
	}

	for (int i = 0; i < n; i++) {
		//infile >> b[i].t >> b[i].v;

		b[i].t = readLong();
		b[i].v = readLong();

		b[i].index = i + 1;
		b[i].x = b[i].temp = 0 - (b[i].v * (double)b[i].t);
	}





	for (int i = 0; i < k; i++)
	{
		long long maxa, maxb;
		long long maxa_2, maxb_2;
		long long tempa = -1, tempb = -1;

		while (true) {
			maxa = a[i].x;
			maxb = b[i].x;

			float distance_0 = (float)l - (a[i].x + b[i].x);
			float veloc_0 = (float)a[i].v + b[i].v;
			float turns = distance_0 / veloc_0;

			maxa_2 = maxa;
			maxb_2 = maxb;
			for (int j = i; j < n; j++) {


				a[j].temp = (a[j].x + a[j].v * turns);
				b[j].temp = (b[j].x + b[j].v * turns);

				if (a[j].temp > maxa_2) {
					swap(a[j], a[i]);
					maxa_2 = a[j].temp;
				}
				if (b[j].temp > maxb_2) {
					swap(b[j], b[i]);
					maxb_2 = b[j].temp;
				}

			}

			if ((a[i].x == maxa) && (b[i].x == maxb)) {
				cout << a[i].index << " " << b[i].index << endl;
				break;

			}


		}
	}


	return 1;
}
