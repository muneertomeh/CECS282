#ifndef BIGINT_H
#define BIGINT_H

#include <vector>
using namespace std;


class BigInt {
	private:
		vector<int> myVector;

	public:
		BigInt();
		BigInt(int);
		BigInt(string);
		BigInt(BigInt&);
		BigInt(const BigInt&);
		vector<int> getVector();
		BigInt operator+(int);
		BigInt operator-(int);
		BigInt operator-(BigInt);
		BigInt operator+(BigInt);
		BigInt operator++(int);
		BigInt operator*(BigInt);
		BigInt operator*(int);
		friend bool operator<(const BigInt&, const BigInt&);
		bool operator<(BigInt);
		bool operator!=(BigInt);
		friend BigInt operator+(int, BigInt);
		
		friend BigInt fact(BigInt);
		friend BigInt exp(BigInt, int);
		friend BigInt exp(BigInt, BigInt);
		BigInt operator/(int);
		BigInt operator/(BigInt);


		friend ostream & operator<<(ostream&, BigInt);
		static BigInt UniverseMiles();

		
		void print();
};


#endif
