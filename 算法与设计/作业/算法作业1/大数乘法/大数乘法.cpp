#include <iostream>
using namespace std;

int f(int x, int y, int n)
{
	int result, a, b, c, d, ac, bd, S;

	if (n == 1)
		return x * y;
	a = x >> (n / 2);
	b = x - (a << (n / 2));
	c = y >> (n / 2);
	d = y - (c << (n / 2));
	ac = f(a, c, n / 2);
	bd = f(b, d, n / 2);
	S = f(a - b, d - c, n / 2);
	result = (ac << n) + ((S + ac + bd) << n / 2) + bd;

	return result;
}

int main()
{
	int x, y;

	cin >> x;
	cin >> y;
	cout << f(x, y, 32);

	return 0;
}