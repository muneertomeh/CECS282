#include <iostream>
#include <string>
#include "myDate.h"
using namespace std;


int main() {
	int month, day, year;

	myDate d1 = myDate();
	myDate dueDate = myDate(2, 27, 2017);
	int x = d1.daysBetween(dueDate);
	cout << "Steve Gold is " << x << " days old today" << endl;

	d1.incrDate(x);
	cout << "Now these days should be the same: ";
	d1.display();
	cout << '\t';
	dueDate.display();
	cout << "\n\n";

	cout << "" << endl;
	cout << "Current day since the beginning of the year for due date is: " << dueDate.dayOfYear() << endl;

	cout << "Changing another date..." << endl;
	myDate d3 = myDate(8, 27, 2008);
	int jack = d3.dayOfYear();
	d3.decrDate(jack - 1);

	cout << "In 2008, New Years occured on: ";
	d3.display();
	cout << endl;
	month = d3.getMonth();
	day = d3.getDay();
	year = d3.getYear();
	cout << "New Years 2008 is also equal to " << month << "/" << day << "/" << year << endl;
	cout << endl;

	cout << "" << endl;
	cout << "Here are the dates for the past week" << endl;
	for (int i = 0; i < 7; i++) {
		dueDate.display();
		cout << " : " << dueDate.dayOfWeek() << endl;
		dueDate.decrDate(1);
	
	}
	cout << "Finally" << endl;
	dueDate.display();
	cout << " : " << dueDate.dayOfWeek() << endl;

	cout << "" << endl;
	myDate badDate = myDate(24, 15, 2019);
	cout << "The bad date now is................." << endl;
	badDate.display();
	cout << endl;

	
	return 0;
}
