#include <iostream>
#include <math.h> 
using namespace std;

int main()
{
	char a, b, c;
	int n, steps, coe, tmp;

	a = 'a';
	b = 'b';
	c = 'c';
	n = 30;
	char location[30];
	for(int i=0;i<n;++i)
	    location[i]='a';
	steps = pow(2, n) - 1;
	for (int i = 0; i < steps; ++i)
	{
		coe = n - 1;
		while (true)
		{
			int mid = 1;
			mid = mid << coe;
			if ((i + 1) % mid == 0)
				break;
			--coe;
		}
		//cout << coe + 1 << ':' << location[coe] << "->";
		if (n % 2 == 0 && (coe + 1) % 2 != 0)
			tmp = (location[coe] - a + 1) % 3;
		else if (n % 2 == 0 && (coe + 1) % 2 == 0)
			tmp = (location[coe] - a + 2) % 3;
		else if (n % 2 != 0 && (coe + 1) % 2 != 0)
			tmp = (location[coe] - a + 2) % 3;
		else if (n % 2 != 0 && (coe + 1) % 2 == 0)
			tmp = (location[coe] - a + 1) % 3;
			
		location[coe] = a + tmp;
		//cout << location[coe] << endl;
	}

	return 0;
}
