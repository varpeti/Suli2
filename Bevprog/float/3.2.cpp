#include "iostream"
#include "fstream"
#include "math.h"
#include "vector"
#include "iomanip"
#include "string.h"

using namespace std;


int main()
{
	int x;
	cin >> x;
	int i = 2;
	int o = 0;
	while (double(i)<x) {
		if (x % i==0) {
			o+=i;
		}
		i++;
	}
	cout << o;
	getchar();getchar();
	return 0;
} 