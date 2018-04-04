#include <iostream>
#include <string>
#include "Card.h"

using namespace std;

//default constructor
Card::Card() {
	rank = 'x';
	suit = 'y';
}

//overloaded constructor
Card::Card(char r, char s) {
	rank = r;
	suit = s;
}

//setter for a card
void Card::setCard(char r, char s) {
	rank = r;
	suit = s;
}

//this method displays a card visually that has been drawn from the deck
void Card::displayCard() {

	switch (suit) {
	case 'H': //case for a Heart card
		cout << "-------------" << endl;
		cout << "[" << rank << "          ]" << endl;
		cout << "[   ** **   ]" << endl;
		cout << "[  *  *  *  ]" << endl;
		cout << "[   *   *   ]" << endl;
		cout << "[    * *    ]" << endl;
		cout << "[     *     ]" << endl;
		cout << "[          "       <<rank<<"]" << endl;
		cout << "-------------" << endl;
		break;
		
	case 'S': //case for a Spade card
		cout << "-------------" << endl;
		cout << "[" << rank << "          ]" << endl;
		cout << "[     *     ]" << endl;
		cout << "[    * *    ]" << endl;
		cout << "[   *****   ]" << endl;
		cout << "[  *  *  *  ]" << endl;
		cout << "[     *     ]" << endl;
		cout << "[          " << rank << "]" << endl;
		cout << "-------------" << endl;
		break;

	case 'D': //case for a Diamond card
		cout << "-------------" << endl;
		cout << "[" << rank << "          ]" << endl;
		cout << "[     *     ]" << endl;
		cout << "[    * *    ]" << endl;
		cout << "[   *   *   ]" << endl;
		cout << "[    * *    ]" << endl;
		cout << "[     *     ]" << endl;
		cout << "[          "       <<rank<<"]" << endl;
		cout << "-------------" << endl;
		break;

	case 'C': //case for a Club card
		cout << "-------------" << endl;
		cout << "[" << rank << "          ]" << endl;
		cout << "[     *     ]" << endl;
		cout << "[  *  *  *  ]" << endl;
		cout << "[   * * *   ]" << endl;
		cout << "[     *	    ]" << endl;
		cout << "[     *	    ]" << endl;
		cout << "[          " << rank << "]" << endl;
		cout << "-------------" << endl;
		break;
	}

}

//This method displays the information of a card and outputs it to the user
void Card::displayCardInfo() {
	//the rank as a character data type is then processed to a string
	string daRank;
	switch (rank) {
	case 'A':
		daRank = "Ace";
		break;
	case 'K':
		daRank = "King";
		break;
	case 'Q':
		daRank = "Queen";
		break;
	case 'J':
		daRank = "Jack";
		break;
	case 'T':
		daRank = "Ten";
		break;
	case '9':
		daRank = "Nine";
		break;
	case '8':
		daRank = "Eight";
		break;
	case '7':
		daRank = "Seven";
		break;
	case '6':
		daRank = "Six";
		break;
	case '5':
		daRank = "Five";
		break;
	case '4':
		daRank = "Four";
		break;
	case '3':
		daRank = "Three";
		break;
	case '2':
		daRank = "Two";
		break;
	}

	//the suit as a character data type is then processed to a string
	string daSuit;
	switch (suit) {
		case 'H':
			daSuit = "Hearts";
			break;
		case 'S':
			daSuit = "Spades";
			break;
		case 'D':
			daSuit = "Diamonds";
			break;
		case 'C':
			daSuit = "Clubs";
			break;
	}

	cout << daRank + " of " + daSuit <<endl;

}

//This method retrieves the card value of a dealt card which is returned for comparison with another
//dealt card's value
int Card::getValue() {
	int cardValue;
	switch (rank) {
		case 'A':
			cardValue = 1;
			break;
		case 'K':
			cardValue = 13;
			break;
		case 'Q':
			cardValue = 12;
			break;
		case 'J':
			cardValue = 11;
			break;
		case 'T':
			cardValue = 10;
			break;
		case '9':
			cardValue = 9;
			break;
		case '8':
			cardValue = 8;
			break;
		case '7':
			cardValue = 7;
			break;
		case '6':
			cardValue = 6;
			break;
		case '5':
			cardValue = 5;
			break;
		case '4':
			cardValue = 4;
			break;
		case '3':
			cardValue = 3;
			break;
		case '2':
			cardValue = 2;
			break;
	}
	return cardValue;
}
