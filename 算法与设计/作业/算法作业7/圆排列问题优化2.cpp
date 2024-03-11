#include <iostream>
#include <algorithm>
#include <math.h>
#include <time.h>
using namespace std;

int n;
double minlen, x[20], r[20], b[20];

double center (int j) {
	double x_j = 0;
	for (int i = 1; i < j; ++i) {
		x_j = max(x_j, x[i] + 2 * sqrt(r[i] * r[j]));
	}
	return x_j;
}

void compute () {
	double left = 0, right = 0;
	for (int i = 0; i <= n; ++i) {
		if (x[i] - r[i] < left) {
			left = x[i] - r[i];
		}
		if (x[i] + r[i] > right) {
			right = x[i] + r[i];
		}
	}
	if (right - left < minlen) {
		minlen = right - left;
		for (int i = 1; i <= n; ++i) {
			b[i] = r[i];
		}
	}
}

void dfs (int j) {
	if (j > n) {
		compute();
	}
	else {
		int rec[20];
		int p = 0;
		for (int i = j; i <= n; ++i) {
			if (j != 1 || i != n) {
				bool flag = 1;
				for (int k = 0; k < p; ++k) {
					if (rec[k] == r[i]) {
						flag = 0;
					}
				}
				if (flag == 1) {
					swap (r[j], r[i]);
					double x_tmp = center(j);
					if (x_tmp + r[1] + r[j] < minlen) {
						x[j] = x_tmp;
						dfs (j + 1);
					}
					swap (r[j], r[i]);
					rec[p] = r[i];
					++p;
				}
			}
		}
	}
}

int main () {
	clock_t start,end;
	minlen = 1e20;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> r[i];
	}
	start = clock(); 
	dfs (1);
	cout << minlen << endl;
	for (int i = 1; i <= n; ++i) {
		cout << b[i] << " ";
	}
	cout << endl;
	end = clock();
	cout << "time = " << double(end-start)/CLOCKS_PER_SEC << "s" << endl;
	return 0;
}
