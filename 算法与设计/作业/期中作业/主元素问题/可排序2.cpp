#include <iostream>
#include <map> 
using namespace std;

int main() {
	map<int, int> times;
	int n, *arr;
	cin >> n;
	arr = (int*)malloc(n * sizeof(int));
	if (!arr)
		exit(-1);
	for (int i = 0; i < n; ++i) 
		cin >> arr[i];
	for (int i = 0; i < n; ++i) {
		if (times.count(arr[i])) {
			++times[arr[i]];
		}
		else {
			times[arr[i]] = 1;
		}
		if (times[arr[i]] > n/2) {
			cout << arr[i];
			return 0;
		}
	}
	cout << "ÎÞÖ÷ÔªËØ" << endl;
	
	return 0;
} 
