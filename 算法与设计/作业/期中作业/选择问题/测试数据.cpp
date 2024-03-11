#include <iostream> 
#include <fstream>
#include <time.h>
using namespace std;

int main () {
	srand((unsigned)time(NULL));
	int n, k;
	ofstream out;
	cin >> n;
	cin >> k;
	out.open("test.txt",ios::out);
	out << n << " ";
	out << k << " " << endl;
	for (int i = 0; i < n; ++i) {
		out << rand() << " ";
	}
	out.close();
	
	return 0;
} 
