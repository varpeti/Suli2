#include "iostream"
#include "sstream"
#include "math.h"
#include "time.h"


using namespace std;

void fv(int &aaa)
{
	int *mmm = &aaa;
	mmm+=1;
	*mmm=100;
}

int main()
{	
	int pont = 0;
	int aaa = 32;
	fv(aaa);
	cout << pont;
	
	return 0;
} 