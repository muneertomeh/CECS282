#include "PowerTools.h"
#include "BigInt.h"
#include <iostream>
#include <map>
using namespace std;

static map<BigInt, BigInt> factBigIntMap;
static map<int, int> fiboIntMap;
vector<int> checkerZero = { 0 };
vector<int> checkerOne = { 1 };
static map<BigInt, BigInt> fiboBigIntMap;

//Calculates factorial for an integer value, n
int fact(int n) {
	static int temp = 1;

	if (n != 0) {
		temp = temp * n;
		if (temp < 0) {
			temp = 1;
			throw temp;
		}
	}
	if (n == 0) {
		temp = 1; //reset temp back to 1 at the end of factorial recursion
		return 1;
	}

	else {
		return n * fact(n - 1);
	}
}


//Calculates fibonacci for an integer value, n
int fibo(int n) {
	if (n == 0 || n == 1) {
		return 1;
	}
	if (!fiboIntMap.count(n)) {
		fiboIntMap[n] = fibo(n - 1) + fibo(n - 2);
		//if one of the values in the map is below zero, then there is int overflow
		if (fiboIntMap[n] < 0 || n==47) {
			throw fiboIntMap;
		}
	}
	return fiboIntMap[n];
}


//Calculates exponents based on base and exponent
int exp(int x, int y) {
	if (y == 0) {
		return 1;
	}
	if (y == 1) {
		return y;
	}
	else {
		return x * exp(x, y - 1);
	}
}

//Calculates the fibonacci of a BigInt
BigInt fibo(BigInt b) {
	if (b.getVector() == checkerZero || b.getVector() == checkerOne) {
		return BigInt(1);
	}
	if (!fiboBigIntMap.count(b)) {
		fiboBigIntMap[b] = fibo(b - 1) + fibo(b - 2);
	}
	return fiboBigIntMap[b];
}

//Calculates the factorial of a BigInt 
BigInt fact(BigInt b) {
	static BigInt temp(1);
	if (b.myVector == checkerZero) {
		return BigInt(1);
	}

	if(!factBigIntMap.count(b)) {
		factBigIntMap[b]= fact(b - 1) * b;
		
	}
	return factBigIntMap[b];
}


//calculates exponent of BigInt
BigInt exp(BigInt x, int y) {

	if (y ==0) {
		
		return BigInt(1);
	}
	if (y == 1) {
		return x;
	}
	else {
		return x * exp(x, y - 1);
	}
}

//calculates exponent of BigInt
BigInt exp(BigInt x, BigInt y) {
	if (y.myVector == checkerZero) {
		return BigInt(1);
	}
	
	else {
		return x * exp(x, y-1);
	}
}
