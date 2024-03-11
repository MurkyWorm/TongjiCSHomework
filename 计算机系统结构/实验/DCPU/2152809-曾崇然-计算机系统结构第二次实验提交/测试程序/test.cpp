#include <iostream>
using namespace std;

int main() {
	int a[60];
	int b[60];
	int c[60];
	unsigned int d[60];
	
	for (int i = 0; i < 60; i++) {
		if (i == 0) {
			a[0] = 0;
			b[0] = 1;
			c[0] = a[0];
			d[0] = b[0];
		}
		else if (i > 0 && i <= 19) {
			a[i] = a[i - 1] + i;
			b[i] = b[i - 1] + 3 * i;
			c[i] = a[i];
			d[i] = b[i];
		}
		else if (i >= 20 && i <= 39) {
			a[i] = a[i - 1] + i;
			b[i] = b[i - 1] + 3 * i;
			c[i] = a[i] + b[i];
			d[i] = a[i] * c[i];
		}
		else {
			a[i] = a[i - 1] + i;
			b[i] = b[i - 1] + 3 * i;
			c[i] = a[i] * b[i];
			d[i] = b[i] * c[i];
		}
	}
	
	cout << a[59] << endl;
	cout << b[59] << endl;
	cout << c[59] << endl;
	cout << d[59] << endl;
} 
