#ifndef MYDATE_H
#define MYDATE_H
#include <iostream>
#include <string>
using namespace std;

//2 methods that are not included in the myDate class
int Greg2Julian(int month, int day, int year);
void Julian2Greg(int JD, int & month, int & day, int & year);

class myDate {
	private:
		int month;
		int day;
		int year;

	public:
		myDate();
		myDate(int M, int D, int Y);
		void display();
		void incrDate(int N);
		void decrDate(int N);
		int daysBetween(myDate otherDate);
		int getMonth();
		int getDay();
		int getYear();
		int dayOfYear();
		string dayOfWeek();
};

#endif;
