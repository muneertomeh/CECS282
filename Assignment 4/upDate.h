#ifndef UPDATE_H
#define UPDATE_H
#include <iostream>
#include <string>
using namespace std;

//upDate.h
int Greg2Julian(int month, int day, int year);
void Julian2Greg(int JD, int & month, int & day, int & year);

class upDate {
	private:
		int *datePtr;
		static int count;
		
		
	public:
		upDate();
		upDate(const upDate &);
		upDate(int, int, int);
		~upDate();
		void setDate(int, int, int);
		int getMonth();
		int getDay();
		int getYear();
		string getMonthName();
		void incrDate(int);
		void decrDate(int);
		int julian();

		static int getDateCount();

		upDate operator+(int);
		upDate operator-(int);
		upDate operator=(const upDate &);
		friend upDate operator+ (int, upDate);
		friend ostream & operator<<(ostream &, upDate);
		friend int operator-(const upDate &, const upDate &);

		upDate operator++(int);
		upDate operator--(int);

		upDate operator++();
		upDate operator--();

		bool operator<(upDate);
		bool operator>(upDate);
		bool operator==(upDate);
};
#endif

