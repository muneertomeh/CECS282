#include "myDate.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <iomanip>
using namespace std;

struct Student {
	int ID;              //student ID
	char name[30];       //student name
	char grade;			 //student grade
	string homeTown;     //student hometown
	myDate birthday;	 //student birthday
};

void fillStudents(Student*);
void initializeStudentArray(Student**, Student*);
int* getRandomIDs();
char* getRandomGrades();
string* getHomeTowns();
void selectionSortID(Student**);
void selectionSortName(Student**);
void selectionSortGrade(Student**);
void selectionSortHomeTown(Student**);
void selectionSortAge(Student**);
void display(Student*);
void displaySort(Student**);


int main() {
	Student cecs282[10]; //an array of Students which will the be original list
	fillStudents(cecs282);


	Student *studID[10]; //forming an array of pointers that will point to every student, later sorts based on student ID order
	Student *studName[10]; //forming an array of pointers that will point to every student, later sorts based on student name order
	Student* studGrade[10]; //forming an array of pointers that will point to every student, later sorts based on student grade order
	Student *studHome[10]; //forming an array of pointers that will point to every student, later sorts based on student hometown order
	Student *studAge[10]; //forming an array of pointers that will point to every student, later sorts based on student age order

	//each pointer of the 5 arrays of pointers to students will now point to each student from the regular array
	initializeStudentArray(studID, cecs282);
	initializeStudentArray(studName, cecs282);
	initializeStudentArray(studGrade, cecs282);
	initializeStudentArray(studHome, cecs282);
	initializeStudentArray(studAge, cecs282);



	selectionSortID(studID);         //sort array of pointers to students by student ID order
	selectionSortName(studName);     //sort array of pointers to students by student name order
	selectionSortGrade(studGrade);   //sort array of pointers to students by student grade order
	selectionSortHomeTown(studHome); //sort array of pointers to students by student hometown order
	selectionSortAge(studAge);       //sort array of pointers to students by student age order

	

	int menuSelection = 0;
	do { //displays menu of options
		cout << "1) Display original list" << endl;
		cout << "2) Display list sorted by Student ID" << endl;
		cout << "3) Display list sorted by Name" << endl;
		cout << "4) Display list sorted by Grade" << endl;
		cout << "5) Display list sorted by Home Town" << endl;
		cout << "6) Display list sorted by Student Age" << endl;
		cout << "7) Exit" << endl;

		cin >> menuSelection;
		switch (menuSelection) {
		case 1: //displays original list
			cout << "" << endl;
			display(cecs282);
			cout << "" << endl;
			break;

		case 2: //displays list sorted by student ID
			cout << "" << endl;
			displaySort(studID);
			cout << "" << endl;
			break;

		case 3: //displays list sorted by student name
			cout << "" << endl;
			displaySort(studName);
			cout << "" << endl;
			break;

		case 4: //displays list sorted by student grade
			cout << "" << endl;
			displaySort(studGrade);
			cout << "" << endl;
			break;

		case 5: //displays list sorted by student hometown
			cout << "" << endl;
			displaySort(studHome);
			cout << "" << endl;
			break;

		case 6: //displays list sorted by student age
			cout << "" << endl;
			displaySort(studAge);
			cout << "" << endl;
			break;

		case 7: //exits program
			cout << "Goodbye!" << endl;
			break;
		}

	} while (menuSelection !=7);

	return 0;
}



//Method fills up the array of students with certain information such ID, name, grade, hometown, and birthday
void fillStudents(Student* daArray) {
	int *ptrArray; //retrieves an array of random IDs
	ptrArray = getRandomIDs();

	char *charArray; //retrieves an array of random chars
	charArray = getRandomGrades();

	string* strArray; // retrieves an array of hometowns 
	strArray = getHomeTowns();

	strcpy_s(daArray[0].name, "Batman");
	strcpy_s(daArray[1].name, "Superman");
	strcpy_s(daArray[2].name, "Green Arrow");
	strcpy_s(daArray[3].name, "Flash");
	strcpy_s(daArray[4].name, "Green Lantern");
	strcpy_s(daArray[5].name, "Wonder Woman");
	strcpy_s(daArray[6].name, "Cyborg");
	strcpy_s(daArray[7].name, "Nightwing");
	strcpy_s(daArray[8].name, "Aquaman");
	strcpy_s(daArray[9].name, "John Constantine");

	//assigning IDs, grades, hometowns, and birthdays to every student using retrieved arrays of information
	for (int i = 0; i < 10; i++) {
		daArray[i].ID = *(ptrArray + i);
		daArray[i].grade = *(charArray + i);
		daArray[i].homeTown = *(strArray + i);
		daArray[i].birthday = myDate();
	}

}

//Method initializes an array of pointers, in which each pointer will point to a student in the original array
void initializeStudentArray(Student** sptr, Student* pupils) {
	for (int i = 0; i < 10; i++) {
		sptr[i] = &pupils[i];
	}
}



//Method uses a selection sort algorithm to ascendingly sort students based on their IDs
void selectionSortID(Student** array) {
	Student* temporary;
	for (int i = 0; i < 9; i++) {
		int minIndex = i;
		for (int j = i + 1; j < 10; j++) {
			//compares two IDs of two different students
			if ((*array[j]).ID < (*array[minIndex]).ID) {
				minIndex = j;
			}
		} //swaps positions of the two students
		if (minIndex != i) {
			temporary = array[minIndex];
			array[minIndex] = array[i];
			array[i] = temporary;
		}
	}
}

//Method uses a selection sort algorithm to ascendingly sort students based on students' names
void selectionSortName(Student** array) {
	Student* auxiliary;
	
	for (int i = 0; i < 9; i++) {
		int minIndex = i;
		for (int j = i+1; j < 10; j++) {
			if (strcmp((*array[j]).name, (*array[minIndex]).name)<0) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			auxiliary = array[minIndex];
			array[minIndex] = array[i];
			array[i] = auxiliary;
		}
	}
}

//Method uses a selection sort algorithm to ascendingly sort students based on their grades 
void selectionSortGrade(Student** array) {
	Student * backup;

	for (int i = 0; i < 9; i++) {
		int minimumIndex = i;
		for (int j = i + 1; j < 10; j++) {
			if ((*array[j]).grade  > (*array[minimumIndex]).grade) {
				minimumIndex = j;
			}
		}
		if (minimumIndex != i) {
			backup = array[minimumIndex];
			array[minimumIndex] = array[i];
			array[i] = backup;
		}
	}
}


//Method uses a selection sort algorithm to ascendingly sort students based on their hometowns
void selectionSortHomeTown(Student** array) {
	Student* temporary;
	
	for (int i = 0; i < 9; i++) {
		int minimumIndex = i;
		for (int j = i+1; j < 10; j++) {
			if (((*array[j]).homeTown).compare((*array[minimumIndex]).homeTown)<0) {
				minimumIndex = j;	
			}
		}
		if (minimumIndex != i) {
			temporary = array[minimumIndex];
			array[minimumIndex] = array[i];
			array[i] = temporary;
		}
	}
}



//Method uses a selection sort algorithm to ascendingly sort students based on their ages
void selectionSortAge(Student** array) {
	int minimumIndex, j;
	Student * temporary;

	for (int i = 0; i < 9; i++) {
		int minimumIndex = i;
		for (int j = i + 1; j < 10; j++) {
			//compares two ages of two different students
			if (((*array[j]).birthday.dateConverter() < (*array[minimumIndex]).birthday.dateConverter())) {
				minimumIndex = j;
			}
		}
		if (minimumIndex != i) {
			temporary = array[minimumIndex];
			array[minimumIndex] = array[i];
			array[i] = temporary;
		}
	}
}


//Displays list after sorting based on ID, name, grade, etc according to user selection
void displaySort(Student** sortedStudents) {
	cout << "Student ID" << "---\t" << "Name" << "---         \t" << "Grade" << "--- \t" << "Home Town" << "---\t" << "           Birthday---" << endl;
	for (int i = 0; i < 10; i++) {
		cout << setw(16) << left << (*sortedStudents[i]).ID << setw(24) << left << (*sortedStudents[i]).name << setw(16) << left << (*sortedStudents[i]).grade << setw(27) << left << (*sortedStudents[i]).homeTown << setw(10) << left << (*sortedStudents[i]).birthday.display() << endl;
	}
}

//Displays original list of student information
void display(Student* daStudents) {
	cout << "Student ID" << "---\t" << "Name" << "---         \t" << "Grade" << "--- \t" << "Home Town" << "---\t" << "           Birthday---" << endl;
	for (int i = 0; i < 10; i++) {
		cout << setw(16) << left << daStudents[i].ID << setw(24) << left << daStudents[i].name << setw(16) << left << daStudents[i].grade << setw(27) << left << daStudents[i].homeTown << setw(10) << left << daStudents[i].birthday.display() << endl;
	}
}


//Generates 10 random IDs one for each student
int* getRandomIDs() {
	srand(time(0));
	int randyNum;
	static int id[10];
	int*ptr = id;
	int j = 1;
	int currentLimit = 1;

	for (int i = 0; i < 10; i++) {
		randyNum = 1000 + (rand() % (int)(9999 - 1000));
		j = 0;
		//loop determines if a recently generated ID is already inside the array of student IDs; if yes, then a new one is generated and checks once again
		while (j < currentLimit) {
			if (randyNum == ptr[j]) {
				randyNum = 1000 + (rand() % (int)(9999 - 1000));
				j = 0;
			}
			else{
				j++;
}
		}
		currentLimit++;
		ptr[i] = randyNum;
	}
	return ptr;
}

//Retrieves a character array filled with randomly generated letter grades (A, B, C, D, F) for each student
char* getRandomGrades() {
	srand(time(0));
	char lettaGrades[5] = { 'A', 'B', 'C', 'D', 'F' };
	static char grades[10];
	char* ptr = grades;
	int randyIndex;

	for (int i = 0; i < 10; i++) {
		randyIndex = 0 + (rand() % (int)(5 - 0));
		ptr[i] = lettaGrades[randyIndex];
	}
	return ptr;
}

//Retrieves hometowns of all ten students
string* getHomeTowns() {
	string ht[10] = { "Gotham City", "Metropolis", "Star City", "Central City", "Coast City", "Themyscira", "National City", "Bludhaven", "Atlantis", "Smallvile" };
	static string hometowns[10];
	string* ptr2 = hometowns;

	for (int i = 0; i < 10;  i++) {
		ptr2[i] = ht[i];
	}

	return ptr2;
}
