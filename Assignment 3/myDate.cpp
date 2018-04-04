#include <iostream>
#include <string>
#include "myDate.h"
using namespace std;

//default constructor
myDate::myDate() {

	int firstJulian = Greg2Julian(1, 1, 1995);
	int secondJulian = Greg2Julian(12, 31, 1999);
	int randyJulian = firstJulian + (rand() % (int)(secondJulian - firstJulian));
	Julian2Greg(randyJulian, month, day, year);
}

//overloaded constructor determines if entries of date are valid, if not default dates will be loaded
myDate::myDate(int M, int D, int Y) {

	int temp1 = M;
	int temp2 = D;
	int temp3 = Y;

	//converts from gregorian to julian for validating user entry for date
	int auxJD = Greg2Julian(M, D, Y);
	Julian2Greg(auxJD, M, D, Y);

	//determine if dates pre-conversion and post-conversion of Gregorian and Julian are exactly the same
	if (temp1 != M || temp2 != D || temp3 != Y) {
		month = 5;
		day = 11;
		year = 1959;
	}
	//else, all entries of date are correct
	else {
		month = temp1;
		day = temp2;
		year = temp3;
	}

}

//Displays the date in the following format ---> (Month name, Date, Year)
string myDate::display() {
	string dateInString;
	//converts from month number format to string format
	switch (month) {
	case 1:
		dateInString = "January";
		break;
	case 2:
		dateInString = "February";
		break;
	case 3:
		dateInString = "March";
		break;
	case 4:
		dateInString = "April";
		break;
	case 5:
		dateInString = "May";
		break;
	case 6:
		dateInString = "June";
		break;
	case 7:
		dateInString = "July";
		break;
	case 8:
		dateInString = "August";
		break;
	case 9:
		dateInString = "September";
		break;
	case 10:
		dateInString = "October";
		break;
	case 11:
		dateInString = "November";
		break;
	case 12:
		dateInString = "December";
		break;

	}
	dateInString.append(" ");
	dateInString.append(to_string(day));
	dateInString.append(", ");
	dateInString.append(to_string(year));

	return dateInString;
}

//Increases the date of myDate object by N days
void myDate::incrDate(int N) {

	int accumulativeJD = Greg2Julian(getMonth(), getDay(), getYear());
	//adding the julian date of original date and the number of N days, to attain the new Julian date
	int newJulianDate = accumulativeJD + N;
	Julian2Greg(newJulianDate, month, day, year);

}

//Decreases the date of myDate object by N days;
void myDate::decrDate(int N) {

	int newlyJD = Greg2Julian(getMonth(), getDay(), getYear());
	int recentJulianDate = newlyJD - N;
	Julian2Greg(recentJulianDate, month, day, year);


}

//Returns the number of days between this date and the otherDate object's date
int myDate::daysBetween(myDate otherDate) {
	int dayInterval = 0;

	//converting each gregorian calendar date to julian date for further arithmetic on the two Julian dates
	int JDforFirst = Greg2Julian(getMonth(), getDay(), getYear());
	int JDforSecond = Greg2Julian(otherDate.getMonth(), otherDate.getDay(), otherDate.getYear());

	return dayInterval = JDforSecond - JDforFirst;
}

//retrieves the month of the myDate object
int myDate::getMonth() {
	return month;
}

//retrieves the day of the myDate object
int myDate::getDay() {
	return day;
}

//retrieves the year of the myDate object
int myDate::getYear() {
	return year;
}

//returns the number of days since the current year began
int myDate::dayOfYear() {
	int dayCounter = 0;
	int currentMonth = 1;
	int daysInMonths[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	for (int i = 0; i < 12; i++) {
		//checks if the object's year is indeed a leap year
		if (currentMonth == 2 && year % 4 == 0) {
			if (year % 100) {
				// if it is, change the number of days in the month of February
				if (year % 400) {
					daysInMonths[1] = 29;
				}
			}
		}
		//if the object's month has been reached, then just add the value in day to the dayCounter
		if (currentMonth == month) {
			dayCounter += day;
			break;
		}
		//resume adding the amount of days in that specific month, and go to the beginning of for loop for further iteration
		dayCounter += daysInMonths[i];
		currentMonth++;
	}
	return dayCounter;
}

//This method returns Monday, Tuesday, etc according to the day of the week
string myDate::dayOfWeek() {
	int m = month;
	int d = day;
	int y = year;
	int dayPattern[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	int dayValue = (y + y / 4 - y / 100 + y / 400 + dayPattern[m - 1] + d) % 7;
	string dayName;

	switch (dayValue) {
	case 0:
		dayName = "Sunday";
		break;
	case 1:
		dayName = "Monday";
		break;
	case 2:
		dayName = "Tuesday";
		break;
	case 3:
		dayName = "Wednesday";
		break;
	case 4:
		dayName = "Thursday";
		break;
	case 5:
		dayName = "Friday";
		break;
	case 6:
		dayName = "Saturday";
		break;
	}
	return dayName;
}

//Retrieves the Julian date for a certain date
int myDate::dateConverter() {
	return Greg2Julian(month, day, year);
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

