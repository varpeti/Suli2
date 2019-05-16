#include "iostream"
#include "fstream"
#include "sstream"
#include "math.h"
#include "vector"
#include "iomanip"
#include "string.h"

using namespace std;

struct skorte;

struct salma
{
	int ertek;
	skorte *korte;
};

struct skorte
{
	int ertek;
	salma *alma;
};


int main()
{
	salma alma;
	skorte korte;

	alma.ertek = 2;
	korte.ertek = 3;

	alma.korte = &korte;
	korte.alma = &alma;

	cout << alma.korte->alma->korte->ertek; // 3
	cout << alma.korte->alma->korte->alma->ertek; //2
	return 0;
} 