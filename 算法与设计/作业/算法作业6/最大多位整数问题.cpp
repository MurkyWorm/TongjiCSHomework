#include <iostream>
#include <vector>
#include <math.h>
#include<algorithm>
using namespace std;

bool comp(long long a, long long b) {
	int n1 = 1, n2 = 1;
	while (true) {
		if (a / n1 == 0) {
			break;
		}
		n1 = n1 * 10;
	}
	while (true) {
		if (b / n2 == 0) {
			break;
		}
		n2 = n2 * 10;
	}
	long long result1, result2;
	result1 = a * n2 + b;
	result2 = b * n1 + a;
	return result1 > result2;
}

int main () {
	int n;
	cin >> n; 
	vector<long long> array(n);
	for (int i = 0; i < n; ++i) {
		cin >> array[i];
	}
	sort(array.begin(), array.end(), comp);
	for (int i = 0; i < n; ++i) {
		cout << array[i];
	}
	
	return 0;
} 
