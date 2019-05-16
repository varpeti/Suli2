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
	double gy = sqrt(x);
	while (double(i)<gy) {
		if (x % i==0) {
			cout << i << " ";
			x/=i;
		}else i++;
	}
	if (x>1) cout << x;
	getchar();getchar();
	return 0;
} 