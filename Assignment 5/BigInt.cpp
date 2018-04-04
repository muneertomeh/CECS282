#include <iostream>
#include <string>
#include "BigInt.h"
#include <map>

using namespace std;
static vector<int> maxIntThingy = { 7,4,6,3,8,4,7,4,1,2 };

	//Default constructor
	BigInt::BigInt() {
		myVector.push_back(0);
	}

	//Overloaded constructor that transforms a regular int to a BigInt
	BigInt::BigInt(int x) {
		string::reverse_iterator it;
		string integerToString = to_string(x);

		for (it= integerToString.rbegin(); it != integerToString.rend(); it++) {
			int digit = (*it) - '0';
			myVector.push_back(digit);
		}
	}

	//Overloaded constructor that transforms a integer in string format to a BigInt
	BigInt::BigInt(string x) {
		string::reverse_iterator it;
		for (it = x.rbegin(); it != x.rend(); it++) {
			int digit = (*it) - '0';
			myVector.push_back(digit);
		}
	}

	//copy constructor
	BigInt::BigInt(BigInt & b) {
		myVector = b.myVector;
	}

	//additional copy constructor for const
	BigInt::BigInt(const BigInt& daOther) {
		myVector = daOther.myVector;
	}


	//gettter for a BigInt's vector
	vector<int> BigInt::getVector() {
		return myVector;
	}


	//adds two BigInts together and returns their summation
	BigInt BigInt :: operator+(BigInt other) {
		BigInt top(*this);
		BigInt bottom(other);
		BigInt result;
		BigInt temp;

		//switches the two BigInts if the bottom one has a larger size
		if (top.myVector.size() < bottom.myVector.size()) {
			temp = top;
			top = bottom;
			bottom = temp;
		}

		if (top.myVector.size() > bottom.myVector.size() || top.myVector.size() == bottom.myVector.size()){
			int difference = top.myVector.size() - bottom.myVector.size();
			//adds zeros to vector with least size in order to make BigInt addition easier, these zeros will be removed once addition is complete
			while (difference > 0) {
				bottom.myVector.push_back(0);
				difference--;
			}

			int beginSum = 0;
			int endSum = 0;
			int carry = 0;
			for (int i = 0; i<top.myVector.size(); i++) {
				beginSum = carry + top.myVector[i];
				endSum = beginSum + bottom.myVector[i];

				//if the addition result is greater than 10, then place the left side of value into the carry var
				if (endSum >= 10) {
					carry = endSum / 10;
				}
				else { //there is no carry, so it is zero
					carry = 0;
				}
				//if there is a carry and the last column of bigints is calculated, then insert both the result and carry value
				if (endSum >= 10 & i == top.myVector.size() - 1) {
					result.myVector.push_back(endSum % 10);
					result.myVector.push_back(endSum/10);
				}
				else { //else, just insert the result of the column of ints into the vector
					result.myVector.push_back(endSum % 10);
				}
			}
			result.myVector.erase(result.myVector.begin() +0 );
		}		
		return result;
	}

	//calculates the sum of a BigInt and a regular integer
	BigInt BigInt :: operator+(int x) {
		*this = *this + BigInt(x); //in order to add a integer to a BigInt, that int must be transformed into a BigInt too
		return *this;
	}

	//performs subtraction on two BigInts and their difference is returned
	BigInt BigInt :: operator-(BigInt other) {
		bool flag = true;
		BigInt top(*this);
		BigInt bottom(other);
		BigInt temp(0);
		BigInt resultingDifference;


		int auxiliary;
		int borrow = 0;

		//loops through entire vector for BigINt subtraction arithmetic
		for (int i = 0; i < top.myVector.size(); i++) {
			auxiliary = top.myVector[i] - borrow;
			borrow = 0;

			if (i< bottom.myVector.size()) {
				auxiliary = auxiliary - bottom.myVector[i];
			}
			
			//if subtraction result is less than 0, then add 10 to it and utilize a borrow
			if (auxiliary < 0) {
				auxiliary = auxiliary + 10;
				borrow = 1;
				
			}
			//finally insert value onto the vector
			
			resultingDifference.myVector.push_back(auxiliary);
			
		}
		resultingDifference.myVector.erase(resultingDifference.myVector.begin());

		while (flag) {
			int temp = resultingDifference.myVector[resultingDifference.myVector.size()-1];
			if (temp != 0) {
				break;
			}
			resultingDifference.myVector.erase(resultingDifference.myVector.begin()+ resultingDifference.myVector.size() - 1);
		}
		return resultingDifference;
	}

	//calculates the difference of a BigInt and a regular integer, then returns their difference as a BigInt
	BigInt BigInt :: operator-(int x) {
		
		string numberToAppend;
		BigInt winningPlacement(*this);
		vector<int> ::reverse_iterator iteratingInRev;

		for (iteratingInRev = winningPlacement.myVector.rbegin(); iteratingInRev != winningPlacement.myVector.rend(); iteratingInRev++) {
			numberToAppend.append(to_string(*iteratingInRev));
		}

		int temp = stoi(numberToAppend);
		temp = temp - x;
		return BigInt(temp);
	}


	//increments a BigInt value by 1
	BigInt BigInt :: operator++(int dummy) {
		(*this) = *this + 1;
		return *this;
	}

	//friend method to calculate summation of BigInt and a normal int
	BigInt operator+(int x, BigInt B) {
		return B + x;
	}


	//multiplies a BigInt by another BigInt to receive the product of those two numbers
	BigInt BigInt :: operator*(BigInt multiplicand) {
		BigInt multiplier(*this);
		BigInt temp;
		BigInt temp2;
		BigInt zero(0);

		if (multiplier<multiplicand) {
			BigInt temp = multiplier;
			multiplier = multiplicand;
			multiplicand = temp;
		}
		BigInt result(0);

		while (zero< multiplicand) {

			if (multiplicand.myVector.at(0) %2 != 0) {
				temp2 = result + multiplier;
				result = temp2;
			}
			temp = multiplier * 2;
			multiplier = temp;
			multiplicand = multiplicand / 2;
		}
		return result;
	}

	//multiplies a BigInt by an integer that transforms into a BigInt for further BigInt multiplication
	//multiplies a BigInt by another BigInt to receive the product of those two numbers
	BigInt BigInt :: operator*(int other) {
		BigInt multiplicand(other);
		BigInt temp(*this);
		BigInt counter(1);
		BigInt product(0);
		int tracker = 0;

		while (counter != multiplicand) {
			if (tracker == 0) {
				product = temp;
			}
			else {
				product = product + temp;
			}
			counter++;
			tracker++;
		}
		product = product + temp;
		return product;
	}

	//the not equal operator determines if two BigInts are actually not equal for the sake of breaking a loop
	bool BigInt :: operator!=(BigInt b) {
		BigInt mun(*this);
		if (mun.myVector == b.myVector) {
			return false;
		}
		else {
			return true;
		}
	}


	//compares less than operator on two BigInts
	bool operator<(const BigInt & firstB, const BigInt & secondB) {
		if (firstB.myVector < secondB.myVector) {
			return true;
		}
		return false;
	}


	//divides a BigInt by an int 
	BigInt BigInt:: operator/(int x) {
		bool flag = false;
		if (myVector.size() >= maxIntThingy.size()) {
			if (myVector.size() > maxIntThingy.size()) {
				return *this / BigInt(x);
			}
			for (int i = myVector.size() - 1; i > -1; i--) {
				if (myVector[i] > maxIntThingy[i]) {
					flag = true;
					break;
				}
			}
		}
		if (flag == true) {
			return *this / BigInt(x);
		}

		string numberToAppend;
		BigInt winningPlacement(*this);
		vector<int> ::reverse_iterator iteratingInRev;

		for (iteratingInRev = winningPlacement.myVector.rbegin(); iteratingInRev != winningPlacement.myVector.rend(); iteratingInRev++) {
			numberToAppend.append(to_string(*iteratingInRev));
		}

		int temp = stoi(numberToAppend);
		temp = temp / x;

		return BigInt(temp);
	}


	//divides a BigInt by a BigInt
	BigInt BigInt:: operator/(BigInt y) {
		vector<int> ::reverse_iterator reverseFlash;
		int x = y.myVector.at(0);
		BigInt resultant(0);
		BigInt finalResultant(0);
		int backToBack;
		int placement;
		int moduloPlacement;


		for (int i = myVector.size() - 1; i > -1; i--) {
			if (i == myVector.size() - 1) {
				placement = myVector[i] / x;
				moduloPlacement = myVector[i] % x;
				if (i == 0) {
					resultant.myVector.push_back(placement);
					break;
				}
				resultant.myVector.push_back(placement);
			}
			else {
				placement = backToBack / x;
				moduloPlacement = backToBack % 2;
				resultant.myVector.push_back(placement);
			}

			if (i == 0) {
				break;
			}


			string tempString = to_string(moduloPlacement);
			tempString.append(to_string(myVector[i - 1]));
			backToBack = stoi(tempString);

			if (resultant.myVector.at(0) == 0) {
				resultant.myVector.erase(resultant.myVector.begin());
			}

		}
		
		for (reverseFlash = resultant.myVector.rbegin(); reverseFlash != resultant.myVector.rend(); reverseFlash++) {
			finalResultant.myVector.push_back(*reverseFlash);
		}
		finalResultant.myVector.erase(finalResultant.myVector.begin());
		return finalResultant;
	}
	



	//determines if a BigInt less than another BigInt
	bool BigInt ::operator<(BigInt other) {
		BigInt current(*this);
		//if there are the same size...
		if (current.myVector.size() == other.myVector.size()) {
			if (current.myVector == other.myVector) {
				return false;
			}
			//if not loop until a digit is bigger than other digit
			for (int k = 0; k < current.myVector.size(); k++) {
				if (current.myVector[k] < other.myVector[k]) {
					return true;
				}
			}
		}
		else if (current.myVector.size() < other.myVector.size()) {
			return true;
		}
		else {
			return false;
		}
	}

	//displays shorthand version of the BigInt
	ostream & operator<<(ostream & weOut, BigInt grandInteger) {
		//if size is 21 or greater, then print some digits of the BigInt
		if (grandInteger.myVector.size() >= 21) {
			vector<int> ::iterator thisWay;
			vector<int> ::reverse_iterator backThisWay;
			int j = grandInteger.myVector.size() - 1;

			//collecting ostream on first 11 digits
			for (backThisWay = grandInteger.myVector.rbegin(); backThisWay != grandInteger.myVector.rend(); backThisWay++) {
				if (j == grandInteger.myVector.size() - 12) {
					break;
				}
				else {
					weOut << *backThisWay;
				}
				j--;
			}
			cout << "......";
			//collecting ostream on "last" 10 digits
			for (int k = 9; k > -1; k--) {
				if (k == 10) {
					break;
				}
				else {
					weOut << grandInteger.myVector[k];
				}
			}
			weOut << " [size:" << grandInteger.myVector.size()<< "]";
			return weOut;

		}//else print the entire BigInt since it isn't that large
		else {
			grandInteger.print();
			return weOut;
		}
	}

	//prints the entire value of a BigInt
	void BigInt::print() {
		vector<int> ::reverse_iterator iterateInRev;
		for (iterateInRev = myVector.rbegin(); iterateInRev != myVector.rend(); iterateInRev++) {
			cout << *iterateInRev;
		}
	}

	//computes the universe's total amount of miles
	BigInt BigInt :: UniverseMiles() {
		BigInt secondsInYear(31556952);
		BigInt lightVelocity(186282);
		BigInt lightYears("93000000000");

		BigInt wow3 = secondsInYear * lightVelocity;
		return wow3 * lightYears;
	}
