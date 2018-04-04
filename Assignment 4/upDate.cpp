#include <iostream>
#include <string>
#include "upDate.h"
//upDate.cpp
using namespace std;



int upDate::count = 0;

//default constructor
upDate::upDate() {
	datePtr = new int[3];
	*(datePtr + 0) = 5;
	*(datePtr + 1) = 11;
	*(datePtr + 2) = 1959;
	count++;

}

//Overloaded constructor
upDate::upDate(int mes, int dia, int ano) {
	datePtr = new int[3];
	int temp1 = mes;
	int temp2 = dia;
	int temp3 = ano;

	//converts from gregorian to julian for validating user entry for date
	int auxJD = Greg2Julian(mes, dia, ano);
	Julian2Greg(auxJD, mes, dia, ano);

	//determine if dates pre-conversion and post-conversion of Gregorian and Julian are exactly the same
	if (temp1 != mes|| temp2 != dia || temp3 != ano) {
		*(datePtr + 0) = 5;
		*(datePtr + 1) = 11;
		*(datePtr + 2) = 1959;
	}
	//else, all entries of date are correct
	else {
		*(datePtr + 0) = temp1;
		*(datePtr + 1) = temp2;
		*(datePtr + 2) = temp3;
	}
	count++;
	
}

//copy constructor
upDate::upDate(const upDate & D) {
	datePtr = new int[3];
	*(datePtr + 0) = D.datePtr[0];
	*(datePtr + 1) = D.datePtr[1];
	*(datePtr + 2) = D.datePtr[2];
	count++;

}

//destructor for an upDate object to deallocate memory
upDate :: ~upDate() {
	delete[] datePtr;
	count--;

}

//sets the date for an upDate object
void upDate::setDate(int mes, int dia, int ano) {
	datePtr[0] = mes;
	datePtr[1] = dia;
	datePtr[2] = ano;
	count++;
}

//returns the month
int upDate :: getMonth() {
	return *(datePtr + 0);
}

//returns the day
int upDate::getDay() {
	return *(datePtr + 1);
}

//returns the year
int upDate::getYear() {
	return *(datePtr + 2);
}

//returns the name of the month
string upDate::getMonthName() {
	string monthInString;
	//converts from month number format to string format
	switch ((*(datePtr+0))) {
	case 1:
		monthInString = "January";
		break;
	case 2:
		monthInString = "February";
		break;
	case 3:
		monthInString = "March";
		break;
	case 4:
		monthInString = "April";
		break;
	case 5:
		monthInString = "May";
		break;
	case 6:
		monthInString = "June";
		break;
	case 7:
		monthInString = "July";
		break;
	case 8:
		monthInString = "August";
		break;
	case 9:
		monthInString = "September";
		break;
	case 10:
		monthInString = "October";
		break;
	case 11:
		monthInString = "November";
		break;
	case 12:
		monthInString = "December";
		break;

	}

	return monthInString;
}

//Operator Overloading for D+x
upDate upDate::operator+(int x) {
	upDate temporary(*this);
	temporary.incrDate(x);
	return temporary;
}

//Operator Overloading for D - x
upDate upDate::operator-(int x) {
	upDate temp(*this);
	temp.decrDate(x);
	return temp;
}

//Operator Overloading for =
upDate upDate :: operator=(const upDate & D) {
	datePtr = new int[3];
	datePtr[0] = D.datePtr[0];
	datePtr[1] = D.datePtr[1];
	datePtr[2] = D.datePtr[2];

	return *this;
}

//Friend Operator Overloading for x+D
upDate operator+(int x, upDate D) {
	return D + x;
}

//Friend Operator Overloading for output stream <<
ostream & operator<<(ostream & weOut, upDate D) {
	weOut << D.getMonth() << "/" << D.getDay() << "/" << D.getYear();
	return weOut;
}

//Friend Operator Overloading for difference of two upDate objects
 int operator-(const upDate & D1, const upDate & D2) {
	int thisJulian = Greg2Julian(D1.datePtr[0], D1.datePtr[1], D1.datePtr[2]);
	int otherJulian = Greg2Julian(D2.datePtr[0], D2.datePtr[1], D2.datePtr[2]);
	return thisJulian - otherJulian;
}

//Operator Overloading for (upDate object here)++
upDate upDate :: operator++(int somethingUseLess) {
	upDate temp(*this);
	(*this).incrDate(1);
	return temp;
}

//Operator Overloading for (upDate object here)--
upDate upDate :: operator--(int somethingUseLess) {
	upDate temp(*this);
	(*this).decrDate(1);
	return temp;
}

//Operator Overloading for ++(upDate object here)
upDate upDate ::operator++() {
	(*this).incrDate(1);
	return *this;
}


//Operator Overloading for --(upDate object here)
upDate upDate ::operator--() {
	(*this).decrDate(1);
	return *this;
}


//Operator Overloading for <
bool upDate:: operator<(upDate D) {
	if (julian() < D.julian()) {
		return true;
	}
	return false;
}

//Operator Overloading for >
bool upDate:: operator>(upDate D) {
	if ((*this).julian() > D.julian()) {
		return true;
	}
	return false;
}


//Operator Overloading for ==, determines if two upDate objects are equal
bool upDate :: operator==(upDate D) {
	int thisJulianDate = julian();
	int otherJulianDate = D.julian();

	if (thisJulianDate == otherJulianDate) {
		return true;
	}
	return false;
}

//Increases the date of upDate object by N days
void upDate::incrDate(int N) {
	int accumulativeJD = julian();
	//adding the julian date of original date and the number of N days, to attain the new Julian date
	int newJulianDate = accumulativeJD + N;
	Julian2Greg(newJulianDate, datePtr[0], datePtr[1], datePtr[2]);

}

//Increases the date of upDate object by N days
void upDate::decrDate(int N) {

	int accumulativeJD = julian();
	//adding the julian date of original date and the number of N days, to attain the new Julian date
	int newJulianDate = accumulativeJD - N;
	Julian2Greg(newJulianDate, datePtr[0], datePtr[1], datePtr[2]);

}

//This method calls the Greg2Julian method to convert from a Gregorian calendar date to a Julian calendar date 
int upDate::julian() {
	return Greg2Julian(datePtr[0], datePtr[1], datePtr[2]);
}


//This method returns the amount of current upDate objects that currently exist during program runtime
int upDate::getDateCount() {
	return count;
}



//Converts a Gregorian calendar date to a Julian date
int Greg2Julian(int month, int day, int year) {
	int julianDate;
	int m = month;
	int d = day;
	int y = year;


	//an algorithm that computes Julian date based off Gregorian calendar date
	return julianDate = (1461 * (y + 4800 + (m - 14) / 12)) / 4 + (367 * (m - 2 - 12 * ((m - 14) / 12))) / 12 - (3 * ((y + 4900 + (m - 14) / 12) / 100)) / 4 + d - 32075;
	
}


//Converts a Julian date to a Gregorian calendar date
void Julian2Greg(int JD, int & month, int & day, int &year) {
	int L, N, I, J, K; //integers that help in converting from julian to gregorian

	L = JD + 68569;
	N = 4 * L / 146097;
	L = L - (146097 * N + 3) / 4;
	I = 4000 * (L + 1) / 1461001;
	L = L - 1461 * I / 4 + 31;
	J = 80 * L / 2447;
	K = L - 2447 * J / 80;
	L = J / 11;
	J = J + 2 - 12 * L;
	I = 100 * (N - 49) + I + L;

	month = J;
	day = K;
	year = I;

}
