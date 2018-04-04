#include<iostream>
#include<time.h>
#include "PowerTools.h"
#include "BigInt.h"
#include <map>
#include <string>
using namespace std;

static map<int, int> fiboIntMapping;

int main() {
	int start, now, end;


	// using Roman numerals for the varialbe names - makes it easy to test and remember the values
	int i(1), v(5), x(10), xx(20), xxx(30), l(50), c(100),
		d(500), m(1000), mm(2000), mmm(3000), max(INT_MAX);

	BigInt Bi(i), Bv(v), Bx(x), Bxx(xx), Bxxx(xxx), Bl(l), Bc(c),
		Bd(d), Bm(m), Bmm(mm), Bmmm(mmm), Bmax(max);

	/*
	Universe is 93 Billion light years across https://www.universetoday.com/36302/atoms-in-the-universe/

	Light travels at 186,282 miles/second
	There are 365.2425 days in a year.
	How far is the universe from end to end in miles?
	Write this function: BigInt UniverseMiles( );
	Answer: 54669978319152000000000
	*/

	cout << "The width of the Universe in miles: " << BigInt::UniverseMiles() << endl;


	/*
	a Googol is 10^100
	a Googolplex = 10 ^ Googol
	*/

	BigInt Googol = exp(BigInt(10), BigInt(100));
	cout << "Google: " << Googol << endl;  // Mac users may need to change this code - makes the screenpause

	try {
		cout << "Googolplex: ";
		BigInt Googolplex = exp(BigInt(10), Googol);
		cout << Googolplex << endl;
	}
	catch(...){
		cout << "Too long to compute..." << endl;
	}

	system("pause");
	


	cout << "Here's some integer math..." << endl;
	cout << ".......addition........" << endl;
	cout << max << " + " << i << " = " << max + i << endl;
	cout << max << " + " << v << " = " << max + v << endl;
	cout << max << " + " << max << " = " << max + max << endl;
	cout << ".......multiplication........" << endl;
	cout << max << " * " << c << " = " << max * c << endl;
	cout << max << " * " << max << " = " << max * max << endl;
	cout << ".......exponentiation........" << endl;
	for (int index = 0; index <= 10; index++)
		cout << max << " ^ " << index << " = " << exp(max, index) << endl;
	cout << "2 ^ 1000 = " << exp(2, 1000) << endl;

	cout << "\n\nFactorials from 10 to 20............." << endl;
	start = time(0);
	for (int index = 10; index < 21; index++)
	{
		try {
			cout << "fact(" << index << ") = " << fact(index) << endl;
		}
		catch (...) {
			cout << "Exception Found on fact(" << index << ")\n";
		}
	}
	end = time(0);
	cout << "Elapsed seconds: " << end - start << endl;

	cout << "\nFibonacci nubmers from 40 to 50......................." << endl;
	for (int index = 40; index < 51; index++) {
		cout << "fibo(" << index << ") = ";
		try {
			int m = fibo(index);
			cout << m << endl;
		}
		catch (...) {
			cout << "Integer Overflow" << endl;
		}
	}


	cout << "\n\n\n";
	cout << "Here's some BigInt math..." << endl;
	cout << ".......addition........" << endl;
	cout << Bmax << " + " << Bi << " = " << Bmax + Bi << endl;
	cout << Bmax << " + " << Bv << " = " << Bmax + Bv << endl;
	cout << Bmax << " + " << Bmax << " = " << Bmax + Bmax << endl;
	cout << ".......multiplication........" << endl;
	cout << Bmax << " * " << Bc << " = " << Bmax * Bc << endl;
	cout << Bmax << " * " << Bmax << " = " << Bmax * Bmax << endl;
	cout << ".......exponentiation........" << endl;
	for (int Bindex = 0; Bindex <= 10; Bindex++)
	{
		cout << Bmax << " ^ " << Bindex << " = " << exp(Bmax, Bindex) << endl;
	}
	cout << "2 ^ 1000 = ";
	cout << exp(BigInt(2), BigInt(1000)) << endl;

	cout << "Factorials from 10 to 20............." << endl;
	start = time(0);
	for (BigInt index = 10; index < 21; index++)
		cout << "fact(" << index << ") = " << fact(index) << endl;
	end = time(0);
	cout << "Elapsed time: " << end - start << " seconds" << endl;

	cout << "\nFibonacci numbers from 40 to 50............." << endl;
	start = time(0);
	for (BigInt index = 40; index < 51; index++)
	{
		now = time(0);
		cout << "fibo(" << index << ") = " << fibo(index);
		cout << "...(" << time(0) - now << " seconds)" << endl;;
	}
	end = time(0);
	cout << "Elapsed time: " << end - start << " seconds" << endl;

	cout << "\n\nBonus Round........\n";
	cout << "fibo(1000) = ";
	cout << fibo(BigInt(1000)) << endl;
	cout << "fact(1000) = ";
	BigInt fact200 = fact(BigInt(400));
	cout << fact200 << endl;
	cout << "TATA" << endl;
	BigInt fact1000 = fact(BigInt(1000));
	cout << fact1000 << endl;

	cout << "Here are all the digits of fact(1000)\n\n";
	system("pause");
	fact1000.print();

	system("pause");





	return 0;
}
